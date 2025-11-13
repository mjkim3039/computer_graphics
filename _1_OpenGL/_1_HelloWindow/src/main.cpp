#include <cstdio>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "renderer.hpp"

// error callback
static void glfw_error_callback(int code, const char* desc){
    std::fprintf(stderr, "GLFW error %d: %s\n", code, desc);
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Get input
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) { glfwSetWindowShouldClose(window, true); }
}

int main(){
    if(!glfwInit()) return -1;

    // OpenGL 3.3 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindwoHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TURE)

    GLFWwindow* win { glfwCreateWindow(1024, 768, "Hello Window", nullptr, nullptr) };
    if(!win){ glfwTerminate(); return -1; }
    glfwMakeContextCurrent(win);
    glfwSwapInterval(1);    //VSync 활성화

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::fprintf(stderr, "Failed to load OpenGL\n");
        return -1;
    }
    glfwSetErrorCallback(glfw_error_callback);
    glfwSetFramebufferSizeCallback(win, framebuffer_size_callback);

    Renderer r;

    while(!glfwWindowShouldClose(win)){
        processInput(win);

        // rendering commands here
        r.draw();

        glfwSwapBuffers(win);   // swap color buffer, show it as output to screen
        glfwPollEvents();       // checks if any events are triggered, updates window states
    }
    glfwDestroyWindow(win);
    glfwTerminate();
    return 0;
}
