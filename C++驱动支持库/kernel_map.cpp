#include"kernel_map.h"
// 构造函数
template <typename Key, typename Value>
map<Key, Value>::map() : data(nullptr), size(0) {
  
}

// 获取大小
template <typename Key, typename Value>
ULONG map<Key, Value>::count() const {
    return size;
}

// 插入键值对
template <typename Key, typename Value>
NTSTATUS map<Key, Value>::insert(const Key& key, const Value& value) {
    // 检查键是否已存在
    if (find_index(key) != ULONG_MAX) {
        return STATUS_OBJECT_NAME_COLLISION; // 键重复
    }

    // 分配新内存
    Pair* newdata = (Pair*)ExAllocatePoolWithTag(NonPagedPool, (size + 1) * sizeof(Pair), 'MapT');
    if (!newdata) {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    if (data != nullptr) {
        RtlCopyMemory(newdata, data, size * sizeof(Pair));
        ExFreePoolWithTag(data, 'MapT');
    }

    newdata[size].key = key;
    newdata[size].value = value;

    data = newdata;
    size++;

    return STATUS_SUCCESS;
}

// 查找键
template <typename Key, typename Value>
Value* map<Key, Value>::find(const Key& key) const {
    ULONG index = find_index(key);
    if (index == ULONG_MAX) {
        return nullptr;
    }
    return &data[index].value;
}

// 删除键值对
template <typename Key, typename Value>
NTSTATUS map<Key, Value>::erase(const Key& key) {
    ULONG index = find_index(key);
    if (index == ULONG_MAX) {
        return STATUS_NOT_FOUND;
    }

    for (ULONG i = index; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }

    size--;

    if (size == 0) {
        ExFreePoolWithTag(data, 'MapT');
        data = nullptr;
    }
    else {
        Pair* newdata = (Pair*)ExAllocatePoolWithTag(NonPagedPool, size * sizeof(Pair), 'MapT');
        if (!newdata) {
            return STATUS_INSUFFICIENT_RESOURCES;
        }

        RtlCopyMemory(newdata, data, size * sizeof(Pair));
        ExFreePoolWithTag(data, 'MapT');
        data = newdata;
    }

    return STATUS_SUCCESS;
}

// 清空容器
template <typename Key, typename Value>
void map<Key, Value>::clear() {
    if (data != nullptr) {
        ExFreePoolWithTag(data, 'MapT');
        data = nullptr;
    }
    size = 0;
}

// 查找索引
template <typename Key, typename Value>
ULONG map<Key, Value>::find_index(const Key& key) const {
    for (ULONG i = 0; i < size; ++i) {
        if (data[i].key == key) {
            return i;
        }
    }
    return ULONG_MAX;
}

// 析构函数
template <typename Key, typename Value>
map<Key, Value>::~map() {
    clear();
}



// 显式实例化常用的数据类型
template class map<int, int>;
template class map<int, float>;
template class map<int, double>;
template class map<int, long>;
template class map<int, unsigned long>;
template class map<int, char>;
template class map<int, unsigned char>;
template class map<int, short>;
template class map<int, unsigned short>;
template class map<int, long long>;
template class map<int, unsigned long long>;
template class map<int, ULONG64>;
template class map<int, ULONG>;
template class map<int, USHORT>;
template class map<int, UCHAR>;
template class map<int, uint64_t>;
template class map<int, int64_t>;
template class map<int, PVOID>;
template class map<PVOID, ULONG>;
template class map<PEPROCESS, BOOLEAN>;


template class map<ULONG, ULONG>;
template class map<ULONG, BOOLEAN>;
template class map<ULONG, PVOID>;
template class map<USHORT, ULONG>;
template class map<UCHAR, PVOID>;