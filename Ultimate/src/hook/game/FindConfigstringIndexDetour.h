#pragma once
#include "hook/Detour.h"

using FindConfigstringIndexFunction = int(*)(const char *, int, int, int, const char *);

class FindConfigstringIndexDetour: public Detour
{
public:
    static FindConfigstringIndexFunction m_originalFindConfigstringIndex;

    long applyDetour() override;
    long restoreDetour() override;

    static int hookFindConfigstringIndex(const char *name, int start, int max, int create, const char *errormsg);
};
