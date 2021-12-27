#pragma once
#include "glad/glad.h"
#include "string"
#include "fstream"
#include "sstream"
#include "iostream"

//TODO: cache uniforms, load files separately, more uniform types
class Shader {
private:
    int _id;

public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();
    void Use() const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
};
