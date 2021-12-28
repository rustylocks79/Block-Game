
#include "Chunk.h"

using namespace std;
using namespace glm;

Chunk::Chunk() {
    vertices = new vector<Vertex>();
    indices = new vector<unsigned int>();
    AddCube(vec3(0.0f, 0.0f, 0.0f));

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
}

void Chunk::render() const {
    glBindVertexArray(_vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glDrawElements(GL_TRIANGLES, indices->size(), GL_UNSIGNED_INT, nullptr);
}

void Chunk::AddCube(glm::vec3 center) {
    //back
    vertices->emplace_back(vec3(-0.5f, -0.5f, -0.5f), vec2(0.0f, 0.0f), 0);
    vertices->emplace_back(vec3(0.5f, -0.5f, -0.5f),  vec2(1.0f, 0.0f), 0);
    vertices->emplace_back(vec3(0.5f,  0.5f, -0.5f),  vec2(1.0f, 1.0f), 0);
//    vertices.emplace_back(vec3(0.5f,  0.5f, -0.5f),  vec2(1.0f, 1.0f), 0);
    vertices->emplace_back(vec3(-0.5f,  0.5f, -0.5f), vec2(0.0f, 1.0f), 0);
//    vertices.emplace_back(vec3(-0.5f, -0.5f, -0.5f), vec2(0.0f, 0.0f), 0);

    //front
    vertices->emplace_back(vec3(-0.5f, -0.5f,  0.5f), vec2(0.0f, 0.0f), 0);
    vertices->emplace_back(vec3(0.5f, -0.5f,  0.5f),  vec2(1.0f, 0.0f), 0);
    vertices->emplace_back(vec3(0.5f,  0.5f,  0.5f),  vec2(1.0f, 1.0f), 0);
//    vertices.emplace_back(vec3(0.5f,  0.5f,  0.5f),  vec2(1.0f, 1.0f), 0);
    vertices->emplace_back(vec3(-0.5f,  0.5f,  0.5f), vec2(0.0f, 1.0f), 0);
//    vertices.emplace_back(vec3(-0.5f, -0.5f,  0.5f), vec2(0.0f, 0.0f), 0);

    //left
    vertices->emplace_back(vec3(-0.5f,  0.5f,  0.5f), vec2(1.0f, 0.0f), 0);
    vertices->emplace_back(vec3(-0.5f,  0.5f, -0.5f), vec2(1.0f, 1.0f), 0);
    vertices->emplace_back(vec3(-0.5f, -0.5f, -0.5f), vec2(0.0f, 1.0f), 0);
//    vertices.emplace_back(vec3(-0.5f, -0.5f, -0.5f), vec2(0.0f, 1.0f), 0);
    vertices->emplace_back(vec3(-0.5f, -0.5f,  0.5f), vec2(0.0f, 0.0f), 0);
//    vertices.emplace_back(vec3(-0.5f,  0.5f,  0.5f), vec2(1.0f, 0.0f), 0);

    //right
    vertices->emplace_back(vec3(0.5f,  0.5f,  0.5f),  vec2(1.0f, 0.0f), 0);
    vertices->emplace_back(vec3(0.5f,  0.5f, -0.5f),  vec2(1.0f, 1.0f), 0);
    vertices->emplace_back(vec3(0.5f, -0.5f, -0.5f),  vec2(0.0f, 1.0f), 0);
//    vertices.emplace_back(vec3(0.5f, -0.5f, -0.5f),  vec2(0.0f, 1.0f), 0);
    vertices->emplace_back(vec3(0.5f, -0.5f,  0.5f),  vec2(0.0f, 0.0f), 0);
//    vertices.emplace_back(vec3(0.5f,  0.5f,  0.5f),  vec2(1.0f, 0.0f), 0);

    //down
    vertices->emplace_back(vec3(-0.5f, -0.5f, -0.5f), vec2(0.0f, 1.0f), 0);
    vertices->emplace_back(vec3(0.5f, -0.5f, -0.5f),  vec2(1.0f, 1.0f), 0);
    vertices->emplace_back(vec3(0.5f, -0.5f,  0.5f),  vec2(1.0f, 0.0f), 0);
//    vertices.emplace_back(vec3(0.5f, -0.5f,  0.5f),  vec2(1.0f, 0.0f), 0);
    vertices->emplace_back(vec3(-0.5f, -0.5f,  0.5f), vec2(0.0f, 0.0f), 0);
//    vertices.emplace_back(vec3(-0.5f, -0.5f, -0.5f), vec2(0.0f, 1.0f), 0);

    //up
    vertices->emplace_back(vec3(-0.5f,  0.5f, -0.5f), vec2(0.0f, 1.0f), 1);
    vertices->emplace_back(vec3(0.5f,  0.5f, -0.5f),  vec2(1.0f, 1.0f), 1);
    vertices->emplace_back(vec3(0.5f,  0.5f,  0.5f),  vec2(1.0f, 0.0f), 1);
//    vertices.emplace_back(vec3(0.5f,  0.5f,  0.5f),  vec2(1.0f, 0.0f), 1);
    vertices->emplace_back(vec3(-0.5f,  0.5f,  0.5f), vec2(0.0f, 0.0f), 1);
//    vertices.emplace_back(vec3(-0.5f,  0.5f, -0.5f), vec2(0.0f, 1.0f), 1);

    for(int i = 0; i < 6; i++) {
        unsigned int start = i * 4;
        indices->push_back(start);
        indices->push_back(start + 1);
        indices->push_back(start + 2);
        indices->push_back(start + 2);
        indices->push_back(start + 3);
        indices->push_back(start);
    }
}

Vertex::Vertex(const vec3 &position, const vec2 &uv, int layer) : position(position), uv(uv), layer(layer) {}
