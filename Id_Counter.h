#pragma once
#include <cstring>
#include <iostream>
#include "MyString.h"

class Id_Counter {
private:
    MyString name;
    unsigned value;

    void free();
    void copyFrom(const Id_Counter& other);

public:
    Id_Counter();
    Id_Counter(const Id_Counter& other);
    Id_Counter(const MyString& new_name, unsigned start = 0);
    Id_Counter& operator=(const Id_Counter& other);
    void increase();
    MyString Name() const;
    unsigned Value() const;
    friend std::ostream& operator<<(std::ostream& os, const Id_Counter& id_counter);
    friend std::istream& operator>>(std::istream& is, Id_Counter& id_counter);
    Id_Counter* clone() const;
    ~Id_Counter();
};