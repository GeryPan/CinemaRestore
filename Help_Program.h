#pragma once

#include "Vector.hpp"
#include "MyString.h"
#include <functional>
#include <iostream>

namespace Help_Program
{
    MyString read(std::istream& in);
    void write(std::ostream& out, const MyString& str);
    unsigned convert_to_minutes(const MyString& timeStr);
    MyString minutes_to_str(unsigned minutes);
    bool coincident_time(const MyString& start1, const MyString& end1,
        const MyString& start2, const MyString& end2);
    bool is_valid(const MyString& timeStr);
    bool is_before(const MyString& date1, const MyString& date2);
    MyString copy_str(const MyString& source);
    MyString getCurrentDateStr(); 
    MyString getCurrentTimeStr();
    MyString add_time(const MyString& timeStr, int minutesToAdd);
    MyString remove_time(const MyString& timeStr, int minutesToRemove);
    unsigned compare_strings(const MyString& str1, const MyString& str2);
}