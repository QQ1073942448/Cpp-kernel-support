#pragma once
#include"ȫ������.h"

void* operator new(size_t size);
void* operator new[](size_t size);
void operator delete(void* ptr, size_t size);
void operator delete[](void* ptr, size_t size);
