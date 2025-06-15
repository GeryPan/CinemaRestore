#pragma once
#include <sstream>
#include <limits>

namespace User_Input 
{
    unsigned enter_unsigned(const char* prompt, unsigned min = std::numeric_limits<int>::min(), unsigned max = std::numeric_limits<int>::max());
    float enter_float(const char* prompt, float min = -std::numeric_limits<float>::max(), float max = std::numeric_limits<float>::max());
    bool enter_bool(const char* prompt);
    const char* enter_text(const char* prompt, int max_length);
    const char* enter_date(const char* prompt);
    const char* enter_time(const char* prompt);

    char* get_remaining(std::stringstream& ss, unsigned max_length);
    unsigned get_unsigned(std::stringstream& ss, unsigned min = std::numeric_limits<int>::min(), unsigned max = std::numeric_limits<int>::max());
    float get_float(std::stringstream& ss, float min = -std::numeric_limits<float>::max(), float max = std::numeric_limits<float>::max());
    bool get_bool(std::stringstream& ss);
    const char* get_word(std::stringstream& ss, int max_length);
    void skip_line();
}
