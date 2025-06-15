#include "Ticket.h"
#include "Help_Program.h"
#include "Movie.h"
#include <iostream>
#include <cstring>

void Ticket::copyFrom(const Ticket& other)
{
    movie = other.movie; // Tickets don't own movies;
    row = other.row;
    col = other.col;
}

Ticket::Ticket(Movie* new_movie, unsigned new_row, unsigned new_col)
{
    movie = new_movie;
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


    Movie* Ticket::Movie() const
    {
        return movie;
    }

    unsigned Ticket::Row() const
    {
        return row;
    }

    unsigned Ticket::Col() const
    {
        return col;
    }

    bool Ticket::is_expired(const char* current_date) const
    {
        return strcmp(movie->Date(), current_date) < 0;
    }

    void Ticket::print() const
    {
        std::cout << "Ticket for \"" << movie->Title() << "\" on " << movie->Date()
            << " at " << movie->Start() << " | Seat: (" << row << "," << col << ")"
            << " | Price: " << movie->calculate_ticket_price() << std::endl;
    }

    Ticket* Ticket::clone() const
    {
        return new Ticket(*this);
    }