#pragma once
#include "dvar.h"
#include "util.h"

enum EntryOperation {
    OP_NOOP = 0x0,
    OP_RIGHTPAREN = 0x1,
    OP_MULTIPLY = 0x2,
    OP_DIVIDE = 0x3,
    OP_MODULUS = 0x4,
    OP_ADD = 0x5,
    OP_SUBTRACT = 0x6,
    OP_NOT = 0x7,
    OP_LESSTHAN = 0x8,
    OP_LESSTHANEQUALTO = 0x9,
    OP_GREATERTHAN = 0xA,
    OP_GREATERTHANEQUALTO = 0xB,
    OP_EQUALS = 0xC,
    OP_NOTEQUAL = 0xD,
    OP_AND = 0xE,
    OP_OR = 0xF,
    OP_LEFTPAREN = 0x10,
    OP_COMMA = 0x11,
    OP_BITWISEAND = 0x12,
    OP_BITWISEOR = 0x13,
    OP_BITWISENOT = 0x14,
    OP_BITSHIFTLEFT = 0x15,
    OP_BITSHIFTRIGHT = 0x16,
    OP_STATICDVARINT = 0x17,
    OP_STATICDVARBOOL = 0x18,
    OP_STATICDVARFLOAT = 0x19,
    OP_STATICDVARSTRING = 0x1A,
    OP_INT = 0x1B,
    OP_STRING = 0x1C,
    OP_FLOAT = 0x1D,
    OP_SIN = 0x1E,
    OP_COS = 0x1F,
    OP_MIN = 0x20,
    OP_MAX = 0x21,
    OP_MILLISECONDS = 0x22,
    OP_DVARINT = 0x23,
    OP_DVARBOOL = 0x24,
    OP_DVARFLOAT = 0x25,
    OP_DVARSTRING = 0x26,
    OP_STAT = 0x27,
    OP_UIACTIVE = 0x28,
    OP_FLASHBANGED = 0x29,
    OP_USINGVEHICLE = 0x2A,
    OP_MISSILECAM = 0x2B,
    OP_SCOPED = 0x2C,
    OP_SCOPEDTHERMAL = 0x2D,
    OP_SCOREBOARDVISIBLE = 0x2E,
    OP_INKILLCAM = 0x2F,
    OP_INKILLCAMNPC = 0x30,
    OP_PLAYERFIELD = 0x31,
    OP_GETPERK = 0x32,
    OP_SELECTINGLOCATION = 0x33,
    OP_SELECTINGDIRECTION = 0x34,
    OP_TEAMFIELD = 0x35,
    OP_OTHERTEAMFIELD = 0x36,
    OP_MARINESFIELD = 0x37,
    OP_OPFORFIELD = 0x38,
    OP_MENUISOPEN = 0x39,
    OP_WRITINGDATA = 0x3A,
    OP_INLOBBY = 0x3B,
    OP_INPRIVATEPARTY = 0x3C,
    OP_PRIVATEPARTYHOST = 0x3D,
    OP_PRIVATEPARTYHOSTINLOBBY = 0x3E,
    OP_ALONEINPARTY = 0x3F,
    OP_ADSJAVELIN = 0x40,
    OP_WEAPLOCKBLINK = 0x41,
    OP_WEAPATTACKTOP = 0x42,
    OP_WEAPATTACKDIRECT = 0x43,
    OP_WEAPLOCKING = 0x44,
    OP_WEAPLOCKED = 0x45,
    OP_WEAPLOCKTOOCLOSE = 0x46,
    OP_WEAPLOCKSCREENPOSX = 0x47,
    OP_WEAPLOCKSCREENPOSY = 0x48,
    OP_SECONDSASTIME = 0x49,
    OP_TABLELOOKUP = 0x4A,
    OP_TABLELOOKUPBYROW = 0x4B,
    OP_TABLEGETROWNUM = 0x4C,
    OP_LOCALIZESTRING = 0x4D,
    OP_LOCALVARINT = 0x4E,
    OP_LOCALVARBOOL = 0x4F,
    OP_LOCALVARFLOAT = 0x50,
    OP_LOCALVARSTRING = 0x51,
    OP_TIMELEFT = 0x52,
    OP_SECONDSASCOUNTDOWN = 0x53,
    OP_GAMEMSGWNDACTIVE = 0x54,
    OP_GAMETYPENAME = 0x55,
    OP_GAMETYPE = 0x56,
    OP_GAMETYPEDESCRIPTION = 0x57,
    OP_SCORE = 0x58,
    OP_FRIENDSONLINE = 0x59,
    OP_SPECTATINGCLIENT = 0x5A,
    OP_SPECTATINGFREE = 0x5B,
    OP_STATRANGEBITSSET = 0x5C,
    OP_KEYBINDING = 0x5D,
    OP_ACTIONSLOTUSABLE = 0x5E,
    OP_HUDFADE = 0x5F,
    OP_MAXRECOMMENDEDPLAYERS = 0x60,
    OP_ACCEPTINGINVITE = 0x61,
    OP_ISINTERMISSION = 0x62,
    OP_GAMEHOST = 0x63,
    OP_PARTYISMISSINGMAPPACK = 0x64,
    OP_PARTYMISSINGMAPPACKERROR = 0x65,
    OP_ANYNEWMAPPACKS = 0x66,
    OP_AMISELECTED = 0x67,
    OP_PARTYSTATUSSTRING = 0x68,
    OP_ATTACHEDCONTROLLERCOUNT = 0x69,
    OP_ISSPLITSCREENONLINEPOSSIBLE = 0x6A,
    OP_SPLITSCREENPLAYERCOUNT = 0x6B,
    OP_GETPLAYERDATA = 0x6C,
    OP_GETPLAYERDATASPLITSCREEN = 0x6D,
    OP_EXPERIENCEFORLEVEL = 0x6E,
    OP_LEVELFOREXPERIENCE = 0x6F,
    OP_ISITEMUNLOCKED = 0x70,
    OP_ISITEMUNLOCKEDSPLITSCREEN = 0x71,
    OP_DEBUGPRINT = 0x72,
    OP_GETPLAYERDATAANYBOOLTRUE = 0x73,
    OP_WEAPONCLASSNEW = 0x74,
    OP_WEAPONNAME = 0x75,
    OP_ISRELOADING = 0x76,
    OP_SAVEGAMEAVAILABLE = 0x77,
    OP_UNLOCKEDITEMCOUNT = 0x78,
    OP_UNLOCKEDITEMCOUNTSPLITSCREEN = 0x79,
    OP_UNLOCKEDITEM = 0x7A,
    OP_UNLOCKEDITEMSPLITSCREEN = 0x7B,
    OP_MAILSUBJECT = 0x7C,
    OP_MAILFROM = 0x7D,
    OP_MAILRECEIVED = 0x7E,
    OP_MAILBODY = 0x7F,
    OP_MAILLOOTLOCALIZED = 0x80,
    OP_MAILGIVESLOOT = 0x81,
    OP_ANYNEWMAIL = 0x82,
    OP_MAILTIMETOFOLLOWUP = 0x83,
    OP_MAILLOOTTYPE = 0x84,
    OP_MAILRANLOTTERY = 0x85,
    OP_LOTTERYLOOTLOCALIZED = 0x86,
    OP_RADARISJAMMED = 0x87,
    OP_RADARJAMINTENSITY = 0x88,
    OP_RADARISENABLED = 0x89,
    OP_ISEMPJAMMED = 0x8A,
    OP_PLAYERADS = 0x8B,
    OP_WEAPONHEATACTIVE = 0x8C,
    OP_WEAPONHEATVALUE = 0x8D,
    OP_WEAPONHEATOVERHEATED = 0x8E,
    OP_GETSPLASHTEXT = 0x8F,
    OP_GETSPLASHDESCRIPTION = 0x90,
    OP_GETSPLASHMATERIAL = 0x91,
    OP_SPLASHHASICON = 0x92,
    OP_SPLASHROWNUM = 0x93,
    OP_GETFOCUSEDITEMNAME = 0x94,
    OP_GETFOCUSEDITEMX = 0x95,
    OP_GETFOCUSEDITEMY = 0x96,
    OP_GETFOCUSEDITEMWIDTH = 0x97,
    OP_GETFOCUSEDITEMHEIGHT = 0x98,
    OP_GETITEMX = 0x99,
    OP_GETITEMY = 0x9A,
    OP_GETITEMWIDTH = 0x9B,
    OP_GETITEMHEIGHT = 0x9C,
    OP_PLAYLIST = 0x9D,
    OP_SCOREBOARDEXTERNALMUTENOTICE = 0x9E,
    OP_GETCLIENTMATCHDATA = 0x9F,
    OP_GETCLIENTMATCHDATADEF = 0xA0,
    OP_GETMAPNAME = 0xA1,
    OP_GETMAPIMAGE = 0xA2,
    OP_GETMAPCUSTOM = 0xA3,
    OP_GETMIGRATIONSTATUS = 0xA4,
    OP_GETPLAYERCARDINFO = 0xA5,
    OP_ISOFFLINEPROFILESELECTED = 0xA6,
    OP_COOPPLAYER = 0xA7,
    OP_ISCOOP = 0xA8,
    OP_GETPARTYSTATUS = 0xA9,
    OP_GETSEARCHPARAMS = 0xAA,
    OP_GETTIMEPLAYED = 0xAB,
    OP_ISSELECTEDPLAYERFRIEND = 0xAC,
    OP_GETCHARBYINDEX = 0xAD,
    OP_GETPROFILEDATA = 0xAE,
    OP_ISPROFILESIGNEDIN = 0xAF,
    OP_GETWAITPOPUPSTATUS = 0xB0,
    OP_GETNATTYPE = 0xB1,
    OP_GETLOCALIZEDNATTYPE = 0xB2,
    OP_GETADJUSTEDSAFEAREAHORIZONTAL = 0xB3,
    OP_GETADJUSTEDSAFEAREAVERTICAL = 0xB4,
    OP_CONNECTIONINFO = 0xB5,
    OP_OFFLINEPROFILECANSAVE = 0xB6,
    OP_ALLSPLITSCREENPROFILESCANSAVE = 0xB7,
    OP_ALLSPLITSCREENPROFILESARESIGNEDIN = 0xB8,
    OP_DOWEHAVEMAPPACK = 0xB9,
};

enum ExpressionDataType {
    VAL_INT = 0x0,
    VAL_FLOAT = 0x1,
    VAL_STRING = 0x2,
    NUM_INTERNAL_DATATYPES = 0x3,
    VAL_FUNCTION = 0x3,
    NUM_DATATYPES = 0x4,
};

struct ExpressionString {
    const char* string;

    void draw();
};

union OperandInternalDataUnion {
    int intVal;
    float floatVal;
    ExpressionString* stringVal;
    struct Statement* function;

    void draw();
};

struct Operand {
    ExpressionDataType dataType;
    OperandInternalDataUnion internals;

    void draw();
};

union EntryInternalData {
    EntryOperation op;
    Operand operand;

    void draw();
};

struct SetLocalVarData {
    const char* localVarName;
    struct Statement* expression;

    void draw();
};

struct ConditionalScript {
    struct MenuEventHandlerSet* eventHandlerSet;
    struct Statement* eventExpression; // loads this first

    void draw();
};

struct ExpressionEntry {
    int type;
    EntryInternalData data;

    void draw();
};

struct Statement {
    int numEntries;
    ExpressionEntry* entries;
    struct ExpressionSupportingData* supportingData;
    char unknown[0xC];

    void draw();
};

enum ItemFloatExpressionTarget {
    ITEM_FLOATEXP_TGT_RECT_X = 0x0,
    ITEM_FLOATEXP_TGT_RECT_Y = 0x1,
    ITEM_FLOATEXP_TGT_RECT_W = 0x2,
    ITEM_FLOATEXP_TGT_RECT_H = 0x3,
    ITEM_FLOATEXP_TGT_FORECOLOR_R = 0x4,
    ITEM_FLOATEXP_TGT_FORECOLOR_G = 0x5,
    ITEM_FLOATEXP_TGT_FORECOLOR_B = 0x6,
    ITEM_FLOATEXP_TGT_FORECOLOR_RGB = 0x7,
    ITEM_FLOATEXP_TGT_FORECOLOR_A = 0x8,
    ITEM_FLOATEXP_TGT_GLOWCOLOR_R = 0x9,
    ITEM_FLOATEXP_TGT_GLOWCOLOR_G = 0xA,
    ITEM_FLOATEXP_TGT_GLOWCOLOR_B = 0xB,
    ITEM_FLOATEXP_TGT_GLOWCOLOR_RGB = 0xC,
    ITEM_FLOATEXP_TGT_GLOWCOLOR_A = 0xD,
    ITEM_FLOATEXP_TGT_BACKCOLOR_R = 0xE,
    ITEM_FLOATEXP_TGT_BACKCOLOR_G = 0xF,
    ITEM_FLOATEXP_TGT_BACKCOLOR_B = 0x10,
    ITEM_FLOATEXP_TGT_BACKCOLOR_RGB = 0x11,
    ITEM_FLOATEXP_TGT_BACKCOLOR_A = 0x12,
    ITEM_FLOATEXP_TGT__COUNT = 0x13,
};

struct ItemFloatExpression {
    ItemFloatExpressionTarget target;
    Statement* expression;

    void draw();
};

union EventData {
    const char* unconditionalScript;
    ConditionalScript* conditionalScript;
    MenuEventHandlerSet* elseScript;
    SetLocalVarData* setLocalVarData;

    void draw();
};

#pragma pack(push, 4)
struct MenuEventHandler {
    EventData eventData;
    char eventType;

    void draw();
};
#pragma pack(pop)

struct MenuEventHandlerSet {
    int eventHandlerCount;
    MenuEventHandler** eventHandlers;

    void draw();
};

struct ItemKeyHandler {
    int key;
    MenuEventHandlerSet* action;
    ItemKeyHandler* next;

    void draw();
};

struct NewsTicker {
    int feedId; // 0 = text input, 1 = motd
    int speed;
    int spacing;
    char unknown[0x10];

    void draw();
};

#define MAX_LB_COLUMNS 16

struct ColumnInfo {
    int pos;
    int width;
    int maxChars;
    int alignment;

    void draw();
};

struct ListBox {
    int unknown[4];
    float elementWidth;
    float elementHeight;
    int elementStyle;
    int numColumns;
    ColumnInfo columnInfo[MAX_LB_COLUMNS];
    MenuEventHandlerSet* doubleClick;
    int notselectable;
    int noscrollbars;
    int usepaging;
    float selectBorder[4];
    /*Material*/ void* selectIcon;

    void draw();
};

struct EditField {
    float minVal;
    float maxVal;
    float defVal;
    float range;
    int maxChars;
    int maxCharsGotoNext;
    int maxPaintChars;
    int paintOffset;

    void draw();
};

#define MAX_MULTI_DVARS 32

struct MultiDef {
    char* dvarList[MAX_MULTI_DVARS];
    char* dvarStr[MAX_MULTI_DVARS];
    float dvarValue[MAX_MULTI_DVARS];
    int count;
    int strDef;

    void draw();
};

struct TextScroll {
    int startTime;

    void draw();
};

union ItemData {
    ListBox* listBox;
    EditField* editField;
    MultiDef* multi;
    const char* enumDvarName;
    NewsTicker* newsTicker;
    TextScroll* textScroll;
    void* data;

    void draw();
};

#define WINDOWDYNAMIC_VISIBLE 0x00000004
#define WINDOWDYNAMIC_HASFORECOLOR 0x00010000

#define WINDOWSTATIC_DECORATION 0x00100000
#define WINDOWSTATIC_HORIZONTALSCROLL 0x00200000
#define WINDOWSTATIC_SCREENSPACE 0x00400000
#define WINDOWSTATIC_AUTOWRAPPED 0x00800000
#define WINDOWSTATIC_POPUP 0x01000000
#define WINDOWSTATIC_OUTOFBOUNDSCLICK 0x02000000
#define WINDOWSTATIC_LEGACYSPLITSCREENSCALE 0x04000000
#define WINDOWSTATIC_HIDDENDURINGFLASH 0x10000000
#define WINDOWSTATIC_HIDDENDURINGSCOPE 0x20000000
#define WINDOWSTATIC_HIDDENDURINGUI 0x40000000
#define WINDOWSTATIC_TEXTONLYFOCUS 0x80000000

#pragma pack(push, 4)
struct Rect {
    float x;
    float y;
    float w;
    float h;
    char horzAlign;
    char vertAlign;

    void draw();
};
#pragma pack(pop)

struct Window {
    const char* name;
    Rect rect;
    Rect rectClient;
    const char* group;
    int style;
    int border;
    int ownerDraw;
    int ownerDrawFlags;
    float borderSize;
    int staticFlags;
    int dynamicFlags;
    int nextTime;
    float foreColor[4];
    float backColor[4];
    float borderColor[4];
    float outlineColor[4];
    float disableColor[4];
    /*Material*/ void* background;

    void draw();
};

struct Item {
    Window window;
    Rect textRect;
    int type;
    int dataType;
    int align;
    int fontEnum;
    int textAlignMode;
    float textAlignX;
    float textAlignY;
    float textScale;
    int textStyle;
    int gameMsgWindowIndex;
    int gameMsgWindowMode;
    const char* text;
    int textSaveGameInfo;
    struct MenuDefinition* parent;
    MenuEventHandlerSet* mouseEnterText;
    MenuEventHandlerSet* mouseExitText;
    MenuEventHandlerSet* mouseEnter;
    MenuEventHandlerSet* mouseExit;
    MenuEventHandlerSet* action;
    MenuEventHandlerSet* accept;
    MenuEventHandlerSet* onFocus;
    MenuEventHandlerSet* leaveFocus;
    const char* dvar;
    const char* dvarTest;
    ItemKeyHandler* onKey;
    const char* enableDvar;
    int dvarFlags;
    void /*snd_alias_list_t*/* focusSound;
    float special;
    int cursorPos;
    ItemData typeData;
    int imageTrack;
    int floatExpressionCount;
    ItemFloatExpression* floatExpressions;
    Statement* visibleExp;
    Statement* disabledExp;
    Statement* textExp;
    Statement* materialExp;
    float glowColor[4];
    bool decayActive;
    int fxBirthTime;
    int fxLetterTime;
    int fxDecayStartTime;
    int fxDecayDuration;
    int lastSoundPlayedTime;

    void draw();
};

struct StaticDvar {
    dvar_s* dvar;
    const char* dvarName;

    void draw();
};

struct StaticDvarList {
    int numStaticDvars;
    StaticDvar** staticDvars;

    void draw();
};

struct FunctionList {
    int totalFunctions;
    Statement** functions;

    void draw();
};

struct StringList {
    int totalStrings;
    const char** strings;

    void draw();
};

struct ExpressionSupportingData {
    FunctionList uifunctions;
    StaticDvarList staticDvarList;
    StringList uiStrings;

    void draw();
};

enum TransitionType {
    TRANS_INACTIVE = 0x0,
    TRANS_LERP = 0x1,
};

enum TriggerType {
    TRIGGER_NONE = 0x0,
    TRIGGER_CLOSEMENU = 0x1,
};

struct MenuTransition {
    TransitionType transitionType;
    int startTime;
    float startVal;
    float endVal;
    float time;
    TriggerType endTriggerType;

    void draw();
};

struct MenuDefinition {
    Window window;
    const char* font;
    int fullscreen;
    int itemCount;
    int fontIndex;
    int cursorItems;
    int fadeCycle;
    float fadeClamp;
    float fadeAmount;
    float fadeInAmount;
    float blurRadius;
    MenuEventHandlerSet* onOpen;
    MenuEventHandlerSet* onRequestClose;
    MenuEventHandlerSet* onClose;
    MenuEventHandlerSet* onEsc;
    ItemKeyHandler* execKeys;
    Statement* visibleExp;
    const char* allowedBinding;
    const char* soundName;
    int imageTrack;
    float focusColor[4];
    Statement* rectXExp;
    Statement* rectYExp;
    Statement* rectHExp;
    Statement* rectWExp;
    Statement* openSoundExp;
    Statement* closeSoundExp;
    Item** items;
    char unknown[112];
    ExpressionSupportingData* expressionData;

    void draw();
};

struct MenuList {
    const char* name;
    int menuCount;
    struct MenuDefinition** menus;

    void draw();
};

namespace Menu {

IW4_FUNCTION(OpenMenu, void, (int localClientNum, const char* menuName), 0x59DF10);
}
