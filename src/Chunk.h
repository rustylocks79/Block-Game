#pragma once
#include "glad/glad.h"

class Chunk {
private:
    unsigned int _vao, _vbo;
public:
    Chunk();
    ~Chunk();
    void render() const;
};
