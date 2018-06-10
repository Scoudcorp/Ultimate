#include "Patch.h"
#include <Windows.h>
#include <array>

Patch::Patch(const uint32_t address, std::initializer_list<unsigned char> bytes)
    : m_base{ reinterpret_cast<unsigned char*>(address) }
    , m_size{ bytes.size() }
    , m_patchBytes{ bytes }
    , m_oldProtect{ PAGE_EXECUTE_READ }
{
    m_originalBytes.insert(m_originalBytes.end(), m_base, m_base + m_size);
}

void Patch::apply()
{
    markRegionAsWritable();
    std::memcpy(m_base, m_patchBytes.data(), m_size);
    restoreRegion();

    std::printf("Patched %Iu bytes @ %p\n", m_size, m_base);
}

void Patch::restore()
{
    markRegionAsWritable();
    std::memcpy(m_base, m_originalBytes.data(), m_size);
    restoreRegion();

    std::printf("Restored %Iu bytes @ %p\n", m_size, m_base);
}

void Patch::markRegionAsWritable()
{
    VirtualProtect(m_base, m_size, PAGE_EXECUTE_READWRITE, &m_oldProtect);
}

void Patch::restoreRegion()
{
    VirtualProtect(m_base, m_size, m_oldProtect, &m_oldProtect);
}
