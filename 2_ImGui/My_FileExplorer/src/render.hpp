#pragma once

#include <string_view>
#include <filesystem>

namespace fs = std::filesystem;

class WindowClass
{
public:
    WindowClass() : m_currentPath(fs::current_path()) {};

    void Draw(std::string_view label);

private:
    fs::path m_currentPath;
};

void render(WindowClass &window_obj);
