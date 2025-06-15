#pragma once
#include "Movie.h"

class Ticket 
{
    Movie* movie;
    unsigned row;
    unsigned col;
    void copyFrom(const Ticket& other);
public:
    Ticket(Movie* new_movie, unsigned new_row, unsigned new_col);
    Ticket(const Ticket& other);
    Ticket& operator=(const Ticket& other);
    Movie* Movie() const;
    unsigned Row() const;
    unsigned Col() const;
    bool is_expired(const char* current_date) const;
    void print() const;
    Ticket* clone() const;
    };
