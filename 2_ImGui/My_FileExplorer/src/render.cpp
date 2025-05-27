#include <iostream>
#include <regex>

#include <fmt/format.h>
#include <imgui.h>

#include "render.hpp"

namespace
{
    std::string PathToString(const fs::path& pth)
    {
        std::string escaped = std::regex_replace(pth.string(), std::regex("\\\\"), "\\");
        return escaped;
    }

    std::vector<FolderContentEntry> FolderContent(const fs::path& pth)
    {
        std::vector<FolderContentEntry> output_lines;

        for (const auto &entry : fs::directory_iterator(pth))
            output_lines.emplace_back(entry, entry.is_directory());
        return output_lines;
    }
}; // namespace

void WindowClass::Draw(std::string_view label)
{
    ImGui::Begin(label.data());

    if (ImGui::Button("[..Up..]"))
    {
        if (m_currentPath.has_parent_path())
            updatePath(m_currentPath.parent_path());
    }
    ImGui::SameLine(); // next element appears in the same line!
    std::string pathString{PathToString(m_currentPath)};
    ImGui::Text("Current folder: %s", pathString.c_str());
    ImGui::Separator();

    DrawFolderContent();

    ImGui::Separator();

    ImGui::End();
}

void WindowClass::DrawFolderContent()
{
    if (m_needsUpdate)
    {
        m_folderContent = FolderContent(m_currentPath);
        m_needsUpdate = false; // reset the flag
    }
    for (const auto &entry : m_folderContent)
        if (ImGui::Selectable(entry.label().c_str()) && entry.isDirectory())
        {
            m_selectedPath = m_currentPath;
            updatePath(m_currentPath /= entry.name());
        }
}

void render(WindowClass &window_obj)
{
    window_obj.Draw("Label");
}
