#include "renderer.hpp"
#include <glad/glad.h>

void Renderer::draw(void) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // 초기화할 색을 설정
    glClear(GL_COLOR_BUFFER_BIT);           // color buffer를 설정한 색으로 채움
}