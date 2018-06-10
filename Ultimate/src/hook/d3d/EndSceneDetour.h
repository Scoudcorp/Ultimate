#pragma once
#include <d3d9.h>
#include <hook/Detour.h>

using EndSceneFunction = HRESULT(WINAPI*)(IDirect3DDevice9* device);

class EndSceneDetour : public Detour {
public:
    static EndSceneFunction m_originalEndScene;

    long applyDetour() override;
    long restoreDetour() override;

    static HRESULT WINAPI hookEndScene(IDirect3DDevice9* device);
};
