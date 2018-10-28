#pragma once

#pragma comment(lib, "PolyHook_2.lib")

class Hook
{
public:
    virtual void hook() = 0;
    virtual void unhook() = 0;
};
