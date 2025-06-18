#include "Help_Program.h"
#include <ctime>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <cstdio>

namespace Help_Program 
{

	unsigned convert_to_minutes(const MyString& str) 
	{
		unsigned hours = (str[0] - '0') * 10 + (str[1] - '0');
		unsigned minutes = (str[3] - '0') * 10 + (str[4] - '0');
		return hours * 60 + minutes;
	}

	MyString minutes_to_str(unsigned totalMinutes)
	{
		if (totalMinutes < 0 || totalMinutes >= 24 * 60)
			throw std::out_of_range("Minutes exceed 24-hour range.");

		char buffer[6]; // HH:MM + \0
		std::snprintf(buffer, sizeof(buffer), "%02d:%02d", totalMinutes / 60, totalMinutes % 60);
		return MyString(buffer);
	}

	bool coincident_time(const MyString& start1, const MyString& end1,
		const MyString& start2, const MyString& end2) {
		unsigned s1 = convert_to_minutes(start1);
		unsigned e1 = convert_to_minutes(end1);
		unsigned s2 = convert_to_minutes(start2);
		unsigned e2 = convert_to_minutes(end2);
		return s1 < e2&& s2 < e1;
	}

	bool is_valid(const MyString& str) {
		if (str.length() != 5 || str[2] != ':')
			return false;

		for (int i = 0; i < 5; ++i) {
			if (i == 2) continue;
			if (str[i] > '9' || str[i] < '0')
				return false;
		}

		int hours = (str[0] - '0') * 10 + (str[1] - '0');
		int minutes = (str[3] - '0') * 10 + (str[4] - '0');

		return hours >= 0 && hours < 24 && minutes >= 0 && minutes < 60;
	}

	MyString add_time(const MyString& timeStr, int minutesToAdd) {
		int totalMinutes = convert_to_minutes(timeStr) + minutesToAdd;
		return minutes_to_str(totalMinutes);
	}

	MyString remove_time(const MyString& timeStr, int minutesToRemove) {
		return add_time(timeStr, -minutesToRemove);
	}

	bool is_before(const MyString& date1, const MyString& date2) {
		return compare_strings(date1, date2) < 0;
	}

	MyString copy_str(const MyString& source) {
		return MyString(source);
	}

	MyString getCurrentDateStr() {
		time_t now = time(nullptr);
		tm local;
		localtime_s(&local, &now);

		char buffer[11]; // YYYY-MM-DD + \0
		std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &local);
		return MyString(buffer);
		//return "2027-06-17";
	}

	MyString getCurrentTimeStr() {
		time_t now = time(nullptr);
		tm local;
		localtime_s(&local, &now);

		char buffer[6]; // HH:MM + \0
		std::strftime(buffer, sizeof(buffer), "%H:%M", &local);
		return MyString(buffer);
	}

	void writeString(std::ostream& out, const MyString& str) {
		int len = str.length();
		out.write((char*)&len, sizeof(int));
		out.write(str.c_str(), len);
	}

	MyString read(std::istream& in) 
	{
		int len;
		in.read((char*)&len, sizeof(int));
		if (!in || len < 0) throw std::runtime_error("Corrupt or invalid string length");
		char* buffer = new char[len + 1];
		in.read(buffer, len);
		if (!in) {
			delete[] buffer;
			throw std::runtime_error("Failed to read string contents");
		}
		buffer[len] = '\0';
		MyString result(buffer);
		delete[] buffer;
		return result;
	}

	unsigned compare_strings(const MyString& str1, const MyString& str2) 
	{
		return std::strcmp(str1.c_str(), str2.c_str());
	}
}