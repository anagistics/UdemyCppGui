#include <iostream>
#include <string>
#include <regex>

#include <fmt/format.h>
#include <imgui.h>
#include <implot.h>

#include "render.hpp"

namespace
{
    std::string PathToString(const fs::path &pth)
    {
        std::string escaped = std::regex_replace(pth.string(), std::regex("\\\\"), "\\");
        return escaped;
    }
}; // namespace

void WindowClass::Draw(std::string_view label)
{
    ImGui::Begin(label.data());

    if (ImGui::Button("[..Up..]"))
    {
        if (m_currentPath.has_parent_path())
            m_currentPath = m_currentPath.parent_path();
    }
    ImGui::SameLine(); // next element appears in the same line!
    std::string pathString{PathToString(m_currentPath)};
    ImGui::Text("Current folder: %s", pathString.c_str());
    ImGui::Separator();

    for (const auto& entry: fs::directory_iterator(m_currentPath))
    {
        std::string entry_name{entry.path().filename().string()};
        std::string output_line;

        if (entry.is_directory())
        {
            output_line = std::string{"[D] "}.append(entry_name);
        }
        else if (entry.is_regular_file())
        {
            output_line = std::string{"[F] "}.append(entry_name);
        }
        ImGui::Text(output_line.c_str());
    }

    ImGui::Separator();

    ImGui::End();
}

void render(WindowClass &window_obj)
{
    window_obj.Draw("Label");
}
