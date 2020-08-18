cmake_minimum_required(VERSION 3.10)

add_subdirectory(lib)

project(CoffeeShader VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(SEND_ERROR "In-source builds are not allowed.")
endif ()

file(GLOB_RECURSE SRC src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC})

set (CMAKE_CXX_STANDARD 17)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set(COMPILE_OPTIONS ${COMPILE_OPTIONS} "-Werror")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(COMPILE_OPTIONS ${COMPILE_OPTIONS} "/Wall")
else()
    message(FATAL_ERROR "${PROJECT_NAME} is not compatible with the ${CMAKE_CXX_COMPILER_ID} compiler.")
endif()

target_link_libraries(${PROJECT_NAME} glfw glad imgui osdialog)
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTIONS})

if (CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(${PROJECT_NAME} PUBLIC DEBUG)
    target_compile_options(${PROJECT_NAME} PRIVATE -g)
elseif (CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_options(${PROJECT_NAME} PRIVATE -O3)
endif ()