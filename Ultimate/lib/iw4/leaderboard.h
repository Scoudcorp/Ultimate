#pragma once

struct LeaderboardDefEntry {
    char* stringPointer1;
    char unknownData1[12];
    char* stringPointer2;
    char unknownData2[12];
};

struct LeaderboardDef {
    char* name;
    int unknown1;
    int entryCount;
    int unknown2;
    int unknown3;
    LeaderboardDefEntry* entries;
};
