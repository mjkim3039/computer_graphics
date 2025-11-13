#include <cstdio>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "renderer.hpp"

// error callback
static void glfw_error_callback(int code, const char* desc){
    std::fprintf(stderr, "GLFW error %d: %s\n", code, desc);
}

int main(){
    glfwSetErrorCallback(glfw_error_callback);
    if(!glfwInit()) return -1;

    // OpenGL 3.3 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* win { glfwCreateWindow(1024, 768, "HelloRectangle", nullptr, nullptr) };
    if(!win){ glfwTerminate(); return -1; }
    glfwMakeContextCurrent(win);
    glfwSwapInterval(1);    //VSync 활성화

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::fprintf(stderr, "Failed to load OpenGL\n");
        return -1;
    }

    Renderer r;
    if(!r.init()){ std::fprintf(stderr, "Renderer init failed\n"); return -1; }

    while(!glfwWindowShouldClose(win)){
        if(glfwGetKey(win, GLFW_KEY_ESCAPE)==GLFW_PRESS) glfwSetWindowShouldClose(win, 1);
        int w, h; 
        glfwGetFramebufferSize(win, &w, &h);
        r.draw(w, h);
        glfwSwapBuffers(win);
        glfwPollEvents();
    }
    r.shutdown();
    glfwDestroyWindow(win);
    glfwTerminate();
    return 0;
}
