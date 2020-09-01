cmake_minimum_required(VERSION 3.10)

project(CoffeeShader VERSION 0.1.0 LANGUAGES CXX)

add_subdirectory(lib)

if (UNIX)
    set(GL_LIB "gl")
elseif (WIN32)
    find_package(OpenGL REQUIRED)
    set(GL_LIB "opengl32")
endif()


set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED)

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(SEND_ERROR "In-source builds are not allowed.")
endif ()

file(GLOB_RECURSE SRC src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC})

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set(COMPILE_OPTIONS ${COMPILE_OPTIONS} "-Werror")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
else()
    message(FATAL_ERROR "${PROJECT_NAME} is not compatible with the ${CMAKE_CXX_COMPILER_ID} compiler.")
endif()

target_link_libraries(${PROJECT_NAME} glfw glad imgui osdialog ${GL_LIB} glm)
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTIONS})

if (CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(${PROJECT_NAME} PUBLIC DEBUG)
    target_compile_options(${PROJECT_NAME} PRIVATE -g)
elseif (CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_options(${PROJECT_NAME} PRIVATE -O3)
endif ()