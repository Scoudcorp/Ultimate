#include "weapon.h"

std::string TranslateWeaponBase(const std::string_view& weapon)
{
    if (weapon == "m79")
        return "Thumper";
    if (weapon == "rpg")
        return "RPG-7";
    if (weapon == "at4")
        return "AT4-HS";
    if (weapon == "stinger")
        return "Stinger";
    if (weapon == "javelin")
        return "Javelin";
    if (weapon == "riotshield")
        return "Riot Shield";
    if (weapon == "beretta")
        return "M9";
    if (weapon == "usp")
        return "USP .45";
    if (weapon == "coltanaconda")
        return ".44 Magnum";
    if (weapon == "deserteagle")
        return "Desert Eagle";
    if (weapon == "deserteaglegold")
        return "Desert Eagle Gold";
    if (weapon == "pp2000")
        return "PP2000";
    if (weapon == "tmp")
        return "TMP";
    if (weapon == "glock")
        return "G18";
    if (weapon == "beretta393")
        return "M93 Raffica";
    if (weapon == "mp5k")
        return "MP5K";
    if (weapon == "uzi")
        return "Mini-Uzi";
    if (weapon == "p90")
        return "P90";
    if (weapon == "kriss")
        return "Vector";
    if (weapon == "ump45")
        return "UMP45";
    if (weapon == "ak47")
        return "AK-47";
    if (weapon == "m16")
        return "M16A4";
    if (weapon == "m4")
        return "M4A1";
    if (weapon == "fn2000")
        return "F2000";
    if (weapon == "masada")
        return "ACR";
    if (weapon == "famas")
        return "FAMAS";
    if (weapon == "fal")
        return "FAL";
    if (weapon == "scar")
        return "SCAR-H";
    if (weapon == "tavor")
        return "TAR-21";
    if (weapon == "barrett")
        return "Barett .50cal";
    if (weapon == "wa2000")
        return "WA2000";
    if (weapon == "m21")
        return "M21 EBR";
    if (weapon == "cheytac")
        return "Intervention";
    if (weapon == "ranger")
        return "Ranger";
    if (weapon == "model1887")
        return "Model 1887";
    if (weapon == "striker")
        return "Striker";
    if (weapon == "aa12")
        return "AA-12";
    if (weapon == "m1014")
        return "M1014";
    if (weapon == "spas12")
        return "SPAS-12";
    if (weapon == "rpd")
        return "RPD";
    if (weapon == "sa80")
        return "L86 LSW";
    if (weapon == "mg4")
        return "MG4";
    if (weapon == "m240")
        return "M240";
    if (weapon == "aug")
        return "AUG HBAR";

    return std::string(weapon);
}

std::string TranslateWeaponAttachment(const std::string_view& attachment)
{
    if (attachment == "acog")
        return "ACOG scope";
    if (attachment == "akimbo")
        return "Akimbo";
    if (attachment == "eotech")
        return "Holographic Sight";
    if (attachment == "fmj")
        return "FMJ";
    if (attachment == "gl")
        return "Grenade Launcher";
    if (attachment == "grip")
        return "Grip";
    if (attachment == "heartbeat")
        return "Heartbeat Sensor";
    if (attachment == "reflex")
        return "Red Dot Sight";
    if (attachment == "rof")
        return "Rapid Fire";
    if (attachment == "shotgun")
        return "Shotgun";
    if (attachment == "silencer")
        return "Silencer";
    if (attachment == "tactical")
        return "Tactical Knife";
    if (attachment == "thermal")
        return "Thermal";
    if (attachment == "xmags")
        return "Extended Mags";

    return std::string(attachment);
}

std::string TranslatePerk(const std::string_view& perk)
{
    if (perk == "specialty_null")
        return "No perk";
    if (perk == "specialty_marathon")
        return "Marathon";
    if (perk == "specialty_fastreload")
        return "Sleight of Hand";
    if (perk == "specialty_scavenger")
        return "Scavenger";
    if (perk == "specialty_onemanarmy")
        return "One Man Army";
    if (perk == "specialty_bling")
        return "Bling";
    if (perk == "specialty_bulletdamage")
        return "Stopping Power";
    if (perk == "specialty_lightweight")
        return "Lightweight";
    if (perk == "specialty_hardline")
        return "Hardline";
    if (perk == "specialty_coldblooded")
        return "Cold-Blooded";
    if (perk == "specialty_explosivedamage")
        return "Danger Close";
    if (perk == "specialty_extendedmelee")
        return "Commando";
    if (perk == "specialty_bulletaccuracy")
        return "Steady Aim";
    if (perk == "specialty_localjammer")
        return "Scrambler";
    if (perk == "specialty_heartbreaker")
        return "Ninja";
    if (perk == "specialty_pistoldeath")
        return "Last Stand";
    if (perk == "specialty_delaymine")
        return "Scrambler Pro";
    if (perk == "specialty_selectivehearing")
        return "SitRep Pro";
    if (perk == "specialty_quickdraw")
        return "Sleight Of Hand Pro";
    if (perk == "specialty_fastsprintrecovery")
        return "Lightweight Pro";
    if (perk == "specialty_secondarybling")
        return "Bling Pro";
    if (perk == "specialty_gpsjammer")
        return "GPS Jammer";
    if (perk == "specialty_fastmantle")
        return "Marathon Pro";
    if (perk == "specialty_armorpiercing")
        return "Stopping Power Pro";
    if (perk == "specialty_rollover")
        return "Hardline Pro";
    if (perk == "specialty_omaquickchange")
        return "One Man Army Pro";
    if (perk == "specialty_extraammo")
        return "Scavenger Pro";
    if (perk == "specialty_spygame")
        return "Cold-Blooded Pro";
    if (perk == "specialty_holdbreath")
        return "Steady Aim Pro";
    if (perk == "specialty_laststandoffhand")
        return "Last Stand Pro";
    if (perk == "specialty_quieter")
        return "Ninja Pro";
    if (perk == "specialty_dangerclose")
        return "Danger Close Pro";
    if (perk == "specialty_falldamage")
        return "Commando Pro";
    if (perk == "specialty_grenadepulldeath")
        return "Martyrdom";
    if (perk == "specialty_c4death")
        return "C4 Death";
    if (perk == "specialty_combathigh")
        return "Painkiller";
    if (perk == "specialty_finalstand")
        return "Final Stand";
    if (perk == "specialty_copycat")
        return "Copycat";

    return std::string(perk);
}

bool IsWeapon(const int weaponIndex)
{
    return weaponIndex >= 3 && weaponIndex <= 1143;
}

bool IsEquipment(const int weaponIndex)
{
    return weaponIndex >= 1144 && weaponIndex <= 1154;
}

bool IsAkimbo(const int weaponIndex)
{
    return std::strstr(g_weaponDefs[weaponIndex]->szInternalName, "akimbo") != nullptr;
}
