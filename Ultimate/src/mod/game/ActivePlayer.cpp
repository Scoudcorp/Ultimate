#include "ActivePlayer.h"
#include "imgui/imgui.h"
#include "iw4/iw_string.h"
#include "ultimate/Ultimate.h"
#include "util/Message.h"

void ActivePlayer::reset()
{
    m_active = false;
    m_kills = 0;
    m_deaths = 0;
    m_killstreak = 0;
}

void ActivePlayer::addDeath()
{
    if (m_killstreak > 10) {
        const auto message = String::Format("%s^7 killstreak ended on ^2%i^7!", getPartyClient()->name, m_killstreak);
        Message::SendChatAnnouncement(-1, message);
    }

    m_deaths += 1;
    m_killstreak = 0;
}

void ActivePlayer::addKill()
{
    m_kills += 1;
}

PartyClient* ActivePlayer::getPartyClient() const
{
    return &Party::g_partyData->partyMembers[m_index];
}

void ActivePlayer::initHud()
{
    if (m_hudKillStreak == nullptr || m_hudKillStreak->hud.type == 0) {
        m_hudKillStreak = Hud::Alloc(m_index, 0);
        m_hudKillStreak->clientNum = m_index;
    }

    updateKillStreakHud();
}

void ActivePlayer::updateKillStreakHud()
{
    m_hudKillStreak->hud.setText("Killstreak: %d", m_killstreak);
    m_hudKillStreak->hud.fontScale = 2;
    m_hudKillStreak->hud.x = 5;
    m_hudKillStreak->hud.y = 5;
}

void ActivePlayer::draw()
{
    const auto client = getPartyClient();

    ImGui::Text("Name: %s", client->name);
    ImGui::Text("SteamID: %lld", client->steamId);
    ImGui::Text("Local ip: %d.%d.%d.%d", client->localIp[0], client->localIp[1], client->localIp[2], client->localIp[3]);
    ImGui::Text("Remote ip: %d.%d.%d.%d", client->remoteIp[0], client->remoteIp[1], client->remoteIp[2], client->remoteIp[3]);

//    const auto cls = &g_cls[m_index];
//    const auto address = &cls->header.netchan.remoteAddress;
//    ImGui::Text("Address (client_t): %d.%d.%d.%d:%d", address->ip[0], address->ip[1], address->ip[2], address->ip[3], address->port);
//    ImGui::Text("client_t size: %d", sizeof(client_t));

    ImGui::Separator();

    ImGui::Text("Kills: %d", m_kills);
    ImGui::Text("Deaths: %d", m_deaths);
    ImGui::Text("Streak: %d", m_killstreak);

    ImGui::Separator();

    if (ImGui::Button("Kick")) {
        Ultimate::m_ultimate->m_accessControl.kickClient(m_index, "you have been ^2kicked^7 from the server");
    }

    if (ImGui::Button("Ban")) {
        Ultimate::m_ultimate->m_accessControl.banClient(m_index, "you have been ^2banned^7 from the server");
    }

//    if (ImGui::Button("Kill")) {
//        const auto event = std::make_shared<EntityEvent>(m_index, [](int32_t entNum) {
//            const auto message = String::Format("killed %s", Party::g_partyData->partyMembers[entNum].name);
//            Message::SendChatAnnouncement(-1, message);
//            Game::Suicide(entNum);
//        });
//
//        Ultimate::m_ultimate->m_eventQueue.pushEvent(event);
//    }
}
