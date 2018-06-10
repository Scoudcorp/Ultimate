#pragma once

class ThreadAction {
public:
    virtual ~ThreadAction() = default;

    virtual bool onFrame();
};
