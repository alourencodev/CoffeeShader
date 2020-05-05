cmake_minimum_required(VERSION 3.10)

add_subdirectory(lib)

project(CoffeeShader VERSION 0.1.0 LANGUAGES CXX)

find_package(glfw3 3.2 REQUIRED)
find_package(glm REQUIRED)

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(COMPILE_OPTIONS "-Werror")
set(COMPILE_FEATURES "cxx_std_17")

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(SEND_ERROR "In-source builds are not allowed.")
endif ()

file(GLOB_RECURSE SRC src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} glfw glad glm imgui osdialog)
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTIONS})
target_compile_features(${PROJECT_NAME} PRIVATE ${COMPILE_FEATURES})

if (CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(${PROJECT_NAME} PUBLIC DEBUG)
    target_compile_options(${PROJECT_NAME} PRIVATE -g)
elseif (CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_options(${PROJECT_NAME} PRIVATE -O3)
endif ()