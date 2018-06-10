#pragma once
#include "Event.h"

class GenericEvent: public Event
{
    using GenericCallback = void(*)();
    GenericCallback m_callback;

public:
    GenericEvent(const GenericCallback callback)
        : m_callback(callback)
    {
    }

    void execute() override;
};
