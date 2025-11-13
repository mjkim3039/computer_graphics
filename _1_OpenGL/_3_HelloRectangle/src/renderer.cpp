#include "renderer.hpp"
#include <glad/glad.h>

// GPU memory에 vertex data upload + shader program load
bool Renderer::init(){
    // 사각형
    float rect[18] = {
        -.5f, -.5f, .0f,
        .5f, -.5f, .0f,
        -.5f, .5f, .0f,

        -.5f, .5f, .0f,
        .5f, -.5f, .0f,
        .5f, .5f, .0f,
    };

    // VAO 생성 및 바인딩
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // VBO 생성 및 data를 GPU VRAM에 복사
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);

    // vertex 속성 index 0번을 활성화
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
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Renderer::shutdown(){
    if(vbo) glDeleteBuffers(1, &vbo);
    if(vao) glDeleteVertexArrays(1, &vao);
}
