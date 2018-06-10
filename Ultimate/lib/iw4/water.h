#pragma once
#include "image.h"

struct WaterWritable {
    float floatTime;
};

struct water_t {
    WaterWritable writable;
    float* H0X;
    float* H0Y;
    float* wTerm;
    int M;
    int N;
    float Lx;
    float Lz;
    float gravity;
    float windvel;
    float winddir[2];
    float amplitude;
    float codeConstant[4];
    GfxImage* image;
};
