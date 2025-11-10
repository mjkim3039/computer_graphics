#include "renderer.hpp"
#include <glad/glad.h>

bool Renderer::init(){
    // 삼각형
    float tri[9] = {
        -0.5f,-0.5f,0.f,
         0.5f,-0.5f,0.f,
         0.0f, 0.5f,0.f
    };
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tri), tri, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 3*sizeof(float), (void*)0);

    if(!shader.loadFromFiles("assets/shaders/tri.vert", "assets/shaders/tri.frag"))
        return false;
    return true;
}

void Renderer::draw(int w, int h){
    glViewport(0, 0, w, h);
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    shader.use();
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Renderer::shutdown(){
    if(vbo) glDeleteBuffers(1, &vbo);
    if(vao) glDeleteVertexArrays(1, &vao);
}
