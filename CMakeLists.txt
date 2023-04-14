cmake_minimum_required (VERSION 3.25)

set(PROJECT_NAME "pur")
set(CMAKE_CXX_STANDARD 20)
set(EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/external/vcpkg/scripts/buildsystems/vcpkg.cmake"
      CACHE STRING "")
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

project(${PROJECT_NAME})

find_package(SDL2 CONFIG REQUIRED)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/main.cpp)

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)

