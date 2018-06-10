#pragma once
#include "menu.h"

struct cursor_t {
    float x;
    float y;
};

enum UILocalVarType {
    UILOCALVAR_INT = 0x0,
    UILOCALVAR_FLOAT = 0x1,
    UILOCALVAR_STRING = 0x2,
};

struct UILocalVar {
    UILocalVarType type;
    const char* name;

	void drawLocalVar();
};

struct UILocalVarContext {
    UILocalVar table[256];

	void drawLocalVarContext();
};

struct UiContext {
    int contextIndex;
    float bias;
    int realTime;
    int frameTime;
    cursor_t cursor;
    cursor_t prevCursor;
    int isCursorVisible;
    int screenWidth;
    int screenHeight;
    float screenAspect;
    float FPS;
    float blurRadiusOut;
    MenuDefinition* menus[640];
    int menuCount;
    MenuDefinition* menuStack[16];
    int openMenuCount;
    UILocalVarContext localVars;

	void drawUiContext();
};

namespace Ui {
	const inline auto g_uiContext = reinterpret_cast<UiContext*>(0x627AA18);
}
