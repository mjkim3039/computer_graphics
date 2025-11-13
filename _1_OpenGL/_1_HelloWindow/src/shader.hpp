#pragma once
#include <string>
#include <glad/glad.h>

struct Shader {
    unsigned id {};
    bool loadFromFiles(const std::string& vsPath, const std::string& fsPath);
    void use() const { glUseProgram(id); }
};