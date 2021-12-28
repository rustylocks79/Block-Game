#include "Chunk.h"

using namespace std;
using namespace glm;

Vertex::Vertex(const vec3 &position, const vec2 &uv, int layer) : position(position), uv(uv), layer(layer) {}

Chunk::Chunk() {
    vertices = new vector<Vertex>();
    indices = new vector<unsigned int>();
    blockData = new unsigned int[LENGTH_X * LENGTH_Y * LENGTH_Z];
    for(int i = 0; i < LENGTH_X * LENGTH_Y * LENGTH_Z; i++) {
        blockData[i] = 0;
    }
    SetBlockAtPos(0, 0, 0, 1);
    SetBlockAtPos(1, 0, 0, 1);
    SetBlockAtPos(0, 0, 1, 1);
    SetBlockAtPos(1, 0, 1, 1);
    BuildMesh();

    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glGenBuffers(1, &_ebo);

    glBindVertexArray(_vao);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices->size() * sizeof(Vertex), &(*vertices)[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size() * sizeof(unsigned int), &(*indices)[0], GL_STATIC_DRAW);

    int stride = sizeof(Vertex);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 1, GL_INT, GL_FALSE, stride, (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Chunk::~Chunk() {
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_ebo);
    delete vertices;
    delete indices;
}

void Chunk::Render() const {
    glBindVertexArray(_vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glDrawElements(GL_TRIANGLES, indices->size(), GL_UNSIGNED_INT, nullptr);
}

void Chunk::SetBlockAtPos(int x, int y, int z, unsigned int block) {
    blockData[(y * LENGTH_X * LENGTH_Z) + (z * LENGTH_X) + x] = block;
}

unsigned int Chunk::GetBlockAtPos(int x, int y, int z) const {
    return blockData[(y * LENGTH_X * LENGTH_Z) + (z * LENGTH_X) + x];
}

unsigned int Chunk::GetBlockAtPos(int x, int y, int z, Direction direction) const {
    //TODO: handle chunk boundaries.
    switch (direction) {
        case NORTH:
            z++;
            if(z >= LENGTH_Z) {
                return 0;
            }
            break;
        case EAST:
            x++;
            if(x >= LENGTH_X) {
                return 0;
            }
            break;
        case SOUTH:
            z--;
            if(z < 0) {
                return 0;
            }
            break;
        case WEST:
            x--;
            if(x < 0) {
                return 0;
            }
            break;
        case UP:
            y++;
            if(y >= LENGTH_Y) {
                return 0;
            }
            break;
        case DOWN:
            y--;
            if(y < 0) {
                return 0;
            }
            break;
    }
    return blockData[(y * LENGTH_X * LENGTH_Z) + (z * LENGTH_X) + x];
}

void Chunk::BuildMesh() {
    int cubes = 0;
    for(int y = 0; y < LENGTH_Y; y++) {
        for(int z = 0; z < LENGTH_Z; z++) {
            for(int x = 0; x < LENGTH_X; x++) {
                if(GetBlockAtPos(x, y, z) != 0) {
                    AddCube(vec3(x, y, z));
                    cubes++;
                }
            }
        }
    }
    cout << cubes << endl;
}

void Chunk::AddCube(glm::vec3 blockPos) {
    if(GetBlockAtPos(blockPos.x, blockPos.y, blockPos.z, NORTH) == 0) {
        AddFace(blockPos, NORTH, 0);
    }
    if(GetBlockAtPos(blockPos.x, blockPos.y, blockPos.z, EAST) == 0) {
        AddFace(blockPos, EAST, 0);
    }
    if(GetBlockAtPos(blockPos.x, blockPos.y, blockPos.z, SOUTH) == 0) {
        AddFace(blockPos, SOUTH, 0);
    }
    if(GetBlockAtPos(blockPos.x, blockPos.y, blockPos.z, WEST) == 0) {
        AddFace(blockPos, WEST, 0);
    }
    if(GetBlockAtPos(blockPos.x, blockPos.y, blockPos.z, UP) == 0) {
        AddFace(blockPos, UP, 1);
    }
    if(GetBlockAtPos(blockPos.x, blockPos.y, blockPos.z, DOWN) == 0) {
        AddFace(blockPos, DOWN, 0);
    }
}
    
void Chunk::AddFace(glm::vec3 blockPos, Direction direction, int texture) {
    switch (direction) {
        case NORTH:
            vertices->emplace_back(vec3(blockPos.x - 0.5f, blockPos.y - 0.5f,  blockPos.z + 0.5f), vec2(0.0f, 0.0f), texture);
            vertices->emplace_back(vec3(blockPos.x + 0.5f, blockPos.y - 0.5f,  blockPos.z + 0.5f),  vec2(1.0f, 0.0f), texture);
            vertices->emplace_back(vec3(blockPos.x + 0.5f, blockPos.y + 0.5f,  blockPos.z + 0.5f),  vec2(1.0f, 1.0f), texture);
            vertices->emplace_back(vec3(blockPos.x - 0.5f, blockPos.y + 0.5f,  blockPos.z + 0.5f), vec2(0.0f, 1.0f), texture);
            break;
        case EAST:
            vertices->emplace_back(vec3(blockPos.x + 0.5f, blockPos.y + 0.5f, blockPos.z + 0.5f),  vec2(1.0f, 0.0f), texture);
            vertices->emplace_back(vec3(blockPos.x + 0.5f, blockPos.y + 0.5f, blockPos.z - 0.5f),  vec2(1.0f, 1.0f), texture);
            vertices->emplace_back(vec3(blockPos.x + 0.5f, blockPos.y - 0.5f, blockPos.z - 0.5f),  vec2(0.0f, 1.0f), texture);
            vertices->emplace_back(vec3(blockPos.x + 0.5f, blockPos.y - 0.5f, blockPos.z + 0.5f),  vec2(0.0f, 0.0f), texture);
            break;
        case SOUTH:
            vertices->emplace_back(vec3(blockPos.x - 0.5f, blockPos.y - 0.5f, blockPos.z - 0.5f), vec2(0.0f, 0.0f), texture);
            vertices->emplace_back(vec3(blockPos.x + 0.5f, blockPos.y - 0.5f, blockPos.z - 0.5f),  vec2(1.0f, 0.0f), texture);
            vertices->emplace_back(vec3(blockPos.x + 0.5f, blockPos.y + 0.5f, blockPos.z - 0.5f),  vec2(1.0f, 1.0f), texture);
            vertices->emplace_back(vec3(blockPos.x - 0.5f, blockPos.y + 0.5f, blockPos.z - 0.5f), vec2(0.0f, 1.0f), texture);
            break;
        case WEST:
            vertices->emplace_back(vec3(blockPos.x - 0.5f, blockPos.y + 0.5f, blockPos.z + 0.5f), vec2(1.0f, 0.0f), texture);
            vertices->emplace_back(vec3(blockPos.x - 0.5f, blockPos.y + 0.5f, blockPos.z - 0.5f), vec2(1.0f, 1.0f), texture);
            vertices->emplace_back(vec3(blockPos.x - 0.5f, blockPos.y - 0.5f, blockPos.z - 0.5f), vec2(0.0f, 1.0f), texture);
            vertices->emplace_back(vec3(blockPos.x - 0.5f, blockPos.y - 0.5f, blockPos.z + 0.5f), vec2(0.0f, 0.0f), texture);
            break;
        case UP:
            vertices->emplace_back(vec3(blockPos.x - 0.5f, blockPos.y + 0.5f, blockPos.z - 0.5f), vec2(0.0f, 1.0f), texture);
            vertices->emplace_back(vec3(blockPos.x + 0.5f, blockPos.y + 0.5f, blockPos.z - 0.5f),  vec2(1.0f, 1.0f), texture);
            vertices->emplace_back(vec3(blockPos.x + 0.5f, blockPos.y + 0.5f, blockPos.z + 0.5f),  vec2(1.0f, 0.0f), texture);
            vertices->emplace_back(vec3(blockPos.x - 0.5f, blockPos.y + 0.5f, blockPos.z + 0.5f), vec2(0.0f, 0.0f), texture);
            break;
        case DOWN:
            vertices->emplace_back(vec3(blockPos.x - 0.5f, blockPos.y - 0.5f, blockPos.z - 0.5f), vec2(0.0f, 1.0f), texture);
            vertices->emplace_back(vec3(blockPos.x + 0.5f, blockPos.y - 0.5f, blockPos.z - 0.5f),  vec2(1.0f, 1.0f), texture);
            vertices->emplace_back(vec3(blockPos.x + 0.5f, blockPos.y - 0.5f, blockPos.z + 0.5f),  vec2(1.0f, 0.0f), texture);
            vertices->emplace_back(vec3(blockPos.x - 0.5f, blockPos.y - 0.5f, blockPos.z + 0.5f), vec2(0.0f, 0.0f), texture);
            break;
    }

    unsigned int start = faces * 4;
    indices->push_back(start);
    indices->push_back(start + 1);
    indices->push_back(start + 2);
    indices->push_back(start + 2);
    indices->push_back(start + 3);
    indices->push_back(start);

    faces+=1;
}
