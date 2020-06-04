#include "ObjLoader.hpp"

#include <iostream>
#include <functional>
#include <glm/glm.hpp>
#include <optional>
#include <unordered_map>

namespace coffee::obj
{
constexpr int k_vectorReserveSize = 64;

struct ObjData
{
    std::vector<glm::vec3> vertices = {};
    std::vector<glm::vec3> normals = {};

    std::vector<uint16_t> vertexIndices = {};
    std::vector<uint16_t> normalIndices = {};
};

using ParseFunction = std::function<void(std::stringstream &, ObjData *)>;

inline glm::vec3 parseVec3(std::stringstream &lineStream)
{
    float x, y, z;
    lineStream >> x >> y >> z;
    return glm::vec3(x, y, z);
}

static void parseVertex(std::stringstream &lineStream, ObjData *objData)
{
    objData->vertices.emplace_back(parseVec3(lineStream));
}

static void parseNormals(std::stringstream &lineStream, ObjData *objData)
{
    objData->normals.emplace_back(parseVec3(lineStream));
}

static void parseFaces(std::stringstream &lineStream, ObjData *objData)
{
    auto parseFaceToken = [](std::stringstream &lineStream, char splitChar) -> std::optional<int>
    {
        std::string token;
        std::getline(lineStream, token, splitChar);
        if (token.size() > 0) {
            return std::stoi(token);
        }

        return {};
    };

    for (int i = 0; i < 3; i++) {
        const auto vertexIndex = parseFaceToken(lineStream, '/');
        if (vertexIndex.has_value()) {
            objData->vertexIndices.push_back(vertexIndex.value() - 1);
        }

        const auto texCoordIndex = parseFaceToken(lineStream, '/');
        if (texCoordIndex.has_value()) {
            // TODO
        }

        const auto normalIndex = parseFaceToken(lineStream, ' ');
        if (normalIndex.has_value()) {
            objData->normalIndices.push_back(normalIndex.value() - 1);
        }
    }
}

Obj load(std::ifstream &ifstream)
{
    ObjData objData = {};
    {   // ParseObj
        static std::unordered_map<std::string, ParseFunction> parseMap = {
            {"v", parseVertex},
            {"vn", parseNormals},
            {"f", parseFaces}
        };

        objData.vertices.reserve(k_vectorReserveSize);
        objData.normals.reserve(k_vectorReserveSize);

        objData.vertexIndices.reserve(k_vectorReserveSize);
        objData.normalIndices.reserve(k_vectorReserveSize);

        std::string line;
        while (std::getline(ifstream, line)) {
            std::string token;
            auto lineStream = std::stringstream(line);
            lineStream >> token;
            if (parseMap.find(token) != parseMap.end()) {
                parseMap[token](lineStream, &objData);
            }
        }
    }

    Obj obj = {};
    { // CreateObj
        obj.vertices.reserve(objData.vertexIndices.size());
        for (uint16_t i : objData.vertexIndices) {
            obj.vertices.push_back(objData.vertices[i]);
        }

        obj.normals.reserve(objData.normalIndices.size());
        for (uint16_t i : objData.normalIndices) {
            obj.normals.push_back(objData.normals[i]);
        }
    }

    return obj;
}

}
