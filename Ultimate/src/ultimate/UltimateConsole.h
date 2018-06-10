#pragma once
#include <cstdio>

class UltimateConsole {
public:
    UltimateConsole();
    ~UltimateConsole();

    UltimateConsole(const UltimateConsole& other) = default;

    UltimateConsole(UltimateConsole&& other) noexcept
        : m_fileOut(other.m_fileOut)
    {
    }

    UltimateConsole& operator=(const UltimateConsole& other)
    {
        if (this == &other) {
            return *this;
}
        m_fileOut = other.m_fileOut;
        return *this;
    }

    UltimateConsole& operator=(UltimateConsole&& other) noexcept
    {
        if (this == &other) {
            return *this;
}
        m_fileOut = other.m_fileOut;
        return *this;
    }

private:
    FILE* m_fileOut;
};
