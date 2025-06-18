#include "Documentary.h"
#include "Help_Program.h"
#include "Serialize.h"
#include <cstring>
#include <iostream>

void Documentary::free()
{
}

void Documentary::copyFrom(const Documentary& other)
{
    Movie::copyFrom(other);
    theme = Help_Program::copy_str(other.theme);
    based_on_true_story = other.based_on_true_story;
}

Documentary::Documentary()
{
    theme = nullptr;
    based_on_true_story = false;
}
Documentary::Documentary(const Documentary& other)
{
    copyFrom(other);
}

Documentary::Documentary(unsigned new_id, unsigned new_haul_id, const MyString& new_title, float new_rate,
    unsigned continuance, const MyString& new_date, unsigned new_year, 
    const MyString& new_start, const MyString& new_finish, const MyString& new_theme, bool new_based_on_true_story)
    : Movie(new_id, new_haul_id, new_title, new_rate, 
        continuance, new_date, new_year, "Documentary", new_start, new_finish)
{
    theme = Help_Program::copy_str(new_theme);
    based_on_true_story = new_based_on_true_story;
}
Documentary& Documentary::operator=(const Documentary& other)
{
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

MyString  Documentary::Theme() const 
{
    return theme;
}

bool Documentary::Based_on_true_story() const
{
    return based_on_true_story;
}
double Documentary::calculate_ticket_price() const
{
    const double base_price = 7.0;
    return base_price + (based_on_true_story ? 3.0 : 0.0);
}

void Documentary::print() const
{
    std::cout << "[Documentary] " << Title()
        << " | Theme: " << theme
        << (based_on_true_story ? " (Based on true story)" : "")
        << "\n Price: " << calculate_ticket_price()
        << "\n Date: " << Date()
        << "\n Start: " << Start()
        << "\n Finish: " << Finish()
        << "\n Haul: " << Haul_id()
        << std::endl;
}
void Documentary::serialize(std::ostream& os) const
{
    char tag = 'C';
    os.write(&tag, sizeof(char));
    write(os);
    Help_Program::write(os, theme);
    os.write((const char*)&based_on_true_story, sizeof(bool));
}

void Documentary::deserialize(std::istream& is)
{
    read(is);
    theme = Help_Program::read(is);
    is.read((char*)&based_on_true_story, sizeof(bool));
}
Documentary* Documentary::clone() const
{
    return new Documentary(*this);
}

Documentary::~Documentary()
{
    free();
}