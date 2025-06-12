#pragma once

#include <string_view>
#include <filesystem>

class State
{
public:
    State() = delete;
    explicit State(size_t nOptions) : nOptions(nOptions), selectedOptions(nOptions, false)
    { }

    void setOption(size_t index, bool value)
    {
        if (index < nOptions)
        {
            selectedOptions[index] = value;
        }
    }

    bool option(size_t index) const
    {
        if (index < nOptions)
        {
            return selectedOptions[index];
        }
        return false; // or throw an exception
    }

    std::string toString() const
    {
        std::string result;
        for (size_t i = 0; i < nOptions; ++i)
        {
            result += "Option " + std::to_string(i) + ": " + (selectedOptions[i] ? "Selected" : "Not Selected") + "\n";
        }
        return result;
    }

private:
    const size_t nOptions;
    std::vector<bool> selectedOptions;
};

class WindowClass
{
public:
    static const size_t NumOfOptions = 3u;

    WindowClass() : m_state(NumOfOptions) {};

    void Draw(std::string_view label);
    State& state()
    {
        return m_state;
    }

private:
    State m_state;
};

void render(WindowClass &window_obj);
