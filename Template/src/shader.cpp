#include "shader.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdio>

static std::string readAll(const std::string& p){
    std::ifstream f(p, std::ios::binary);
    std::stringstream s; s << f.rdbuf(); return s.str();
}
static bool check(GLuint obj, bool program){
    GLint ok = 0;
    if(program){ glGetProgramiv(obj, GL_LINK_STATUS, &ok); }
    else{ glGetShaderiv(obj, GL_COMPILE_STATUS, &ok); }
    if(!ok){
        GLint len=0;
        if(program){ glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &len); }
        else{ glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &len); }
        std::vector<char> log(len);
        if(program){ glGetProgramInfoLog(obj, len, nullptr, log.data()); }
        else{ glGetShaderInfoLog(obj, len, nullptr, log.data()); }
        std::fprintf(stderr, "%s\n", log.data());
        return false;
    }
    return true;
}

bool Shader::loadFromFiles(const std::string& vsp, const std::string& fsp){
    auto vsSrc = readAll(vsp);
    auto fsSrc = readAll(fsp);
    const char* v = vsSrc.c_str();
    const char* f = fsSrc.c_str();

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &v, nullptr);
    glCompileShader(vs);
    if(!check(vs, false)) return false;

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &f, nullptr);
    glCompileShader(fs);
    if(!check(fs, false)) return false;

    id = glCreateProgram();
    glAttachShader(id, vs);
    glAttachShader(id, fs);
    glLinkProgram(id);
    glDeleteShader(vs);
    glDeleteShader(fs);
    if(!check(id, true)) return false;

    return true;
}
