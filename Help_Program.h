#pragma once

#include "Vector.hpp"
#include <functional>
#include <iostream>

namespace Help_Program 
{
    char* read(std::istream& is);
    void write(std::ostream& out, const char* str);
    unsigned convert_to_minutes(const char* time);
    bool coincident_time(const char* start_1, const char* start_2, const char* finish_1, const char* finish_2);
    bool is_valid(const char* time);
    bool is_before(const char* date_1, const char* date_2);
    char* current_time(); 
    char* copy_str(const char* str);
}
