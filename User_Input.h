#pragma once
#include "MyString.h"
#include <sstream>
#include <limits>

namespace User_Input
{
    unsigned enter_unsigned(const MyString& enter, unsigned min = std::numeric_limits<unsigned>::min(),
    unsigned max = std::numeric_limits<unsigned>::max());
    float enter_float(const MyString& enter, float min = -std::numeric_limits<float>::max(), float max = std::numeric_limits<float>::max());
    bool enter_bool(const MyString& enter);
    MyString enter_text(const MyString& enter, unsigned max_length);
    MyString enter_date(const MyString& enter, const MyString& after = MyString(), const MyString& before = MyString());
    MyString enter_time(const MyString& enter, const MyString& after = MyString(), const MyString& before = MyString());

    MyString get_remaining(std::stringstream& ss, unsigned max_length);
    unsigned get_unsigned(std::stringstream& ss, unsigned min = std::numeric_limits<int>::min(), unsigned max = std::numeric_limits<int>::max());
    float get_float(std::stringstream& ss, float min = -std::numeric_limits<float>::max(), float max = std::numeric_limits<float>::max());
    bool get_bool(std::stringstream& ss);
    MyString get_word(std::stringstream& ss, unsigned max_length);
    void skip_line();
}