#include"kernel_string.h"

// Ĭ�Ϲ��캯��
string::string() {
    temp = nullptr;
}

string::~string()
{
    clear();
}

// ���캯������ C ����ַ�����ʼ��
string::string(const char* str) {
    while (*str) {
        data.push_back(*str);
        str++;
    }
    temp = nullptr;
}

// ��ȡ�ַ����Ĵ�С
ULONG string::size() const {
    return data.size();
}

// ��ȡ C ����ַ���
const char* string::c_str() const {
    // ����ַ���Ϊ�գ����ؿտ��ַ���
    if (data.size() == 0) {
        return "";
    }
    if (temp != nullptr) {
        delete temp;
    }
    else {
        temp = new char[data.size() + 1];

        // ���� data �е����ݵ���ʱ�ڴ�
        for (ULONG i = 0; i < data.size(); ++i) {
            temp[i] = data[i];
        }
        // ��� null ��ֹ��
        temp[data.size()] = L'\0';
    }
    return temp;  // ������ʱ�ڴ��ָ��

}

// ׷��һ���ַ�
NTSTATUS string::append(char c) {
    return data.push_back(c);
}

// ׷�� C ����ַ���
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

// ��ȡָ��λ�õ��ַ�
char string::at(ULONG index) const {
    return data.at(index);
}

// ��������أ��ַ�׷��
string& string::operator+=(char c) {
    append(c);
    return *this;
}

// ��������أ�C ����ַ���׷��
string& string::operator+=(const char* str) {
    append(str);
    return *this;
}

// ��������أ��ַ����Ƚ�
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

// ����ַ���
void string::clear() {
    data.clear();
    if (temp != nullptr) {
        delete temp;
    }
}

// �����Ӵ�
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

    return ULONG_MAX;  // δ�ҵ�
}

// ɾ��ָ��λ�õ��Ӵ�
NTSTATUS string::erase(ULONG index, ULONG length) {
    if (index >= size()) {
        return STATUS_INVALID_PARAMETER;
    }

    // ɾ��ָ��λ�ÿ�ʼ���Ӵ�
    for (ULONG i = index; i < size() - length; ++i) {
        data[i] = data[i + length];
    }

    // ���´�С
    for (ULONG i = size() - length; i < size(); ++i) {
        data[i] = '\0';  // ��ն�����ַ�
    }

    // ���´�С
    for (ULONG i = 0; i < length; ++i) {
        data.pop_back();
    }

    return STATUS_SUCCESS;
}

// �ַ�����ת
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

// ��ӡ�ַ����������ã�
void string::print() const {
    if (data.size() > 0) {
        DbgPrint("%.*s\n", static_cast<int>(data.size()), &data[0]);
    }
    else {
        DbgPrint("(empty string)\n");
    }
}