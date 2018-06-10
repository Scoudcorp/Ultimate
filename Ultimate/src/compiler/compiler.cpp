#include "compiler.h"
#include "iw4/iw4_memory.h"
#include "iw4/iw_string.h"
#include "iw4/script.h"

char* TempMalloc(const int len)
{
    static unsigned char buffer[128];
    return reinterpret_cast<char*>(Memory::HunkUserAlloc(&buffer, len, 1));
}

unsigned Scr_LoadScriptInternal(const char* filename, PrecacheEntry* entries, const int entriesCount)
{
//    unsigned int sourceBuffer;
//    sval_u parseData{};
//    char extFilename[64];
//
//    const auto fileNameIndex = Script::CreateCanonicalFilename(filename);
//
//    if (Script::FindVariable(g_parentId, fileNameIndex)) {
//        String::RemoveRefToString(fileNameIndex);
//        if (Script::FindVariable(dword_1D378CC, fileNameIndex)) {
//            sourceBuffer = Script::FindObject(dword_1D378CC);
//        } else {
//            sourceBuffer = 0;
//        }
//    } else {
//        const auto scriptId = Script::GetNewVariable(g_parentId, fileNameIndex);
//        String::RemoveRefToString(fileNameIndex);
//        const auto fileName = String::ConvertToString(fileNameIndex);
//        String::Sprintf(extFilename, 64, "%s.gsc", fileName);
//        TempMalloc(0);
//
//        const auto filenameIndex = String::ConvertToString(fileNameIndex);
//        sourceBuffer = reinterpret_cast<unsigned int>(Scr_AddSourceBuffer(filenameIndex, extFilename)); // TODO: is that reinterpret_cast right?
//        const auto v7 = sourceBuffer;
//        if (sourceBuffer) {
//            const int v8 = dword_1D374A8;
//            dword_1D374A8 = 0;
//            dword_1D378C4 = 0;
//
//            //nullsub_4(); // ?
//
//            dword_1D578E0 = reinterpret_cast<unsigned int>("+"); // TODO: is that reinterpret_cast right?
//            dword_1D578E8 = v7;
//            byte_1D578E4 = 0;
//
//            ScriptParse(&parseData, 0);
//
//            dword_1D578E8 = 0;
//            const int v9 = Script::GetVariable(dword_1D378CC, fileNameIndex);
//            const int filePosId = Script::GetObject(dword_1D378CC, v9);
//            const int v11 = Script::GetVariable(dword_1D378D0, fileNameIndex);
//            const int fileCountId = Script::GetObject(dword_1D378D0, v11);
//
//            ScriptCompile(parseData, filePosId, fileCountId, scriptId, entries, entriesCount);
//
//            Script::RemoveVariable(dword_1D378D0, fileNameIndex);
//            dword_1D374A8 = v8;
//            sourceBuffer = filePosId;
//        }
//    }
//    return sourceBuffer;

    return 1;
}
