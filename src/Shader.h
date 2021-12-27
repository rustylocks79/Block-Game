#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

#include "glad/glad.h"
#include "fwd.hpp"
#include "gtc/type_ptr.hpp"

//TODO: cache uniforms, load files separately, more uniform types
class Shader {
private:
    int _id;
    std::map<std::string, int> _uniformCache;

    int FindUniform(const std::string& name);
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();
    void Use() const;
    void SetInt(const std::string& name, int value);
    void SetFloat(const std::string& name, float value);
    void SetMat4(const std::string& name, const glm::mat4& value);
};
