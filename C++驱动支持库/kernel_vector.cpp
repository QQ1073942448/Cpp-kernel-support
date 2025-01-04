#include "kernel_vector.h"


extern "C" int _fltused = 0;
template <typename T>
vector<T>::vector() : Size(0), data(nullptr) {}

template <typename T>
ULONG vector<T>::size() const {
    return Size;
}

template <typename T>
NTSTATUS vector<T>::push_back(const T& element) {
    T* newdata = (T*)ExAllocatePoolWithTag(NonPagedPool, (Size + 1) * sizeof(T), 'VecT');
    if (!newdata) {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    if (data != nullptr) {
        RtlCopyMemory(newdata, data, Size * sizeof(T));
        ExFreePoolWithTag(data, 'VecT');
    }

    newdata[Size] = element;
    data = newdata;
    Size++;

    return STATUS_SUCCESS;
}

template <typename T>
T vector<T>::at(ULONG index) const {
    if (index >= Size) {
        return T();
    }
    return data[index];
}


template <typename T>
T& vector<T>::operator[](ULONG index) {
    if (index >= Size) {
        // 内核代码中抛异常不方便，可选择返回静态对象以避免崩溃
        static T dummy = T();
        return dummy;
    }
    return data[index];
}

template <typename T>
const T& vector<T>::operator[](ULONG index) const {
    if (index >= Size) {
        static T dummy = T();
        return dummy;
    }
    return data[index];
}

template <typename T>
NTSTATUS vector<T>::pop_back() {
    if (Size > 0) {
        Size--;

        if (Size == 0 && data != nullptr) {
            ExFreePoolWithTag(data, 'VecT');
            data = nullptr;
            return STATUS_SUCCESS;
        }

        T* newdata = (T*)ExAllocatePoolWithTag(NonPagedPool, Size * sizeof(T), 'VecT');
        if (!newdata) {
            return STATUS_INSUFFICIENT_RESOURCES;
        }

        RtlCopyMemory(newdata, data, Size * sizeof(T));
        ExFreePoolWithTag(data, 'VecT');
        data = newdata;

        return STATUS_SUCCESS;
    }
    return STATUS_INVALID_PARAMETER;
}

template <typename T>
void vector<T>::clear() {
    if (data != nullptr) {
        ExFreePoolWithTag(data, 'VecT');
        data = nullptr;
    }
    Size = 0;
}

template <typename T>
ULONG vector<T>::find(const T& element) const {
    for (ULONG i = 0; i < Size; ++i) {
        if (data[i] == element) {
            return i;  
        }
    }
    return ULONG_MAX;  
}

template <typename T>
NTSTATUS vector<T>::erase(ULONG index) {
    if (index >= Size) {
        return STATUS_INVALID_PARAMETER;
    }

    for (ULONG i = index; i < Size - 1; ++i) {
        data[i] = data[i + 1];
    }


    data[Size - 1] = T(); 

    Size--;

    if (Size == 0) {
        ExFreePoolWithTag(data, 'VecT');
        data = nullptr;
    }
    else {
        T* newdata = (T*)ExAllocatePoolWithTag(NonPagedPool, Size * sizeof(T), 'VecT');
        if (!newdata) {
            return STATUS_INSUFFICIENT_RESOURCES;
        }

        RtlCopyMemory(newdata, data, Size * sizeof(T));
        ExFreePoolWithTag(data, 'VecT');
        data = newdata;
    }

    return STATUS_SUCCESS;
}

template <typename T>
vector<T>::~vector() {
    clear();
}


template class vector<int>;
template class vector<float>;
template class vector<double>;
template class vector<long>;
template class vector<unsigned long>;
template class vector<char>;
template class vector<wchar_t>;
template class vector<unsigned char>;
template class vector<short>;
template class vector<unsigned short>;
template class vector<long long>;
template class vector<unsigned long long>;
template class vector<ULONG64>;  
template class vector<ULONG>;  
template class vector<USHORT>;   
template class vector<UCHAR>;  
template class vector<uint64_t>; 
template class vector<int64_t>;  
template class vector<PVOID>;   






