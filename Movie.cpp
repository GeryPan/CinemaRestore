#include "Movie.h"
#include "Help_Program.h"
#include <cstring>
#include <iostream>

void Movie::free()
{
}

void Movie::copyFrom(const Movie& other)
{
    id = other.id;
    rate = other.rate;
    continuance = other.continuance;
    year = other.year;
    haul_id = other.haul_id;

    title = Help_Program::copy_str(other.title);
    genre = Help_Program::copy_str(other.genre);
    date = Help_Program::copy_str(other.date);
    start = Help_Program::copy_str(other.start);
    finish = Help_Program::copy_str(other.finish);
}

void Movie::write(std::ostream& os) const
{
    os.write((const char*)&id, sizeof(int));
    Help_Program::write(os, title);
    os.write((const char*)&rate, sizeof(float));
    os.write((const char*)&continuance, sizeof(int));
    os.write((const char*)&year, sizeof(int));
    os.write((const char*)&haul_id, sizeof(int));
    Help_Program::write(os, date);
    Help_Program::write(os, start);
    Help_Program::write(os, finish);
}

void Movie::read(std::istream& is)
{
    is.read((char*)&id, sizeof(int));
    title = Help_Program::read(is);
    is.read((char*)&rate, sizeof(float));
    is.read((char*)&continuance, sizeof(int));
    is.read((char*)&year, sizeof(int));
    is.read((char*)&haul_id, sizeof(int));
    date = Help_Program::read(is);
    start = Help_Program::read(is);
    finish = Help_Program::read(is);
}

Movie::Movie()
{
    title = nullptr;
    genre = nullptr;
    date = nullptr;
    start = nullptr;
    finish = nullptr;
}

Movie::Movie(const Movie& other)
{
    copyFrom(other);
}

Movie::Movie(unsigned new_id, unsigned new_haul_id, const MyString& new_title, float new_rate,
    unsigned new_continuance, const MyString& new_date, unsigned new_year, const MyString& new_genre,
    const MyString& new_start, const MyString& new_finish)
{
    id = new_id;
    title = Help_Program::copy_str(new_title);
    rate = new_rate;
    continuance = new_continuance;
    year = new_year;
    genre = Help_Program::copy_str(new_genre);
    haul_id = new_haul_id;
    date = Help_Program::copy_str(new_date);
    start = Help_Program::copy_str(new_start);
    finish = Help_Program::copy_str(new_finish);
}

void Movie::set_title(const MyString& new_title)
{
    title = Help_Program::copy_str(new_title);
}

void Movie::set_haul_id(unsigned new_haul_id)
{
    haul_id = new_haul_id;
}

Movie& Movie::operator=(const Movie& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

unsigned Movie::Id() const
{
    return id;
}

unsigned Movie::Haul_id() const
{
    return haul_id;
}

 MyString Movie::Title() const
{
    return title;
}

MyString Movie::Date() const
{
    return date;
}

MyString Movie::Start() const
{
    return start;
}

MyString Movie::Finish() const
{
    return finish;
}
Movie::~Movie()
{
    free();
}