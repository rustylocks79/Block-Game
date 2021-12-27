#include "Chunk.h"

using namespace std;
using namespace glm;

Chunk::Chunk() {
    vertices = vector<Vertex>();
    AddCube(vec3(0.0f, 0.0f, 0.0f));

    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glBindVertexArray(_vao);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    int stride = sizeof(Vertex);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Chunk::~Chunk() {
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);
}

void Chunk::render() const {
    glBindVertexArray(_vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Chunk::AddCube(vec3 center) {
    vertices.emplace_back(vec3(-0.5f, -0.5f, -0.5f), vec2(0.0f, 0.0f));
    vertices.emplace_back(vec3(0.5f, -0.5f, -0.5f),  vec2(1.0f, 0.0f));
    vertices.emplace_back(vec3(0.5f,  0.5f, -0.5f),  vec2(1.0f, 1.0f));
    vertices.emplace_back(vec3(0.5f,  0.5f, -0.5f),  vec2(1.0f, 1.0f));
    vertices.emplace_back(vec3(-0.5f,  0.5f, -0.5f), vec2(0.0f, 1.0f));
    vertices.emplace_back(vec3(-0.5f, -0.5f, -0.5f), vec2(0.0f, 0.0f));

    vertices.emplace_back(vec3(-0.5f, -0.5f,  0.5f), vec2(0.0f, 0.0f));
    vertices.emplace_back(vec3(0.5f, -0.5f,  0.5f),  vec2(1.0f, 0.0f));
    vertices.emplace_back(vec3(0.5f,  0.5f,  0.5f),  vec2(1.0f, 1.0f));
    vertices.emplace_back(vec3(0.5f,  0.5f,  0.5f),  vec2(1.0f, 1.0f));
    vertices.emplace_back(vec3(-0.5f,  0.5f,  0.5f), vec2(0.0f, 1.0f));
    vertices.emplace_back(vec3(-0.5f, -0.5f,  0.5f), vec2(0.0f, 0.0f));

    vertices.emplace_back(vec3(-0.5f,  0.5f,  0.5f), vec2(1.0f, 0.0f));
    vertices.emplace_back(vec3(-0.5f,  0.5f, -0.5f), vec2(1.0f, 1.0f));
    vertices.emplace_back(vec3(-0.5f, -0.5f, -0.5f), vec2(0.0f, 1.0f));
    vertices.emplace_back(vec3(-0.5f, -0.5f, -0.5f), vec2(0.0f, 1.0f));
    vertices.emplace_back(vec3(-0.5f, -0.5f,  0.5f), vec2(0.0f, 0.0f));
    vertices.emplace_back(vec3(-0.5f,  0.5f,  0.5f), vec2(1.0f, 0.0f));

    vertices.emplace_back(vec3(0.5f,  0.5f,  0.5f),  vec2(1.0f, 0.0f));
    vertices.emplace_back(vec3(0.5f,  0.5f, -0.5f),  vec2(1.0f, 1.0f));
    vertices.emplace_back(vec3(0.5f, -0.5f, -0.5f),  vec2(0.0f, 1.0f));
    vertices.emplace_back(vec3(0.5f, -0.5f, -0.5f),  vec2(0.0f, 1.0f));
    vertices.emplace_back(vec3(0.5f, -0.5f,  0.5f),  vec2(0.0f, 0.0f));
    vertices.emplace_back(vec3(0.5f,  0.5f,  0.5f),  vec2(1.0f, 0.0f));

    vertices.emplace_back(vec3(-0.5f, -0.5f, -0.5f), vec2(0.0f, 1.0f));
    vertices.emplace_back(vec3(0.5f, -0.5f, -0.5f),  vec2(1.0f, 1.0f));
    vertices.emplace_back(vec3(0.5f, -0.5f,  0.5f),  vec2(1.0f, 0.0f));
    vertices.emplace_back(vec3(0.5f, -0.5f,  0.5f),  vec2(1.0f, 0.0f));
    vertices.emplace_back(vec3(-0.5f, -0.5f,  0.5f), vec2(0.0f, 0.0f));
    vertices.emplace_back(vec3(-0.5f, -0.5f, -0.5f), vec2(0.0f, 1.0f));

    vertices.emplace_back(vec3(-0.5f,  0.5f, -0.5f), vec2(0.0f, 1.0f));
    vertices.emplace_back(vec3(0.5f,  0.5f, -0.5f),  vec2(1.0f, 1.0f));
    vertices.emplace_back(vec3(0.5f,  0.5f,  0.5f),  vec2(1.0f, 0.0f));
    vertices.emplace_back(vec3(0.5f,  0.5f,  0.5f),  vec2(1.0f, 0.0f));
    vertices.emplace_back(vec3(-0.5f,  0.5f,  0.5f), vec2(0.0f, 0.0f));
    vertices.emplace_back(vec3(-0.5f,  0.5f, -0.5f), vec2(0.0f, 1.0f));
}