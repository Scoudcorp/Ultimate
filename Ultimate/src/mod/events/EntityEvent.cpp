#include "EntityEvent.h"

void EntityEvent::execute()
{
	m_callback(m_entNum);
}
