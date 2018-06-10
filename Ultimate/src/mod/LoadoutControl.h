#pragma once

#include "perk/PerkRule.h"
#include "weapon/WeaponClassRule.h"
#include "weapon/WeaponRule.h"
#include <array>
#include <string_view>

struct WeaponParts {
    const std::string m_weapon;
    const std::string m_firstAttachment;
    const std::string m_secondAttachment;

	std::string build() const;
};

class LoadoutControl {
public:
    LoadoutControl();

    void drawLoadoutControls();

    WeaponParts m_replacementWeapon;
    std::string m_replacementPerk;

    bool shouldWeaponBeReplaced(const std::string& weapon);
    bool shouldPerkBeReplaced(const std::string& perkName);

    WeaponRule m_genericRule;
    WeaponClassRule<5> m_launchers;
    WeaponClassRule<5> m_handGuns;
    WeaponClassRule<4> m_machinePistols;
    WeaponClassRule<6> m_shotguns;
    WeaponClassRule<9> m_assaultRifles;
    WeaponClassRule<5> m_subMachineGuns;
    WeaponClassRule<5> m_lightMachineGuns;
    WeaponClassRule<4> m_sniperRifles;
    WeaponClassRule<1> m_special;

    std::array<PerkRule, 32> m_perks;
    std::array<PerkRule, 5> m_deathStreaks;

private:
    template <class InIt>
    const WeaponRule* findWeapon(InIt begin, InIt end, const std::string& weapon)
    {
        auto result = std::find_if(*begin, *end, [&weapon](const WeaponRule& rule) {
            return weapon == rule.m_name;
        });

        if (result == *end) {
            return nullptr;
        }

	    return &*result;
    }

    template <class InIt>
    const PerkRule* findSpeciality(InIt begin, InIt end, const std::string& perk)
    {
        auto result = std::find_if(*begin, *end, [&perk](const PerkRule& rule) {
            return perk == rule.m_name;
        });

        if (result == *end) {
            return nullptr;
        }

	    return &*result;
    }

    const PerkRule* findSpeciality(const std::string& perk);
    const PerkRule* findPerk(const std::string& perk);
    const PerkRule* findDeathStreak(const std::string& perk);

    const WeaponRule* findWeapon(const std::string& weapon);
    const WeaponRule* findLauncher(const std::string& weapon);
    const WeaponRule* findHandgun(const std::string& weapon);
    const WeaponRule* findMachinePistol(const std::string& weapon);
    const WeaponRule* findShotgun(const std::string& weapon);
    const WeaponRule* findAssaultRifle(const std::string& weapon);
    const WeaponRule* findSubMachineGun(const std::string& weapon);
    const WeaponRule* findLightMachineGun(const std::string& weapon);
    const WeaponRule* findSniperRifle(const std::string& weapon);
    const WeaponRule* findSpecial(const std::string& weapon);

	WeaponParts breakdownWeapon(const std::string& weapon) const;
};
