#include "server.h"

void SV_GameSendServerCommandAll(svscmd_type type, const char* fmt)
{
    for (auto i = 0; i < 18; i++) {
        SV_GameSendServerCommand(i, type, fmt);
    }
}

void Server::ExecuteClientCommand(client_t* client, const char* command, int clientOk, int fromOldServer)
{
    auto func = 0x586B80;

    __asm {
        mov eax, fromOldServer
        push eax
        mov eax, clientOk
        push eax
        mov eax, command
        mov ecx, client
        call func
        add esp, 8
    }
}
