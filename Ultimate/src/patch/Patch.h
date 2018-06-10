#pragma once
#include <cstddef>
#include <vector>

class Patch {
public:
    Patch(uint32_t address, std::initializer_list<unsigned char> bytes);

    void apply();
    void restore();

private:
    unsigned char* m_base;
    size_t m_size;
    std::vector<unsigned char> m_originalBytes;
    std::vector<unsigned char> m_patchBytes;

    unsigned long m_oldProtect;

    void markRegionAsWritable();
    void restoreRegion();
};
