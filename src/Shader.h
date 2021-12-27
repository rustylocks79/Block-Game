#pragma once
#include "glad/glad.h"
#include "string"
#include "fstream"
#include "sstream"
#include "iostream"
#include "fwd.hpp"

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
    void SetMat4(const std::string& name, const glm::mat4& value) const;
};
