#pragma once

#include <string_view>
#include <filesystem>
#include <vector>
#include <string>

namespace fs = std::filesystem;

class FolderContentEntry
{
public:
    FolderContentEntry() = delete;

    FolderContentEntry(const fs::path &path, bool isDirectory) : m_isDirectory(isDirectory), m_path(path)
    {}

    std::string label() const
    {
        if (m_isDirectory)
            return std::string{"[D] "}.append(name());
        else 
            return std::string{"[F] "}.append(name());
    }

    std::string name() const { return m_path.filename().string(); }
    fs::path path() const { return m_path; }
    bool isDirectory() const { return m_isDirectory; }

private:
    bool m_isDirectory;
    fs::path m_path;
};

class WindowClass
{
public:
    WindowClass() : m_currentPath(fs::current_path()), m_selectedPath(fs::current_path()), m_needsUpdate(true) {};

    void Draw(std::string_view label);

    void DrawFolderContent();

private:
    fs::path m_currentPath;
    fs::path m_selectedPath;
    bool m_needsUpdate;
    std::vector<FolderContentEntry> m_folderContent;

    void updatePath(const fs::path& newPath)
    {
        m_currentPath = newPath;
        m_needsUpdate = true;
    }
};

void render(WindowClass &window_obj);
