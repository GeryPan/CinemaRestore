#pragma once
#include "MyString.h"
#include <iostream>

class Movie {
protected:
    unsigned id;
    unsigned haul_id;
    MyString title;
    float rate;
    MyString genre;
    unsigned continuance;
    MyString date;
    unsigned year;
    MyString start;
    MyString finish;

    void free();
    void copyFrom(const Movie& other);
    void write(std::ostream& os) const;
    void read(std::istream& is);
public:
    Movie();
    Movie(const Movie& other);
    Movie(unsigned new_id, unsigned new_haul_id, const MyString& new_title, float new_rate,
        unsigned continuance, const MyString& new_date, unsigned new_year, const MyString& new_genre,
        const MyString& new_start, const MyString& new_finish);
    Movie& operator=(const Movie& other);
    unsigned Id() const;
    unsigned Haul_id() const;
    MyString Title() const;
    MyString Date() const;
    MyString Start() const;
    MyString Finish() const;

    void set_title(const MyString& new_title);
    void set_haul_id(unsigned new_haul_id);

    virtual double calculate_ticket_price() const = 0;
    virtual void serialize(std::ostream& os) const = 0;
    virtual void deserialize(std::istream& is) = 0;
    virtual void print() const = 0;
    virtual Movie* clone() const = 0;
    virtual ~Movie();
};