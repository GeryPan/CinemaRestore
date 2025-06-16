#pragma once
#include "Help_Program.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include "User_Input.h"
#include <limits>
#include <cstring>
#include <cctype>

namespace User_Input
{
    unsigned enter_unsigned(const char* enter, unsigned min = std::numeric_limits<unsigned>::min(), unsigned max = std::numeric_limits<unsigned>::max())
    {
        unsigned value;
        while (true)
        {
            std::cout << enter;
            std::cin >> value;
            if (!std::cin.fail() && value >= min && value <= max)
            {
                User_Input::skip_line();
                return value;
            }
            std::cout << "Invalid input. ";
            std::cin.clear();
            User_Input::skip_line();
        }
        throw std::invalid_argument("Invalid unsigned input.");
    }

    float enter_float(const char* enter, float min = -std::numeric_limits<float>::max(), float max = std::numeric_limits<float>::max())
    {
        float value;
        while (true)
        {
            std::cout << enter;
            std::cin >> value;
            if (!std::cin.fail() && value >= min && value <= max)
            {
                User_Input::skip_line();
                return value;
            }

            std::cout << "Invalid input. ";
            std::cin.clear();
            User_Input::skip_line();
        }
        throw std::invalid_argument("Invalid float input.");
    }

    bool enter_bool(const char* enter)
    {
        std::string input;
        while (true)
        {
            std::cout << enter << " true/false: ";
            std::getline(std::cin, input);
            for (char& c : input)
                c = std::tolower(c);
            if (input == "true" || input == "1")
                return true;
            if (input == "false" || input == "0")
                return false;
            std::cout << "Invalid input.\n";
        }
        throw std::invalid_argument("Invalid boolean input.");
    }

    const char* enter_text(const char* enter, unsigned max_length)
    {
        static std::string buffer;
        while (true)
        {
            std::cout << enter;
            std::getline(std::cin, buffer);
            size_t start = buffer.find_first_not_of(" \t");
            size_t finish = buffer.find_last_not_of(" \t");
            if (start != std::string::npos && finish != std::string::npos)
                buffer = buffer.substr(start, finish - start + 1);
            else
                buffer.clear();

            if (buffer.empty())
            {
                std::cout << "Input cannot be empty.\n";
                continue;
            }

            if ((int)buffer.length() >= max_length)
            {
                std::cout << "Input too long. Maximum length is " << max_length - 1 << " characters.\n";
                continue;
            }

            return buffer.c_str();
        }
        throw std::invalid_argument("Invalid text input.");
    }

    const char* enter_date(const char* enter)
    {
        static std::string buffer;
        while (true) {
            std::cout << enter;
            std::getline(std::cin, buffer);

            if (buffer.length() != 10 || buffer[4] != '-' || buffer[7] != '-')
            {
                std::cout << "Invalid date format. Use YYYY-MM-DD.\n";
                continue;
            }

            bool valid = true;
            for (unsigned i = 0; i < 10; i++)
            {
                if (i == 4 || i == 7)
                    continue;
                if (buffer[i] > '9' || buffer[i] < '0')
                {
                    valid = false;
                    break;
                }
            }

            if (valid == false)
            {
                std::cout << "Invalid date format. Use YYYY-MM-DD.\n";
                continue;
            }

            unsigned year = std::stoi(buffer.substr(0, 4));
            unsigned month = std::stoi(buffer.substr(5, 2));
            unsigned day = std::stoi(buffer.substr(8, 2));

            if (month < 1 || month > 12)
            {
                std::cout << "Invalid month. Use value between 01 and 12.\n";
                continue;
            }

            unsigned daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
            bool isLeapYear = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
            if (isLeapYear && month == 2) daysInMonth[1] = 29;

            if (day < 1 || day > daysInMonth[month - 1]) {
                std::cout << "Invalid day for given month.\n";
                continue;
            }

            return buffer.c_str();
        }

        throw std::invalid_argument("Invalid date input."); // unreachable but required
    }

    const char* enter_time(const char* enter)
    {
        static std::string buffer;
        while (true)
        {
            std::cout << enter;
            std::getline(std::cin, buffer);
            if (Help_Program::is_valid(buffer.c_str()))
                return buffer.c_str();
            std::cout << "Invalid time format. Use HH:MM.\n";
        }
    }
    char* get_remaining(std::stringstream& ss, unsigned max_length) {
        std::string str;
        std::getline(ss, str);
        size_t first_char = str.find_first_not_of(" \t");
        if (first_char != std::string::npos)
            str = str.substr(first_char);
        else
            str.clear();
        if (str.empty()) {
            throw std::invalid_argument("No input provided.");
        }
        if ((int)str.length() >= max_length)
            throw std::invalid_argument("Remaining input too long.");

        char* result = new char[str.length() + 1];
        std::copy(str.begin(), str.end(), result);
        result[str.length()] = '\0';
        return result;
    }

    unsigned get_unsigned(std::stringstream& ss, unsigned min = std::numeric_limits<unsigned>::min(), unsigned max = std::numeric_limits<unsigned>::max())
    {
        std::string take;
        if (!(ss >> take)) throw std::invalid_argument("Missing int argument.");

        try {
            unsigned val = std::stoi(take);
            if (val >= min && val <= max) return val;
        }
        catch (...) {}

        throw std::invalid_argument("Invalid int argument.");
    }

    float get_float(std::stringstream& ss, float min = -std::numeric_limits<float>::max(), float max = std::numeric_limits<float>::max())
    {
        std::string token;
        if (!(ss >> token)) throw std::invalid_argument("Missing float argument.");

        try {
            float val = std::stof(token);
            if (val >= min && val <= max) return val;
        }
        catch (...) {}

        throw std::invalid_argument("Invalid float argument.");
    }

    bool get_bool(std::stringstream& ss)
    {
        std::string token;
        if (!(ss >> token)) throw std::invalid_argument("Missing boolean argument.");

        for (char& c : token) c = std::tolower(c);

        if (token == "true" || token == "1") return true;
        if (token == "false" || token == "0") return false;

        throw std::invalid_argument("Invalid boolean argument.");
    }

    const char* get_word(std::stringstream& ss, int max_length)
    {
        static std::string buffer;
        if (!(ss >> buffer) || buffer.length() >= (size_t)max_length)
            throw std::invalid_argument("Missing or too long word argument.");
        return buffer.c_str();
    }

    void skip_line()
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}
