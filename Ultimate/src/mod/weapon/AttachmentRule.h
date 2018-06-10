#pragma once
#include <string>
class AttachmentRule
{
public:
	explicit AttachmentRule(const std::string& name);

	bool m_allowed;
	const std::string m_name;
	const std::string m_translated;
	void drawAttachmentRule();
};

