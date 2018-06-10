#include "GenericEvent.h"

void GenericEvent::execute()
{
    m_callback();
}
