cmake_minimum_required(VERSION 3.21)
project(GraphicsProjects LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
  add_compile_options(/utf-8)
endif()

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_executable(app
    src/main.cpp
    src/shader.cpp
    src/renderer.cpp
)

target_compile_definitions(app PRIVATE GLFW_INCLUDE_NONE)

if (WIN32)
  target_link_libraries(app PRIVATE glfw glad::glad opengl32)
else()
  target_link_libraries(app PRIVATE glfw glad::glad)
endif()

# 셰이더 복사
add_custom_command(TARGET app POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${CMAKE_SOURCE_DIR}/assets
          $<TARGET_FILE_DIR:app>/assets)
