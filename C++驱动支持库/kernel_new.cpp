#include"kernel_new.h"
//÷ÿ‘ÿnew”Îdelete
void* operator new(size_t size) {
    void* ptr = ExAllocatePoolWithTag(NonPagedPool, size, 'newT');
    if (!ptr) {
        ExRaiseStatus(STATUS_INSUFFICIENT_RESOURCES);
    }
    return ptr;
}

void* operator new[](size_t size) {
    void* ptr = ExAllocatePoolWithTag(NonPagedPool, size, 'arrT');
    if (!ptr) {
        ExRaiseStatus(STATUS_INSUFFICIENT_RESOURCES);
    }
    return ptr;
}

void operator delete(void* ptr, size_t size) {
    if (ptr) {
        ExFreePoolWithTag(ptr, 'newT');
    }
}

void operator delete[](void* ptr, size_t size) {
    if (ptr) {
        ExFreePoolWithTag(ptr, 'arrT');
    }

}