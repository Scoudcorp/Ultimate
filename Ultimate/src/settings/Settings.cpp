#include "Settings.h"
#include "iw4/command.h"
#include "iw4/iw_string.h"
#include "iw4/menu.h"
#include "iw4/server.h"
#include <imgui/imgui.h>

void PartySettings::drawPartySettings()
{
    if (ImGui::TreeNode("Party")) {
        if (ImGui::Checkbox("Force host", &m_forceHost)) {
            if (m_forceHost) {
                m_connectTimeOut->current.integer = 1;
                m_bandwithTestEnabled->current.enabled = false;
                m_autoTeams->current.enabled = true;
                m_maxTeamDifference->current.integer = 18;
                m_requireOpenNat->current.enabled = false;
                *m_doWeSuckAsHost = false;
                *m_natType = NAT_OPEN;
            } else {
                m_connectTimeOut->current.integer = m_connectTimeOut->reset.integer;
                m_bandwithTestEnabled->current.enabled = m_bandwithTestEnabled->reset.enabled;
                m_autoTeams->current.enabled = m_autoTeams->reset.enabled;
                m_maxTeamDifference->current.integer = m_maxTeamDifference->reset.integer;
                m_requireOpenNat->current.enabled = m_requireOpenNat->reset.enabled;
            }
        }

        ImGui::InputInt("Max clients", m_maxClients);

        if (ImGui::Button("Open game setup")) {
            Menu::OpenMenu(0, "popup_gamesetup");
        }

        ImGui::TreePop();
    }
}

void LogSettings::drawLogSettings()
{
    if (ImGui::TreeNode("Logging")) {
        ImGui::Checkbox("Log deaths", &m_logDeaths);
        ImGui::Checkbox("Log chat", &m_logChat);
        ImGui::Checkbox("Log allowed clients", &m_logAllowedHandshakes);
        ImGui::Checkbox("Log denied clients", &m_logDeniedHandshakes);
        ImGui::Checkbox("Log weapons", &m_logWeapons);
        ImGui::Checkbox("Log client dvars", &m_logClientDvars);
        ImGui::Checkbox("Log client perks", &m_logPerks);
        ImGui::Checkbox("Log spawn weapons", &m_logSpawnWeapons);
        ImGui::Checkbox("Log player spawns", &m_logSpawn);
        ImGui::Checkbox("Log loadout control", &m_logLoadoutControl);
        //ImGui::Checkbox("Log XAsset lookups", &m_logXAssetLookups);
        //ImGui::InputInt("XAsset filter", &m_logXAssetFilter);
        ImGui::Checkbox("Log menu responses", &m_logMenuResponses);
        ImGui::Checkbox("Log access violations", &m_logAccessViolations);
        //ImGui::Checkbox("Log server commands", &m_logServerCommands);

        ImGui::TreePop();
    }
}

void ModSettings::drawModSettings()
{
    if (ImGui::TreeNode("Mods")) {
        ImGui::Checkbox("Random weapons", &m_randomWeaponModEnabled);

//        if (ImGui::TreeNode("All weapons")) {
//            for (auto i = 0; i < g_weaponDefs.size(); i++) {
//                const auto weaponName = g_weaponDefs[i]->szInternalName;
//                ImGui::Text("%4d - %s", i, weaponName);
//            }
//
//            ImGui::TreePop();
//        }

        ImGui::TreePop();
    }
}

void GameSettings::drawGameSettings()
{
    if (ImGui::TreeNode("Game")) {
        static char commandBuffer[1024] = "";
        if (ImGui::InputText("Command", commandBuffer, IM_ARRAYSIZE(commandBuffer), ImGuiInputTextFlags_EnterReturnsTrue)) {
            Cmd::AddCommandToBuffer(0, commandBuffer);
            strcpy_s(commandBuffer, "");
            ImGui::SetKeyboardFocusHere(-1);
        }

        if (ImGui::InputInt("Field of view", &m_forcedFov)) {
            const auto fovString = String::Format("s cg_fov \"%d\"", m_forcedFov);
            SV_GameSendServerCommandAll(svscmd_type::SV_CMD_RELIABLE, fovString);
        };

        ImGui::TreePop();
    }
}

void Settings::drawSettings()
{
    ImGui::Begin("Settings", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);

    m_partySettings.drawPartySettings();
    m_gameSettings.drawGameSettings();
    m_modSettings.drawModSettings();
    m_logSettings.drawLogSettings();

    ImGui::End();
}
