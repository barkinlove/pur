cmake_minimum_required (VERSION 3.25)

set(PROJECT_NAME "pur")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/external/vcpkg/scripts/buildsystems/vcpkg.cmake"
      CACHE STRING "")
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
set(CONFIG_FILE "config.json")

project(${PROJECT_NAME})

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

if (NOT EXISTS "${PROJECT_SOURCE_DIR}/build/${CONFIG_FILE}")
  file(WRITE "build/${CONFIG_FILE}" "{}")
endif()


add_executable(${PROJECT_NAME} 
  ${PROJECT_SOURCE_DIR}/src/main.cpp
  ${PROJECT_SOURCE_DIR}/src/Target.cpp
  ${PROJECT_SOURCE_DIR}/src/Actor.cpp
  ${PROJECT_SOURCE_DIR}/src/Color.cpp
  ${PROJECT_SOURCE_DIR}/src/Window.cpp
  ${PROJECT_SOURCE_DIR}/src/Game.cpp
  ${PROJECT_SOURCE_DIR}/src/Config.cpp
  ${PROJECT_SOURCE_DIR}/src/CollisionSystem.cpp
  )

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/build/vcpkg_installed/x64-windows/include")

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-network sfml-graphics sfml-window)
