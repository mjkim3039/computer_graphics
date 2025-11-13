#pragma once
#include "shader.hpp"

struct Renderer {
    unsigned vao = 0, vbo = 0;
    Shader shader;
    void draw();
};
