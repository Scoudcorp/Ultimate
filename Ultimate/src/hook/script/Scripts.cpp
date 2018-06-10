#include "Scripts.h"
#include "mod/events/EntityEvent.h"
#include "settings/Settings.h"
#include "util/Message.h"
#include <iw4/iw_string.h>
#include <iw4/party.h>
#include <iw4/server.h>
#include <ultimate/Ultimate.h>

namespace Proxies {

bool GiveWeaponControl(const scr_entref_t entref)
{
    const auto weaponName = Script::GetString(0);

    if (g_settings.m_modSettings.m_randomWeaponModEnabled) {

        const char* randomWeapon = nullptr;

        const auto weaponIndex = BG_FindWeaponIndexForName(weaponName);
        if (IsEquipment(weaponIndex)) {
            randomWeapon = Ultimate::m_ultimate->m_activeGame.getCurrentRandomEquipment(entref.entnum);
            Ultimate::m_ultimate->m_activeGame.advanceCurrentRandomEquipment(entref.entnum);
        } else if (IsWeapon(weaponIndex)) {
            randomWeapon = Ultimate::m_ultimate->m_activeGame.getCurrentRandomWeapon(entref.entnum);
            Ultimate::m_ultimate->m_activeGame.advanceCurrentRandomWeapon(entref.entnum);
        }

        if (randomWeapon != nullptr) {
            Script::g_scrVmPub->top->u.stringValue = String::GetString(randomWeapon, 0);
        }
    } else {
        const auto replace = Ultimate::m_ultimate->m_loadoutControl.shouldWeaponBeReplaced(weaponName);
        if (replace) {
            Script::g_scrVmPub->top->u.stringValue = String::GetString(Ultimate::m_ultimate->m_loadoutControl.m_replacementWeapon.build().c_str(), 0);
        }

//        if (strstr(weaponName, "deserteagle") != nullptr) {
//            Script::g_scrVmPub->top->u.stringValue = String::GetString("deserteaglegold_mp", 0);
//        } else if (entref.entnum == *g_hostId && strstr(weaponName, "usp") != nullptr) {
//            Script::g_scrVmPub->top->u.stringValue = String::GetString("deserteaglegold_mp", 0);
//        }
    }

    return true;
}

bool SetSpawnWeaponControl(const scr_entref_t entref)
{
    const auto weaponName = Script::GetString(0);

    const auto weaponIndex = BG_FindWeaponIndexForName(weaponName);

    if (g_settings.m_modSettings.m_randomWeaponModEnabled) {
        const auto randomWeapon = Ultimate::m_ultimate->m_activeGame.getCurrentRandomWeapon(entref.entnum);

        Script::g_scrVmPub->top->u.stringValue = String::GetString(randomWeapon, 0);
    } else if (IsWeapon(weaponIndex)) {
        const auto replace = Ultimate::m_ultimate->m_loadoutControl.shouldWeaponBeReplaced(weaponName);

        if (replace) {
            Script::g_scrVmPub->top->u.stringValue = String::GetString(Ultimate::m_ultimate->m_loadoutControl.m_replacementWeapon.build().c_str(), 0);
        }

//        if (strstr(weaponName, "deserteagle") != nullptr) {
//            Script::g_scrVmPub->top->u.stringValue = String::GetString("deserteaglegold_mp", 0);
//        } else if (entref.entnum == *g_hostId && strstr(weaponName, "usp") != nullptr) {
//            Script::g_scrVmPub->top->u.stringValue = String::GetString("deserteaglegold_mp", 0);
//        }
    }

    const auto fovString = String::Format("s cg_fov \"%d\"", g_settings.m_gameSettings.m_forcedFov);
    SV_GameSendServerCommand(entref.entnum, svscmd_type::SV_CMD_RELIABLE, fovString);
    SV_GameSendServerCommand(entref.entnum, svscmd_type::SV_CMD_RELIABLE, "s cg_ScoresPing_MaxBars \"10\"");
    SV_GameSendServerCommand(entref.entnum, svscmd_type::SV_CMD_RELIABLE, "s cg_chatHeight \"8\"");
    SV_GameSendServerCommand(entref.entnum, svscmd_type::SV_CMD_RELIABLE, "s cg_hudChatPosition \"5 204\"");
    SV_GameSendServerCommand(entref.entnum, svscmd_type::SV_CMD_RELIABLE, "s cg_hudChatIntermissionPosition \"5 110\"");

    if (g_settings.m_modSettings.m_randomWeaponModEnabled) {
        SV_GameSendServerCommand(entref.entnum, svscmd_type::SV_CMD_CAN_IGNORE, "c \"^2Enjoy your ^1RANDOM^2 weapons!\"");
    }

    return true;
}

bool SetClientDvar(const scr_entref_t entref)
{
    const auto playerName = Party::g_partyData->partyMembers[entref.entnum].name;
    const auto dvarName = Script::GetString(0);
    const auto value = Script::GetString(1);

    if (std::strcmp(dvarName, "cg_fov") == 0) {
        if (g_settings.m_logSettings.m_logClientDvars) {
            std::printf("PlayerCmd_SetClientDvar -> ignoring dvar %s to %s for %s\n", dvarName, value, playerName);
        }
        return false;
    }

    if (g_settings.m_logSettings.m_logClientDvars) {
        std::printf("PlayerCmd_SetClientDvar -> setting dvar %s to %s for %s\n", dvarName, value, playerName);
    }
    return true;
}

bool SetPerk(const scr_entref_t entref)
{
    const auto playerName = Party::g_partyData->partyMembers[entref.entnum].name;
    const auto perkName = Script::GetString(0);

    const auto replace = Ultimate::m_ultimate->m_loadoutControl.shouldPerkBeReplaced(perkName);

    if (replace) {
        Script::g_scrVmPub->top->u.stringValue = String::GetString(Ultimate::m_ultimate->m_loadoutControl.m_replacementPerk.c_str(), 0);
    }

    if (g_settings.m_logSettings.m_logPerks) {
        std::printf("PlayerCmd_SetPerk -> setting perk %s on %s\n", perkName, playerName);
    }

    return true;
}

bool Spawn(const scr_entref_t entref)
{
    Ultimate::m_ultimate->m_activeGame.playerSpawned(entref.entnum);
    return true;
}

bool ExitLevel(const scr_entref_t entref)
{
    Ultimate::m_ultimate->m_activeGame.gameOver();
    return true;
}

bool GetEntArray(scr_entref_t entref)
{
    if (Script::GetNumParam()) {
        const auto key = Script::GetString(1);
        const auto value = Script::GetString(0);

        if (String::GetString(value, 0) == String::GetString("care_package", 0)) {
            auto results = Script::GetEntArray(key, value);

            if (!results.empty()) {
                auto matchResults = Script::GetEntArray(key, String::ConvertToString(results[0]->targetname));

                if (!matchResults.empty()) {
                    //std::printf("Found airdropCollision\n");
                    g_airdropCollisionBrush = matchResults[0];
                }
            }
        }
    }

    return true;
}

bool CloneBrushmodelToScriptmodel(const scr_entref_t entref)
{
    auto thisEnt = &g_entities[entref.entnum];
    auto thatEnt = Script::GetEntity(0);

    //std::printf("CloneBrushmodelToScriptmodel -> ent %d cloning to: %d\n", thisEnt->state.number, thatEnt->state.number);

    return true;
}
} // namespace Proxies
