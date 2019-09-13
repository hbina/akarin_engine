#include "akarin_database/shader/shader_program_database.hpp"
#include "akarin_database/shader/shader_code_database.hpp"
#include "akarin_database/texture/texture_database.hpp"
#include "types/shader.hpp"

#include <ostream>
#include <sstream>

ShaderProgramDb &ShaderProgramDb::get_instance() noexcept
{
    static ShaderProgramDb instance;
    return instance;
};

ShaderProgramDb::~ShaderProgramDb() noexcept
{
    for (const auto &shader_program_id : map)
    {
        glDeleteProgram(shader_program_id.first);
    }
};

void test_shader_program_compilation(
    const GLuint p_shader) noexcept;

GLuint ShaderProgramDb::link_shader_codes(
    const std::vector<GLuint> &p_shaders) noexcept
{
    GLuint shader_program_id = glCreateProgram();
    for (const auto shader_id : p_shaders)
    {
        glAttachShader(shader_program_id, shader_id);
    }
    glLinkProgram(shader_program_id);
    get_instance().map[shader_program_id] = ShaderProgram(p_shaders);
    test_shader_program_compilation(shader_program_id);
    return shader_program_id;
};

void ShaderProgramDb::set_shader_program_texture(
    const GLuint p_shader_program_id,
    const std::vector<std::size_t> &textures) noexcept
{
    // TODO :: This is not normalized data structure...please consider making it so.
    for (std::size_t i = 0; i < textures.size(); i++)
    {
        switch (TextureDb::textures_map[textures[i]].m_type)
        {
        case TextureType::DIFFUSE:
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glUniform1i(glGetUniformLocation(p_shader_program_id, "material.diffuse"), i);
            glBindTexture(GL_TEXTURE_2D, TextureDb::textures_map[textures[i]].m_gl_id);
            break;
        };
        case TextureType::HEIGHT:
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glUniform1i(glGetUniformLocation(p_shader_program_id, "material.height"), i);
            glBindTexture(GL_TEXTURE_2D, TextureDb::textures_map[textures[i]].m_gl_id);
            break;
        };
        case TextureType::NORMAL:
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glUniform1i(glGetUniformLocation(p_shader_program_id, "material.normal"), i);
            glBindTexture(GL_TEXTURE_2D, TextureDb::textures_map[textures[i]].m_gl_id);
            break;
        };
        case TextureType::SPECULAR:
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glUniform1i(glGetUniformLocation(p_shader_program_id, "material.specular"), i);
            glBindTexture(GL_TEXTURE_2D, TextureDb::textures_map[textures[i]].m_gl_id);
            break;
        };
        default:
        {
            continue;
        }
        };
    }
    // TODO :: Temporary solution...need to figure out how deal with this crap
};

// Free functions definitions

void test_shader_program_compilation(const GLuint p_shader) noexcept
{
    static constexpr auto info_log_size = 1024;
    GLint success;
    GLchar info_log[info_log_size];
    glGetProgramiv(p_shader, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(p_shader, info_log_size, nullptr, info_log);
        std::cerr << "p_shader:" << p_shader << " shader program compilation failed"
                  << "\n";
        for (const auto &p_iter : ShaderProgramDb::get_instance().map[p_shader].m_shader_ids)
        {
            std::cerr << "id: " << p_iter << "\n";
            std::cerr << "filepath: " << ShaderCodeDb::map[p_iter].m_filepath << "\n";
            std::cerr << "type: " << ShaderCodeDb::map[p_iter].m_type << "\n";
        }
        std::cout << info_log << "\n";
    }
};
