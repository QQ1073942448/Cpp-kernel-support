#include"kernel_string.h"

// 默认构造函数
string::string() {
    temp = nullptr;
}

string::~string()
{
    clear();
}

// 构造函数：从 C 风格字符串初始化
string::string(const char* str) {
    while (*str) {
        data.push_back(*str);
        str++;
    }
    temp = nullptr;
}

// 获取字符串的大小
ULONG string::size() const {
    return data.size();
}

// 获取 C 风格字符串
const char* string::c_str() const {
    // 如果字符串为空，返回空宽字符串
    if (data.size() == 0) {
        return "";
    }
    if (temp != nullptr) {
        delete temp;
    }
    else {
        temp = new char[data.size() + 1];

        // 复制 data 中的内容到临时内存
        for (ULONG i = 0; i < data.size(); ++i) {
            temp[i] = data[i];
        }
        // 添加 null 终止符
        temp[data.size()] = L'\0';
    }
    return temp;  // 返回临时内存的指针

}

// 追加一个字符
NTSTATUS string::append(char c) {
    return data.push_back(c);
}

// 追加 C 风格字符串
NTSTATUS string::append(const char* str) {
    while (*str) {
        NTSTATUS status = data.push_back(*str);
        if (!NT_SUCCESS(status)) {
            return status;
        }
        str++;
    }
    return STATUS_SUCCESS;
}

// 获取指定位置的字符
char string::at(ULONG index) const {
    return data.at(index);
}

// 运算符重载：字符追加
string& string::operator+=(char c) {
    append(c);
    return *this;
}

// 运算符重载：C 风格字符串追加
string& string::operator+=(const char* str) {
    append(str);
    return *this;
}

// 运算符重载：字符串比较
bool string::operator==(const string& other) const {
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
void string::clear() {
    data.clear();
    if (temp != nullptr) {
        delete temp;
    }
}

// 查找子串
ULONG string::find(const char* substr) const {
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
NTSTATUS string::erase(ULONG index, ULONG length) {
    if (index >= size()) {
        return STATUS_INVALID_PARAMETER;
    }

    // 删除指定位置开始的子串
    for (ULONG i = index; i < size() - length; ++i) {
        data[i] = data[i + length];
    }

    // 更新大小
    for (ULONG i = size() - length; i < size(); ++i) {
        data[i] = '\0';  // 清空多余的字符
    }

    // 更新大小
    for (ULONG i = 0; i < length; ++i) {
        data.pop_back();
    }

    return STATUS_SUCCESS;
}

// 字符串反转
void string::reverse() {
    ULONG left = 0, right = size() - 1;
    while (left < right) {
        char temp = data.at(left);
        data[left] = data.at(right);
        data[right] = temp;
        ++left;
        --right;
    }
}

// 打印字符串（调试用）
void string::print() const {
    if (data.size() > 0) {
        DbgPrint("%.*s\n", static_cast<int>(data.size()), &data[0]);
    }
    else {
        DbgPrint("(empty string)\n");
    }
}