#pragma once
#include <vector>

#include "glad/glad.h"
#include "vec3.hpp"
#include "vec2.hpp"

struct Vertex {
    glm::vec3 position;
    glm::vec2 uv;

    Vertex(const glm::vec3 &position, const glm::vec2 &uv) : position(position), uv(uv) {}
};

class Chunk {
private:
    unsigned int _vao, _vbo;
    std::vector<Vertex> vertices;

    void AddCube(glm::vec3 center);
public:
    Chunk();
    ~Chunk();
    void render() const;
};
