#ifndef MESH_H
#define MESH_H

#include "types/texture.hpp"
#include "types/vertex.hpp"

#include "glad/glad.h"

#include <vector>
#include <array>

struct MeshData
{
    GLuint m_vao_gl_id = 0;
    GLuint m_vbo_gl_id = 0;
    GLuint m_ebo_gl_id = 0;
    const std::vector<Vertex> m_vertices;
    const std::vector<unsigned int> m_indices;
    const std::vector<std::size_t> m_textures;

    MeshData() = delete;
    MeshData(
        const unsigned int,
        const unsigned int,
        const unsigned int,
        const std::vector<Vertex> &,
        const std::vector<unsigned int> &,
        const std::vector<std::size_t> &) noexcept;

    void draw(
        const GLuint,
        const bool) const;
};

#endif
