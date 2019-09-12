#include "akarin_imgui/shader_code_database_window.hpp"
#include "akarin_database/shader/shader_code_database.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <algorithm>
#include <sstream>
#include <ostream>
#include <string>

void ShaderCodeDatabaseWindow::render() noexcept
{
    ImGui::Begin("ShaderCode System");
    if (ImGui::CollapsingHeader("Load ShaderCodes"))
    {
        static char shader_code_text[64] = "";
        ImGui::Text("Path to shader code");
        ImGui::InputText("path:", shader_code_text, 64);
        if (ImGui::Button("Load ShaderCode"))
        {
            // TODO :: Dummy, fix later. Add a combo
            ShaderCodeDatabase::load_shader_file(shader_code_text, ShaderType::VERTEX);
        }
    }
    if (ImGui::CollapsingHeader("ShaderCodes List"))
    {
        ImGui::Text("List of ShaderCodes loaded:");

        for (const auto &p_iter : ShaderCodeDatabase::map)
        {
            std::ostringstream out;
            out << p_iter.first;
            out << " : ";
            out << p_iter.second.m_filepath << "\n";
            ImGui::Text(
                "%s",
                out.str().c_str());
        };
    }
    ImGui::End();
};