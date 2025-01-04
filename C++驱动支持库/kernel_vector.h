#pragma once
#include"全局所需.h"


template <typename T>
 class vector {
public:
    T* data;
    ULONG Size;

    vector();
    ULONG size() const;
    NTSTATUS push_back(const T& element);
    T at(ULONG index) const;
    T& operator[](ULONG index); // 可修改元素
    const T& operator[](ULONG index) const; // 只读版本
    NTSTATUS pop_back();
    void clear();
    ULONG find(const T& element) const;
    NTSTATUS erase(ULONG index);
    ~vector();
};



