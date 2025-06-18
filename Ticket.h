#pragma once
#include "Movie.h"

class Ticket
{
    unsigned movie_id;
    unsigned row;
    unsigned col;
    void copyFrom(const Ticket& other);
public:
    Ticket(unsigned new_id, unsigned new_row, unsigned new_col);
    Ticket(const Ticket& other);
    Ticket& operator=(const Ticket& other);
    unsigned Movie_Id() const;
    unsigned Row() const;
    unsigned Col() const;
    bool is_expired(const Movie* movie, const MyString& currentDateStr) const;
    void print(const Movie* movie) const;
    Ticket* clone() const;
};