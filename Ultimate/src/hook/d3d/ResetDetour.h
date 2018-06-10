#pragma once
#include "../Detour.h"
#include <d3d9.h>

using ResetFunction = HRESULT(WINAPI*)(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params);

class ResetDetour : public Detour {
public:
    static ResetFunction m_originalReset;

    long applyDetour() override;

    long restoreDetour() override;

    static HRESULT WINAPI hookReset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params);
};
