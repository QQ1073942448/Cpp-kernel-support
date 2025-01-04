#pragma once
#include"全局所需.h"
#include "kernel_vector.h"  

class string {
private:
    vector<char> data;  // 使用 vector 来存储字符串数据
    mutable char* temp;
public:
    // 默认构造函数
    string();
    ~string();
    // 构造函数：从 C 风格字符串初始化
    string(const char* str);

    // 获取字符串的大小
    ULONG size() const;

    // 获取 C 风格字符串
    const char* c_str() const;

    // 追加一个字符
    NTSTATUS append(char c);

    // 追加 C 风格字符串
    NTSTATUS append(const char* str);

    // 获取指定位置的字符
    char at(ULONG index) const;

    // 运算符重载：字符追加
    string& operator+=(char c);

    // 运算符重载：C 风格字符串追加
    string& operator+=(const char* str);

    // 运算符重载：字符串比较
    bool operator==(const string& other) const;

    // 清空字符串
    void clear();

    // 查找子串
    ULONG find(const char* substr) const;

    // 删除指定位置的子串
    NTSTATUS erase(ULONG index, ULONG length);

    // 字符串反转
    void reverse();

    // 打印字符串（调试用）
    void print() const;
};