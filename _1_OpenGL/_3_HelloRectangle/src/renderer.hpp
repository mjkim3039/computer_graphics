#pragma once
#include "shader.hpp"

struct Renderer {
    unsigned vao = 0, vbo = 0;
    Shader shader;
    bool init();
    void draw(int w, int h);
    void shutdown();
};
