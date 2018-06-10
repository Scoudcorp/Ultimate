#pragma once
#include "hook/Detour.h"
#include "iw4/asset.h"

using FindXAssetHeaderFunction = XAssetHeader (*)(XAssetType type, const char* name);

class FindXAssetHeaderDetour : public Detour {

public:

	static FindXAssetHeaderFunction m_originalFindXAssetHeader;

    long applyDetour() override;
    long restoreDetour() override;

	static XAssetHeader hookFindXAssetHeader(XAssetType type, const char *name);
};
