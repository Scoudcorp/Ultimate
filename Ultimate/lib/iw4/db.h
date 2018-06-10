#pragma once
#include "asset.h"
#include "util.h"

namespace Database
{
	IW4_FUNCTION(FindXAssetHeader, XAssetHeader, (XAssetType type, const char *name), 0x4F4800);
}
