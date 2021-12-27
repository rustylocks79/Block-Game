#include "Shader.h"

using namespace std;
using namespace glm;

Shader::Shader(const char *vertexPath, const char *fragmentPath) {
    // 1. retrieve the vertex source code from filePath
    string vertexCode;
    ifstream vShaderFile;
    vShaderFile.exceptions (ifstream::failbit | ifstream::badbit);
    try {
        vShaderFile.open(vertexPath);
        stringstream vShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        vShaderFile.close();
        vertexCode = vShaderStream.str();
    } catch(ifstream::failure& e) {
        cout << "ERROR::SHADER::VERTEX_FILE_NOT_SUCCESSFULLY_READ" << endl;
    }
    const char* vShaderCode = vertexCode.c_str();

    // 1. retrieve the fragment source code from filePath
    string fragmentCode;
    ifstream fShaderFile;
    fShaderFile.exceptions (ifstream::failbit | ifstream::badbit);
    try {
        fShaderFile.open(fragmentPath);
        stringstream fShaderStream;
        fShaderStream << fShaderFile.rdbuf();
        fShaderFile.close();
        fragmentCode = fShaderStream.str();
    } catch(ifstream::failure& e) {
        cout << "ERROR::SHADER::FRAGMENT_FILE_NOT_SUCCESSFULLY_READ" << endl;
    }
    const char* fShaderCode = fragmentCode.c_str();

    // 3. compile shaders
    int success;
    char infoLog[512];

    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
    };

    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
    };

    //4. Link Shaders
    _id = glCreateProgram();
    glAttachShader(_id, vertex);
    glAttachShader(_id, fragment);
    glLinkProgram(_id);
    glGetProgramiv(_id, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(_id, 512, nullptr, infoLog);
        cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() {
    glDeleteProgram(_id);
}

void Shader::Use() const {
    glUseProgram(_id);
}

void Shader::SetInt(const string &name, int value) {
    glUniform1i(FindUniform(name), value);
}

void Shader::SetFloat(const string &name, float value) {
    glUniform1f(FindUniform(name), value);
}

void Shader::SetMat4(const string &name, const mat4 &value) {
    glUniformMatrix4fv(FindUniform(name), 1, GL_FALSE, value_ptr(value));
}

int Shader::FindUniform(const string &name) {
    if(_uniformCache.find(name) != _uniformCache.end()) {
        return _uniformCache[name];
    } else {
        int result = glGetUniformLocation(_id, name.c_str());
        _uniformCache[name] = result;
        return result;
    }
}