#pragma once

struct PrecacheEntry {
    unsigned __int16 filename;
    bool include;
    unsigned int sourcePos;
};

struct scr_localVar_t {
    unsigned int name;
    unsigned int sourcePos;
};

struct scr_block_s {
    int abortLevel;
    int localVarsCreateCount;
    int localVarsPublicCount;
    int localVarsCount;
    char localVarsInitBits[8];
    scr_localVar_t localVars[64];
};

union sval_u {
    char type;
    unsigned int stringValue;
    unsigned int idValue;
    float floatValue;
    int intValue;
    sval_u* node;
    unsigned int sourcePosValue;
    const char* codePosValue;
    const char* debugString;
    scr_block_s* block;
};

char *TempMalloc(int len);

char *Scr_AddSourceBuffer(const char *filename, const char *extFilenam);

void Scr_BeginLoadScripts(int user);

unsigned int Scr_LoadScript(const char* filename);

unsigned int Scr_LoadScriptInternal(const char* filename, PrecacheEntry* entries, int entriesCount);

void ScriptParse(sval_u *parseData, char user);

void ScriptCompile(sval_u val, unsigned int filePosId, unsigned int fileCountId, unsigned int scriptId, PrecacheEntry *entries, int entriesCount);

inline unsigned int g_parentId = 0;
inline unsigned int dword_1D378CC = 0;
inline unsigned int dword_1D374A8 = 0;
inline unsigned int dword_1D378C4 = 0;
inline unsigned int dword_1D578E0 = 0;
inline unsigned char byte_1D578E4 = 0;
inline unsigned int dword_1D578E8 = 0;
inline unsigned int dword_1D378D0 = 0;
