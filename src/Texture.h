#pragma once

#include "glad/glad.h"
#include <iostream>

class Texture {
private:
    unsigned int _id{};

public:
    Texture(const char* filePath);
    ~Texture();
    void Use() const;
};
