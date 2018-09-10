#include "PerkRule.h"
#include "iw4/weapon.h"
#include <imgui/imgui.h>

PerkRule::PerkRule(const std::string& name)
    : m_allowed{ true }
    , m_name{ name }
	, m_translated{TranslatePerk(name)}
{
}

void PerkRule::drawPerkRule()
{
	ImGui::Checkbox(m_translated.c_str(), &m_allowed);
}
