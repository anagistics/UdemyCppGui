#include <iostream>
#include <regex>
#include <array>
#include <string>
#include <sstream>
#include <vector>

#include <fmt/format.h>
#include <imgui.h>
#include <implot.h>

#include "render.hpp"

void WindowClass::Draw(std::string_view label)
{
    constexpr ImGuiWindowFlags window_flags =
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoTitleBar;

    ImVec2 application_window_size = ImGui::GetMainViewport()->Size;
    ImGui::SetNextWindowSize(application_window_size);
    ImGui::SetNextWindowPos(ImVec2(0.0, 0.0));
    ImGui::Begin(label.data(), nullptr, window_flags);

    std::array<std::string, WindowClass::NumOfOptions> items = {"Item 1", "Item 2", "Item 3"};

    size_t idx = 0;
    for (const std::string& optionName: items)
    {
        bool selected = state().option(idx);
        if (ImGui::Checkbox(optionName.c_str(), &selected))
        {
            state().setOption(idx, selected);
        }
        idx++;
    }

    ImGui::Separator();

    ImGui::Text(state().toString().c_str());

    ImGui::End();
}

void render(WindowClass &window_obj)
{
    window_obj.Draw("Label");
}
