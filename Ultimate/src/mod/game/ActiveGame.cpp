#include "ActiveGame.h"
#include "iw4/iw_string.h"
#include "iw4/party.h"
#include "iw4/server.h"
#include "mod/weapon/WeaponClassRule.h"
#include "ultimate/Ultimate.h"
#include "util/Message.h"

ActivePlayer& ActiveGame::getActivePlayer(const uint32_t playerNum)
{
    return m_activePlayers[playerNum];
}

const char* ActiveGame::getRandomWeaponName()
{
    return g_weaponDefs[m_weaponDistribution(m_weaponRng)]->szInternalName;
}

const char* ActiveGame::getRandomEquipmentName()
{
    return g_weaponDefs[m_equipmentDistribution(m_weaponRng)]->szInternalName;
}

void ActiveGame::playerSpawned(const uint32_t playerNum)
{
    auto& player = getActivePlayer(playerNum);

    if (!player.m_active) {
        player.reset();
        player.m_index = playerNum;
        player.m_active = true;

//        player.initHud();

        const auto name = player.getPartyClient()->name;
        const auto ip = player.getPartyClient()->getRemoteIp();
        const auto message = String::Format("%s^7 connected", name);
        Message::SendChatAnnouncement(-1, message);
    }

    player.m_nextRandomWeapons[0] = getRandomWeaponName();
    player.m_nextRandomWeapons[1] = getRandomWeaponName();
    player.m_nextRandomEquipment[0] = getRandomEquipmentName();
    player.m_nextRandomEquipment[1] = getRandomEquipmentName();
}

void ActiveGame::playerKilled(const uint32_t victimPlayerNum, const uint32_t killerPlayerNum)
{
    if (victimPlayerNum == killerPlayerNum) {
        return playerSuicide(victimPlayerNum);
    }

    auto& victim = getActivePlayer(victimPlayerNum);
    auto& killer = getActivePlayer(killerPlayerNum);

    victim.addDeath();
    killer.addKill();

//    victim.updateKillStreakHud();
}

void ActiveGame::setKillStreak(const uint32_t playerNum, const int32_t streak)
{
    auto& player = getActivePlayer(playerNum);

    if (streak > player.m_killstreak) {
        if (streak % 5 == 0) {
            const auto message = String::Format("%s^7 is on a ^2%i^7 killstreak!", player.getPartyClient()->name, streak);
            Message::SendChatAnnouncement(-1, message);
        }
    }

    player.m_killstreak = streak;
//    player.updateKillStreakHud();
}

void ActiveGame::playerSuicide(const uint32_t playerNum)
{
    auto& victim = getActivePlayer(playerNum);

    victim.addDeath();
//    victim.updateKillStreakHud();
}

void ActiveGame::playerDisconnected(const uint32_t playerNum)
{
    auto& player = getActivePlayer(playerNum);

    player.reset();
}

void ActiveGame::gameOver()
{
    for (auto& activePlayer : m_activePlayers) {
        activePlayer.reset();
    }
}

const char* ActiveGame::getCurrentRandomWeapon(const uint32_t playerNum)
{
    auto& player = getActivePlayer(playerNum);

    return player.m_nextRandomWeapons[player.m_currentRandomWeaponIndex];
}

void ActiveGame::advanceCurrentRandomWeapon(const uint32_t playerNum)
{
    auto& player = getActivePlayer(playerNum);

    player.m_currentRandomWeaponIndex += 1;

    if (player.m_currentRandomWeaponIndex >= player.m_nextRandomWeapons.size()) {
        player.m_currentRandomWeaponIndex = 0;
    }
}

const char* ActiveGame::getCurrentRandomEquipment(const uint32_t playerNum)
{
    auto& player = getActivePlayer(playerNum);

    return player.m_nextRandomEquipment[player.m_currentRandomEquipmentIndex];
}

void ActiveGame::advanceCurrentRandomEquipment(const uint32_t playerNum)
{
    auto& player = getActivePlayer(playerNum);

    player.m_currentRandomEquipmentIndex += 1;

    if (player.m_currentRandomEquipmentIndex >= player.m_nextRandomEquipment.size()) {
        player.m_currentRandomEquipmentIndex = 0;
    }
}

void ActiveGame::drawActiveGame()
{
    ImGui::Begin("Game", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);

    if (ImGui::Button("Restart")) {
        Cmd::AddCommandToBuffer(0, "map_restart");
    }

    ImGui::Separator();

    for (auto& player : m_activePlayers) {

        const auto text = String::Format("%2d - %s", player.m_index, player.m_active ? player.getPartyClient()->name : "---");

        if (ImGui::TreeNodeEx(text)) {
            if (player.m_active) {
                player.draw();
            }

            ImGui::TreePop();
        }
    }

    ImGui::End();
}
