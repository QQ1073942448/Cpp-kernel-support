#include "kernel_wstring.h"
#include"kernel_new.h"
// Ĭ�Ϲ��캯��
wstring::wstring() {
    temp = nullptr;
}

// Ϊ��ȷ���ͷ���ʱ�ڴ棬�޸���������
wstring::~wstring() {
    clear();
}

// ���캯������ C �����ַ�����ʼ��
wstring::wstring(const wchar_t* str) {
    while (*str) {
        data.push_back(*str);
        str++;
    }
    temp = nullptr;
}

// ��ȡ�ַ����Ĵ�С
ULONG wstring::size() const {
    return data.size();
}

// ��ȡ C �����ַ���
const wchar_t* wstring::c_str() const {

    // ����ַ���Ϊ�գ����ؿտ��ַ���
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
        // ��� null ��ֹ��
        temp[data.size()] = L'\0';
    }
    return temp;  // ������ʱ�ڴ��ָ��
}

// ׷��һ�����ַ�
NTSTATUS wstring::append(wchar_t c) {
    return data.push_back(c);
}

// ׷�� C �����ַ���
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

// ��ȡָ��λ�õĿ��ַ�
wchar_t wstring::at(ULONG index) const {
    return data.at(index);
}

// ��������أ����ַ�׷��
wstring& wstring::operator+=(wchar_t c) {
    append(c);
    return *this;
}

// ��������أ�C �����ַ���׷��
wstring& wstring::operator+=(const wchar_t* str) {
    append(str);
    return *this;
}

// ��������أ��ַ����Ƚ�
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

// ����ַ���
void wstring::clear() {
    data.clear();
    if (temp != nullptr) {
        delete temp;
    }
}

// �����Ӵ�
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

    return ULONG_MAX;  // δ�ҵ�
}

// ɾ��ָ��λ�õ��Ӵ�
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

// �ַ�����ת
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

// ��ӡ�ַ����������ã�
void wstring::print() const {
    if (data.size() > 0) {
        DbgPrint("%.*S\n", static_cast<int>(data.size()), &data[0]);  // ע�� %S ���ڿ��ַ����
    }
    else {
        DbgPrint("(empty wstring)\n");
    }
}