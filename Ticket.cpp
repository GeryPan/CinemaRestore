#include "Ticket.h"
#include "Help_Program.h"
#include "Movie.h"
#include "MyString.h"
#include <iostream>
#include <cstring>

void Ticket::copyFrom(const Ticket& other)
{
    movie_id = other.movie_id;
    row = other.row;
    col = other.col;
}

Ticket::Ticket(unsigned new_id, unsigned new_row, unsigned new_col)
{
    movie_id = new_id;
    row = new_row;
    col = new_col;
}

Ticket::Ticket(const Ticket& other)
{
    copyFrom(other);
}

Ticket& Ticket::operator=(const Ticket& other)
{
    copyFrom(other);
    return *this;
}


unsigned Ticket::Movie_Id() const
{
    return movie_id;
}

unsigned Ticket::Row() const
{
    return row;
}

unsigned Ticket::Col() const
{
    return col;
}

bool Ticket::is_expired(const Movie* movie, const MyString& currentDateStr) const
{
    return Help_Program::compare_strings(movie->Date(), currentDateStr) < 0;
}

void Ticket::print(const Movie* movie) const
{
    std::cout << "Ticket for \"" << movie->Title().c_str() << "\" on " << movie->Date().c_str()
        << " at " << movie->Start().c_str() << " | Seat: (" << row << "," << col << ")"
        << " | Price: " << movie->calculate_ticket_price() << std::endl;
}

Ticket* Ticket::clone() const
{
    return new Ticket(*this);
}