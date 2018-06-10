#pragma once

namespace VTable {

int Unprotect(void* region);

void Protect(void* region, int protection);

void* Hook(void* instance, void* hook, int offset);
};
