#pragma once
#include <string>

class PerkRule {
public:
	explicit PerkRule(const std::string& name);

    bool m_allowed;
    const std::string m_name;
    const std::string m_translated;
    void drawPerkRule();
};
