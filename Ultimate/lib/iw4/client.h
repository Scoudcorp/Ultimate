#pragma once

#include "gsl/span.h"
#include "network.h"

struct clientHeader_t
{
    int state;
    int sendAsActive;
    int deltaMessage;
    int rateDelayed;
    netchan_t netchan;
};

struct client_t {
    clientHeader_t header;
    uint8_t __pad[0xA6158];
};


const inline gsl::span<client_t> g_cls = { reinterpret_cast<client_t*>(0x3172090), 18 };
