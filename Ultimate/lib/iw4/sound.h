#pragma once

enum snd_alias_type_t : __int8 {
    SAT_UNKNOWN = 0x0,
    SAT_LOADED = 0x1,
    SAT_STREAMED = 0x2,
    SAT_PRIMED = 0x3,
    SAT_COUNT = 0x4,
};

struct LoadedSound {
    int size;
    char unknown1[10];
    __int16 numFrames;
    int* frames;
    char* data;
};

struct StreamFileNameRaw {
    const char* dir;
    const char* name;
};

struct StreamFileNamePacked {
    unsigned __int64 offset;
    unsigned __int64 length;
};

union StreamFileInfo {
    StreamFileNameRaw raw;
    StreamFileNamePacked packed;
};

struct StreamFileName {
    unsigned __int16 isLocalized;
    unsigned __int16 fileIndex;
    StreamFileInfo info;
};

struct StreamedSound {
    StreamFileName filename;
    unsigned int totalMsec;
};

union SoundFileRef {
    LoadedSound* loadSnd;
    StreamedSound streamSnd;
};

struct SoundFile {
    snd_alias_type_t type;
    bool exists;
    SoundFileRef sound;
};

struct SndCurve {
    const char* filename;
    unsigned __int16 knotCount;
    float knots[2][16];
};

struct SpeakerLevels {
    int speaker;
    int numLevels;
    float levels[2];
};

struct ChannelMap {
    int entryCount;
    SpeakerLevels speakers[6];
};

struct SpeakerMap {
    bool isDefault;
    const char* name;
    ChannelMap channelMaps[2][2];
};

struct snd_alias_t {
    const char* aliasName;
    const char* subtitle;
    const char* secondaryAliasName;
    const char* chainAliasName;
    const char* mixerGroup;
    SoundFile* soundFile;
    int sequence;
    float volMin;
    float volMax;
    float pitchMin;
    float pitchMax;
    float distMin;
    float distMax;
    float velocityMin;
    int flags;
    float slavePercentage;
    float probability;
    float lfePercentage;
    float centerPercentage;
    int startDelay;
    SndCurve* volumeFalloffCurve;
    float envelopMin;
    float envelopMax;
    float envelopPercentage;
    SpeakerMap* speakerMap;
};

struct snd_alias_list_t {
    const char* aliasName;
    snd_alias_t* head;
    int count;
};

struct XAUDIOREVERBSETTINGS {
    unsigned int ReflectionsDelay;
    char ReverbDelay;
    char RearDelay;
    char PositionLeft;
    char PositionRight;
    char PositionMatrixLeft;
    char PositionMatrixRight;
    char EarlyDiffusion;
    char LateDiffusion;
    char LowEQGain;
    char LowEQCutoff;
    char HighEQGain;
    char HighEQCutoff;
    float RoomFilterFreq;
    float RoomFilterMain;
    float RoomFilterHF;
    float ReflectionsGain;
    float ReverbGain;
    float DecayTime;
    float Density;
    float RoomSize;
};

struct XaReverbSettings {
    int presetOverridden;
    XAUDIOREVERBSETTINGS reverbSettings;
};

struct SndDriverGlobals {
    XaReverbSettings* reverbSettings;
    char* name;
};
