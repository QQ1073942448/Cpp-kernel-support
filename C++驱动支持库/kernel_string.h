#pragma once
#include"ȫ������.h"
#include "kernel_vector.h"  

class string {
private:
    vector<char> data;  // ʹ�� vector ���洢�ַ�������
    mutable char* temp;
public:
    // Ĭ�Ϲ��캯��
    string();
    ~string();
    // ���캯������ C ����ַ�����ʼ��
    string(const char* str);

    // ��ȡ�ַ����Ĵ�С
    ULONG size() const;

    // ��ȡ C ����ַ���
    const char* c_str() const;

    // ׷��һ���ַ�
    NTSTATUS append(char c);

    // ׷�� C ����ַ���
    NTSTATUS append(const char* str);

    // ��ȡָ��λ�õ��ַ�
    char at(ULONG index) const;

    // ��������أ��ַ�׷��
    string& operator+=(char c);

    // ��������أ�C ����ַ���׷��
    string& operator+=(const char* str);

    // ��������أ��ַ����Ƚ�
    bool operator==(const string& other) const;

    // ����ַ���
    void clear();

    // �����Ӵ�
    ULONG find(const char* substr) const;

    // ɾ��ָ��λ�õ��Ӵ�
    NTSTATUS erase(ULONG index, ULONG length);

    // �ַ�����ת
    void reverse();

    // ��ӡ�ַ����������ã�
    void print() const;
};