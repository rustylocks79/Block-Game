#pragma once
#include <vector>
#include <iostream>

#include "glad/glad.h"
#include "vec3.hpp"
#include "vec2.hpp"

struct Vertex {
    glm::vec3 position;
    glm::vec2 uv;
    int layer;

    Vertex(const glm::vec3 &position, const glm::vec2 &uv, int layer);
};

class Chunk {
private:
    unsigned int _vao, _vbo, _ebo;
    std::vector<Vertex>* vertices;
    std::vector<unsigned int>* indices;
    void AddCube(glm::vec3 center);
public:
    Chunk();
    ~Chunk();
    void render() const;
};
