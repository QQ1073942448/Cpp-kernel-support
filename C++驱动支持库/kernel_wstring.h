#pragma once
#include "ȫ������.h"
#include "kernel_vector.h"

class wstring {
private:
    vector<wchar_t> data;  // ʹ�� vector ���洢���ַ��ַ�������
    mutable wchar_t* temp;
public:
    // Ĭ�Ϲ��캯��
    wstring();
    // ��������
    ~wstring();
    // ���캯�����ӿ��ַ� C ����ַ�����ʼ��
    wstring(const wchar_t* str);

    // ��ȡ�ַ����Ĵ�С
    ULONG size() const;

    // ��ȡ C �����ַ���
    const wchar_t* c_str() const;

    // ׷��һ�����ַ�
    NTSTATUS append(wchar_t c);

    // ׷�� C �����ַ���
    NTSTATUS append(const wchar_t* str);

    // ��ȡָ��λ�õĿ��ַ�
    wchar_t at(ULONG index) const;

    // ��������أ����ַ�׷��
    wstring& operator+=(wchar_t c);

    // ��������أ�C �����ַ���׷��
    wstring& operator+=(const wchar_t* str);

    // ��������أ��ַ����Ƚ�
    bool operator==(const wstring& other) const;

    // ����ַ���
    void clear();

    // �����Ӵ�
    ULONG find(const wchar_t* substr) const;

    // ɾ��ָ��λ�õ��Ӵ�
    NTSTATUS erase(ULONG index, ULONG length);

    // �ַ�����ת
    void reverse();

    // ��ӡ�ַ����������ã�
    void print() const;
};