#pragma once
#include <vector>
#include <iostream>
#include <algorithm>

#include "glad/glad.h"
#include "vec3.hpp"
#include "vec2.hpp"

#define LENGTH_X 16
#define LENGTH_Y 16
#define LENGTH_Z 16

struct Vertex {
    glm::vec3 position;
    glm::vec2 uv;
    int layer;

    Vertex(const glm::vec3 &position, const glm::vec2 &uv, int layer);
};

enum Direction {
    NORTH, EAST, SOUTH, WEST, UP, DOWN
};

class Chunk {
private:
    unsigned int _vao{}, _vbo{}, _ebo{}, faces = 0;
    std::vector<Vertex>* vertices;
    std::vector<unsigned int>* indices;
    unsigned int* blockData;

    void SetBlockAtPos(int x, int y, int z, unsigned int block);
    unsigned int GetBlockAtPos(int x, int y, int z) const;
    unsigned int GetBlockAtPos(int x, int y, int z, Direction direction) const;

    void BuildMesh();
    void AddCube(glm::vec3 blockPos);
    void AddFace(glm::vec3 blockPos, Direction direction, int texture);
public:
    Chunk();
    ~Chunk();
    void Render() const;
};
