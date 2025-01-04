#pragma once
#include "全局所需.h"
#include "kernel_vector.h"

class wstring {
private:
    vector<wchar_t> data;  // 使用 vector 来存储宽字符字符串数据
    mutable wchar_t* temp;
public:
    // 默认构造函数
    wstring();
    // 析构函数
    ~wstring();
    // 构造函数：从宽字符 C 风格字符串初始化
    wstring(const wchar_t* str);

    // 获取字符串的大小
    ULONG size() const;

    // 获取 C 风格宽字符串
    const wchar_t* c_str() const;

    // 追加一个宽字符
    NTSTATUS append(wchar_t c);

    // 追加 C 风格宽字符串
    NTSTATUS append(const wchar_t* str);

    // 获取指定位置的宽字符
    wchar_t at(ULONG index) const;

    // 运算符重载：宽字符追加
    wstring& operator+=(wchar_t c);

    // 运算符重载：C 风格宽字符串追加
    wstring& operator+=(const wchar_t* str);

    // 运算符重载：字符串比较
    bool operator==(const wstring& other) const;

    // 清空字符串
    void clear();

    // 查找子串
    ULONG find(const wchar_t* substr) const;

    // 删除指定位置的子串
    NTSTATUS erase(ULONG index, ULONG length);

    // 字符串反转
    void reverse();

    // 打印字符串（调试用）
    void print() const;
};