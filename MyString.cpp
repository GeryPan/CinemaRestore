#include "MyString.h"
#include <cstring>
#include <stdexcept>
#include <cstdio>  // for snprintf

void MyString::copyFrom(const MyString& other) {
    size = other.size;
    data = new char[size + 1];
    std::memcpy(data, other.data, size + 1); // copy null terminator too
}

void MyString::moveFrom(MyString&& other) {
    data = other.data;
    size = other.size;
    other.data = nullptr;
    other.size = 0;
}

void MyString::free() {
    delete[] data;
    data = nullptr;
    size = 0;
}

MyString::MyString() : data(new char[1]), size(0) {
    data[0] = '\0';
}

MyString::MyString(const char* cstr) {
    if (!cstr) {
        data = new char[1];
        data[0] = '\0';
        size = 0;
    }
    else {
        size = std::strlen(cstr);
        data = new char[size + 1];
        std::memcpy(data, cstr, size + 1);
    }
}

MyString::MyString(const MyString& other) {
    copyFrom(other);
}

MyString::MyString(MyString&& other) noexcept {
    moveFrom(std::move(other));
}

MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

MyString& MyString::operator=(MyString&& other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

MyString::~MyString() {
    free();
}

size_t MyString::length() const {
    return size;
}

const char* MyString::c_str() const {
    return data;
}

char& MyString::operator[](size_t index) {
    if (index >= size) throw std::out_of_range("Index out of bounds");
    return data[index];
}

const char& MyString::operator[](size_t index) const {
    if (index >= size) throw std::out_of_range("Index out of bounds");
    return data[index];
}

bool MyString::operator==(const MyString& other) const {
    return std::strcmp(data, other.data) == 0;
}

MyString MyString::fromInt(int value) {
    char buffer[32];
    std::snprintf(buffer, sizeof(buffer), "%d", value);
    return MyString(buffer);
}

MyString MyString::fromDouble(double value) {
    char buffer[64];
    std::snprintf(buffer, sizeof(buffer), "%.6f", value); // 6 digits precision
    return MyString(buffer);
}

MyString MyString::operator+(const MyString& other) const {
    size_t newSize = size + other.size;
    char* newData = new char[newSize + 1];
    std::memcpy(newData, data, size);
    std::memcpy(newData + size, other.data, other.size + 1); // +1 to copy null terminator
    MyString result(newData);
    delete[] newData;
    return result;
}

MyString MyString::operator+(const char* cstr) const {
    return *this + MyString(cstr);
}

MyString operator+(const char* lhs, const MyString& rhs) {
    return MyString(lhs) + rhs;
}