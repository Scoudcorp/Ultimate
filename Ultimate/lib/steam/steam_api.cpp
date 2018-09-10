#include "steam_gameserver.h"

S_API HINSTANCE S_CALLTYPE SteamAPI_GetHandle()
{
    static HINSTANCE instance = nullptr;
    if (instance == nullptr)
    {
        instance = GetModuleHandle(L"steam_api");
    }

    return instance;
}

S_API void S_CALLTYPE SteamAPI_Shutdown()
{
    typedef void (S_CALLTYPE *SteamAPI_Shutdown_t)();
    static SteamAPI_Shutdown_t func = nullptr;

    if (func == nullptr)
    {
        func = (SteamAPI_Shutdown_t)GetProcAddress(SteamAPI_GetHandle(), "SteamAPI_Shutdown");
    }

    return func();
}

S_API bool S_CALLTYPE SteamAPI_Init()
{
    typedef bool (S_CALLTYPE *SteamAPI_Init_t)();
    static SteamAPI_Init_t func = nullptr;

    if (func == nullptr)
    {
        func = (SteamAPI_Init_t)GetProcAddress(SteamAPI_GetHandle(), "SteamAPI_Init");
    }

    return func();
}

S_API ISteamClient *S_CALLTYPE SteamClient()
{
    typedef ISteamClient *(S_CALLTYPE *SteamClient_t)();
    static SteamClient_t func = nullptr;

    if (func == nullptr)
    {
        func = (SteamClient_t)GetProcAddress(SteamAPI_GetHandle(), "SteamClient");
    }

    return func();
}

S_API ISteamUser *S_CALLTYPE SteamUser()
{
    typedef ISteamUser *(S_CALLTYPE *SteamUser_t)();
    static SteamUser_t func = nullptr;

    if (func == nullptr)
    {
        func = (SteamUser_t)GetProcAddress(SteamAPI_GetHandle(), "SteamUser");
    }

    return func();
}

S_API ISteamFriends *S_CALLTYPE SteamFriends()
{
    typedef ISteamFriends *(S_CALLTYPE *SteamFriends_t)();
    static SteamFriends_t func = nullptr;

    if (func == nullptr)
    {
        func = (SteamFriends_t)GetProcAddress(SteamAPI_GetHandle(), "SteamFriends");
    }

    return func();
}

S_API ISteamUtils *S_CALLTYPE SteamUtils()
{
    typedef ISteamUtils *(S_CALLTYPE *SteamUtils_t)();
    static SteamUtils_t func = nullptr;

    if (func == nullptr)
    {
        func = (SteamUtils_t)GetProcAddress(SteamAPI_GetHandle(), "SteamUtils");
    }

    return func();
}

S_API ISteamMatchmaking *S_CALLTYPE SteamMatchmaking()
{
    typedef ISteamMatchmaking *(S_CALLTYPE *SteamMatchmaking_t)();
    static SteamMatchmaking_t func = nullptr;

    if (func == nullptr)
    {
        func = (SteamMatchmaking_t)GetProcAddress(SteamAPI_GetHandle(), "SteamMatchmaking");
    }

    return func();
}

S_API ISteamGameServer *SteamGameServer()
{
    typedef ISteamGameServer *(S_CALLTYPE *SteamGameServer_t)();
    static SteamGameServer_t func = nullptr;

    if (func == nullptr)
    {
        func = (SteamGameServer_t)GetProcAddress(SteamAPI_GetHandle(), "SteamGameServer");
    }

    return func();
}

S_API bool SteamGameServer_BSecure()
{
    typedef bool (S_CALLTYPE *SteamGameServer_BSecure_t)();
    static SteamGameServer_BSecure_t func = nullptr;

    if (func == nullptr)
    {
        func = (SteamGameServer_BSecure_t)GetProcAddress(SteamAPI_GetHandle(), "SteamGameServer_BSecure");
    }

    return func();
}

S_API HSteamPipe SteamAPI_GetHSteamPipe()
{
    typedef HSteamPipe (S_CALLTYPE *SteamAPI_GetHSteamPipe_t)();
    static SteamAPI_GetHSteamPipe_t func = nullptr;

    if (func == nullptr)
    {
        func = (SteamAPI_GetHSteamPipe_t)GetProcAddress(SteamAPI_GetHandle(), "SteamAPI_GetHSteamPipe");
    }

    return func();
}

S_API void S_CALLTYPE SteamAPI_RunCallbacks()
{
    typedef void (S_CALLTYPE *SteamAPI_RunCallbacks_t)();
    static SteamAPI_RunCallbacks_t func = nullptr;

    if (func == nullptr)
    {
        func = (SteamAPI_RunCallbacks_t)GetProcAddress(SteamAPI_GetHandle(), "SteamAPI_RunCallbacks");
    }

    return func();
}
