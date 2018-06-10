#pragma once
#include "AttachmentRule.h"
#include <array>
#include <string>

class WeaponRule {
public:
	explicit WeaponRule(const std::string& name);

	void drawWeaponRule();

    bool m_allowed;

    const std::string m_name;
	const std::string m_translated;

    std::array<AttachmentRule, 14> m_attachments;

    const AttachmentRule* findAttachment(const std::string& attachment) const;
};
