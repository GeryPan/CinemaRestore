#pragma once
#include "User_Input.h"
#include "Help_Program.h"
#include "MyString.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include "User_Input.h"
#include <limits>
#include <cstring>
#include <cctype>

namespace User_Input
{
    unsigned enter_unsigned(const MyString& enter, unsigned min, unsigned max)
    {
        unsigned value;
        while (true) {
            std::cout << enter.c_str();
            std::cin >> value;
            if (!std::cin.fail() && value >= min && value <= max) 
            {
                User_Input::skip_line();
                return value;
            }
            std::cout << "Invalid input. " << std::endl;
            std::cin.clear();
            User_Input::skip_line();
        }
        throw std::invalid_argument("Invalid int input.");
    }

    float enter_float(const MyString& enter, float min, float max)
    {
        float value;
        while (true) {
            std::cout << enter.c_str();
            std::cin >> value;
            if (!std::cin.fail() && value >= min && value <= max) {
                User_Input::skip_line();
                return value;
            }
            std::cout << "Invalid input. " << std::endl;
            std::cin.clear();
            User_Input::skip_line();
        }

        throw std::invalid_argument("Invalid float input.");
    }

    bool enter_bool(const MyString& enter)
    {
        std::string input;
        while (true) {
            std::cout << enter.c_str() << " (true/false): ";
            std::getline(std::cin, input);

            for (char& c : input)
                c = std::tolower(c);

            if (input == "true" || input == "1") return true;
            if (input == "false" || input == "0") return false;

            std::cout << "Invalid input." << std::endl;
        }

        throw std::invalid_argument("Invalid boolean input.");
    }

    MyString enter_text(const MyString& enter, unsigned max_length)
    {
        std::string buffer;
        while (true) 
        {
            std::cout << enter.c_str();
            std::getline(std::cin, buffer);

            size_t start = buffer.find_first_not_of(" \t");
            size_t end = buffer.find_last_not_of(" \t");

            if (start != std::string::npos && end != std::string::npos)
                buffer = buffer.substr(start, end - start + 1);
            else
                buffer.clear();

            if (buffer.empty()) {
                std::cout << "Input cannot be empty." << std::endl;
                continue;
            }

            if ((int)buffer.length() >= max_length) {
                std::cout << "Input too long. Maximum length is " << max_length - 1 << " characters.\n";
                continue;
            }
            return MyString(buffer.c_str());
        }
    }

    MyString enter_date(const MyString& enter, const MyString& after, const MyString& before)
    {
        std::string buffer;

        while (true) 
        {
            std::cout << enter.c_str();
            std::getline(std::cin, buffer);

            if (buffer.length() != 10 || buffer[4] != '-' || buffer[7] != '-') 
            {
                std::cout << "Invalid date format. Use YYYY-MM-DD." << std::endl;
                continue;
            }
            bool valid = true;
            for (int i = 0; i < 10; i++)
            {
                if (i == 4 || i == 7) continue;
                if (buffer[i]>'9' || buffer[i]<'0') 
                {
                    valid = false;
                    break;
                }
            }
            if (!valid) 
            {
                std::cout << "Invalid date format. Use YYYY-MM-DD." << std::endl;
                continue;
            }
            unsigned year = std::stoi(buffer.substr(0, 4));
            unsigned month = std::stoi(buffer.substr(5, 2));
            unsigned day = std::stoi(buffer.substr(8, 2));
             if (month < 1 || month > 12) 
             {
                std::cout << "Invalid month. Use value between 01 and 12." << std::endl;
                continue;
            }

             unsigned daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
            bool isLeapYear = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
            if (isLeapYear && month == 2) daysInMonth[1] = 29;
            if (day < 1 || day > daysInMonth[month - 1]) 
            {
                std::cout << "Invalid day for given month." << std::endl;
                continue;
            }
             MyString input(buffer.c_str());
            if (after.length() > 0 && Help_Program::is_before(input, after)) 
            {
                std::cout << "Date must be after or equal to " << after.c_str() << "." << std::endl;
                continue;
            }
            if (before.length() > 0 && Help_Program::is_before(before, input)) 
            {
                std::cout << "Date must be before or equal to " << before.c_str() << "." << std::endl;
                continue;
            }
            return input;
        }
    }
    MyString enter_time(const MyString& enter, const MyString& after, const MyString& before)
    {
        std::string buffer;
        while (true)
        {
            std::cout << enter.c_str();
            std::getline(std::cin, buffer);
            MyString input(buffer.c_str());
            if (!Help_Program::is_valid(input))
            {
                std::cout << "Invalid time format. Use HH:MM (24h)." << std::endl;
                continue;
            }
            if (after.length() > 0 && Help_Program::compare_strings(input, after) < 0)
            {
                std::cout << "Time must be after or equal to " << after.c_str() << ".\n";
                continue;
            }
            if (before.length() > 0 && Help_Program::compare_strings(input, before) > 0)
            {
                std::cout << "Time must be before or equal to " << before.c_str() << ".\n";
                continue;
            }
            return input;
        }
        throw std::invalid_argument("Invalid time.");
    }
        MyString get_remaining(std::stringstream& ss, unsigned max_length)
        {
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

            return MyString(str.c_str());
        }

    unsigned get_unsigned(std::stringstream& ss, unsigned min, unsigned max)
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

    float get_float(std::stringstream& ss, float min, float max)
    {
        std::string token;
        if (!(ss >> token)) 
            throw std::invalid_argument("Missing float argument.");
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

    MyString get_word(std::stringstream& ss, unsigned max_length)
    {
        std::string buffer;
        if (!(ss >> buffer) || buffer.length() >= max_length)
            throw std::invalid_argument("Missing or too long word argument.");
        return MyString(buffer.c_str());
    }

    void skip_line()
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}