#pragma once
#include "imgui/imgui.h"
#include "iw4/weapon.h"
#include "mod/weapon/WeaponRule.h"
#include <array>

enum class WeaponClass {
    Undefined,
    Launcher,
    Handgun,
    MachinePistol,
    Shotgun,
    AssaultRifle,
    SubMachineGun,
    LightMachineGun,
    SniperRifle,
    Special
};

template <std::size_t Size>
class WeaponClassRule {
public:
    WeaponClassRule(const std::string& name, const WeaponClass weaponClass, const std::array<WeaponRule, Size> rules)
        : m_enabled{ true }
        , m_name{ name }
        , m_weaponClass{ weaponClass }
        , m_rules{ rules } {};

    void drawWeaponClassRule()
    {
        if (ImGui::TreeNode(m_name.c_str())) {

            for (auto& rule : m_rules) {
                rule.drawWeaponRule();
            }

            ImGui::TreePop();
        }
    }

    bool m_enabled;
    const std::string m_name;
    const WeaponClass m_weaponClass;
    std::array<WeaponRule, Size> m_rules;
};
