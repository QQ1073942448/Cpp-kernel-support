#include "kernel_wstring.h"
#include"kernel_new.h"
// 默认构造函数
wstring::wstring() {
    temp = nullptr;
}

// 为了确保释放临时内存，修改析构函数
wstring::~wstring() {
    clear();
}

// 构造函数：从 C 风格宽字符串初始化
wstring::wstring(const wchar_t* str) {
    while (*str) {
        data.push_back(*str);
        str++;
    }
    temp = nullptr;
}

// 获取字符串的大小
ULONG wstring::size() const {
    return data.size();
}

// 获取 C 风格宽字符串
const wchar_t* wstring::c_str() const {

    // 如果字符串为空，返回空宽字符串
    if (data.size() == 0) {
        return L"";
    }
    if (temp != nullptr) {
        delete temp;
    }
    else {
        temp= new wchar_t[data.size() + 1];
        for (ULONG i = 0; i < data.size(); ++i) {
            temp[i] = data[i];
        }
        // 添加 null 终止符
        temp[data.size()] = L'\0';
    }
    return temp;  // 返回临时内存的指针
}

// 追加一个宽字符
NTSTATUS wstring::append(wchar_t c) {
    return data.push_back(c);
}

// 追加 C 风格宽字符串
NTSTATUS wstring::append(const wchar_t* str) {
    while (*str) {
        NTSTATUS status = data.push_back(*str);
        if (!NT_SUCCESS(status)) {
            return status;
        }
        str++;
    }
    return STATUS_SUCCESS;
}

// 获取指定位置的宽字符
wchar_t wstring::at(ULONG index) const {
    return data.at(index);
}

// 运算符重载：宽字符追加
wstring& wstring::operator+=(wchar_t c) {
    append(c);
    return *this;
}

// 运算符重载：C 风格宽字符串追加
wstring& wstring::operator+=(const wchar_t* str) {
    append(str);
    return *this;
}

// 运算符重载：字符串比较
bool wstring::operator==(const wstring& other) const {
    if (this->size() != other.size()) {
        return false;
    }

    for (ULONG i = 0; i < this->size(); ++i) {
        if (this->at(i) != other.at(i)) {
            return false;
        }
    }

    return true;
}

// 清空字符串
void wstring::clear() {
    data.clear();
    if (temp != nullptr) {
        delete temp;
    }
}

// 查找子串
ULONG wstring::find(const wchar_t* substr) const {
    ULONG sub_size = 0;
    while (substr[sub_size]) {
        sub_size++;
    }

    for (ULONG i = 0; i <= this->size() - sub_size; ++i) {
        bool match = true;
        for (ULONG j = 0; j < sub_size; ++j) {
            if (this->at(i + j) != substr[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            return i;
        }
    }

    return ULONG_MAX;  // 未找到
}

// 删除指定位置的子串
NTSTATUS wstring::erase(ULONG index, ULONG length) {
    if (index >= size()) {
        return STATUS_INVALID_PARAMETER;
    }

    for (ULONG i = index; i < size() - length; ++i) {
        data[i] = data[i + length];
    }

    for (ULONG i = 0; i < length; ++i) {
        data.pop_back();
    }

    return STATUS_SUCCESS;
}

// 字符串反转
void wstring::reverse() {
    ULONG left = 0, right = size() - 1;
    while (left < right) {
        wchar_t temp = data.at(left);
        data[left] = data.at(right);
        data[right] = temp;
        ++left;
        --right;
    }
}

// 打印字符串（调试用）
void wstring::print() const {
    if (data.size() > 0) {
        DbgPrint("%.*S\n", static_cast<int>(data.size()), &data[0]);  // 注意 %S 用于宽字符输出
    }
    else {
        DbgPrint("(empty wstring)\n");
    }
}