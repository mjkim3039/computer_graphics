#include "shader.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdio>

// 파일을 열어 전체 내용을 문자열로 반환
static std::string readAll(const std::string& p){
    std::ifstream f(p, std::ios::binary);
    std::stringstream s; s << f.rdbuf(); return s.str();
}

// shader / program의 컴파일/링크 상태 검사
static bool check(GLuint obj, bool program){
    GLint ok {};
    if(program){ glGetProgramiv(obj, GL_LINK_STATUS, &ok); }
    else{ glGetShaderiv(obj, GL_COMPILE_STATUS, &ok); }
    if(!ok){
        GLint len {};
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

// shader 준비
bool Shader::loadFromFiles(const std::string& vsp, const std::string& fsp){
    // GLSL 코드 준비
    auto vsSrc { readAll(vsp) };
    auto fsSrc { readAll(fsp) };
    const char* v { vsSrc.c_str() };
    const char* f { fsSrc.c_str() };

    // vertex shader 객체 생성 -> GPU에서 컴파일
    GLuint vs { glCreateShader(GL_VERTEX_SHADER) };
    glShaderSource(vs, 1, &v, nullptr);
    glCompileShader(vs);
    if(!check(vs, false)) return false;

    // fragment shader 객체 생성 -> GPU에서 컴파일
    GLuint fs { glCreateShader(GL_FRAGMENT_SHADER) };
    glShaderSource(fs, 1, &f, nullptr);
    glCompileShader(fs);
    if(!check(fs, false)) return false;

    // 두 프로그램을 하나의 프로그램으로 link
    id = glCreateProgram();
    glAttachShader(id, vs);
    glAttachShader(id, fs);
    glLinkProgram(id);
    glDeleteShader(vs);
    glDeleteShader(fs);
    if(!check(id, true)) return false;

    return true;
}
