#include "Help_Program.h"
#include <iostream>
#include <ctime>
#include <cstring>

char* Help_Program::read(std::istream& is)
{
	size_t length;
	is.read((char*)&length, sizeof(size_t));
	if (length < 0) 
		throw std::length_error("Invalid string length!");

	char* str = new char[length + 1];
	is.read(str, length);
	if (!is) {
		delete[] str;
		throw std::runtime_error("Can not read string contents!");
	}

	str[length] = '\0';

	return str;
}

void Help_Program::write(std::ostream& os, const char* str)
{
	size_t length;
	if (!str) {
		length = 0;
		os.write((char*)&length, sizeof(size_t));
		return;
	}
	length = strlen(str);
	os.write((char*)&length, sizeof(size_t));
	os.write(str, length);
}

unsigned Help_Program::convert_to_minutes(const char* time)
{
	unsigned hours = (time[0] - '0') * 10 + (time[1] - '0');
	unsigned minutes = (time[3] - '0') * 10 + (time[4] - '0');
	return hours * 60 + minutes;
}

bool Help_Program::coincident_time(const char* start_1, const char* start_2, const char* finish_1, const char* finish_2)
{
	int s_1 = convert_to_minutes(start_1);
	int f_1 = convert_to_minutes(finish_1);
	int s_2 = convert_to_minutes(start_2);
	int f_2 = convert_to_minutes(finish_2);
	return s_1 < f_2 && s_2 < f_1;
}

bool Help_Program::is_valid(const char* time)
{
	if (strlen(time) != 5 || time[2] != ':')
		return false;

	for (unsigned i = 0; i < 5; i++)
	{
		if (i == 2) continue;
		if (time[i] < '0' || time[i] > '9')
			return false;
	}

	unsigned hours = (time[0] - '0') * 10 + (time[1] - '0');
	unsigned minutes = (time[3] - '0') * 10 + (time[4] - '0');

	return hours >= 0 && hours < 24 && minutes >= 0 && minutes < 60;
}

bool Help_Program::is_before(const char* date_1, const char* date_2)
{
	return strcmp(date_1, date_2) < 0;
}
char* Help_Program::current_time()
{
	time_t now = time(nullptr);
	tm local;
	localtime_s(&local, &now);
	char* buffer = new char[11]; 
	strftime(buffer, 11, "%Y-%m-%d", &local);
	return buffer;
}

char* Help_Program::copy_str(const char* str)
{
	if (!str) return nullptr;
	size_t length = strlen(str);
	char* new_str = new char[length + 1];
	for (size_t i = 0; i < length; i++)
	{
		new_str[i] = str[i];
	}
	new_str[length] = '\0';
	return new_str;
}
