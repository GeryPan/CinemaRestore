#ifndef MY_STRING_H
#define MY_STRING_H

#include <cstddef>
#include <iostream>

class MyString {
private:
    char* data;
    size_t size;

    void copyFrom(const MyString& other);
    void moveFrom(MyString&& other);
    void free();

public:
    MyString(); // Empty string
    MyString(const char* cstr);
    MyString(const MyString& other);
    MyString(MyString&& other) noexcept;
    MyString& operator=(const MyString& other);
    MyString& operator=(MyString&& other) noexcept;
    ~MyString();

    size_t length() const;
    const char* c_str() const;

    char& operator[](size_t index);
    const char& operator[](size_t index) const;

    bool operator==(const MyString& other) const;

    static MyString fromInt(int value);
    static MyString fromDouble(double value);

    MyString operator+(const MyString& other) const;
    MyString operator+(const char* cstr) const;

    friend MyString operator+(const char* lhs, const MyString& rhs);

    friend std::ostream& operator<<(std::ostream& out, const MyString& str);
    friend std::istream& operator>>(std::istream& in, MyString& str);
};

#endif