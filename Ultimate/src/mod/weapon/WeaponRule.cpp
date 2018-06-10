#include "WeaponRule.h"
#include "imgui/imgui.h"
#include "iw4/weapon.h"

WeaponRule::WeaponRule(const std::string& name)
    : m_allowed{ true }
    , m_name{ name }
    , m_translated{ TranslateWeaponBase(name) }
    , m_attachments{
        AttachmentRule("acog"),
        AttachmentRule("akimbo"),
        AttachmentRule("eotech"),
        AttachmentRule("fmj"),
        AttachmentRule("gl"),
        AttachmentRule("grip"),
        AttachmentRule("heartbeat"),
        AttachmentRule("reflex"),
        AttachmentRule("rof"),
        AttachmentRule("shotgun"),
        AttachmentRule("silencer"),
        AttachmentRule("tactical"),
        AttachmentRule("thermal"),
        AttachmentRule("xmags")
    }
{
}

void WeaponRule::drawWeaponRule()
{
    if (ImGui::TreeNode(m_translated.c_str())) {

        ImGui::Checkbox("Allowed", &m_allowed);

        for (auto& attachment : m_attachments) {
            attachment.drawAttachmentRule();
        }

        ImGui::TreePop();
    }
}

const AttachmentRule* WeaponRule::findAttachment(const std::string& attachment) const
{
	const auto result = std::find_if(m_attachments.begin(), m_attachments.end(), [&attachment](const AttachmentRule& rule) {
        return attachment == rule.m_name;
    });

    if (result == m_attachments.end()) {
        return nullptr;
    }

	return &(*result);
}
