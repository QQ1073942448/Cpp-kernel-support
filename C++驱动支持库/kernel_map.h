#pragma once
#include"全局所需.h"

template <typename Key, typename Value>
class map {
private:
    struct Pair {
        Key key;
        Value value;
    };

    Pair* data;
    ULONG size;

    ULONG find_index(const Key& key) const;

public:
    map();
    ULONG count() const;
    NTSTATUS insert(const Key& key, const Value& value);
    Value* find(const Key& key) const;
    NTSTATUS erase(const Key& key);
    void clear();
    ~map();
};