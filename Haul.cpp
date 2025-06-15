#include "Haul.h"
#include <iostream>

void Haul::copyFrom(const Haul& other)
{
    id = other.id;
    rows = other.rows;
    cols = other.cols;
    allocate_seats();
    for (unsigned i = 0; i < rows; i++)
    {
        for (unsigned j = 0; j < cols; j++)
            seats[i][j] = other.seats[i][j];
    }
}

void Haul::allocate_seats()
{
    seats = new bool* [rows];
    for (unsigned i = 0; i < rows; i++)
    {
        seats[i] = new bool[cols];
        for (unsigned j = 0; j < cols; j++)
            seats[i][j] = false;
    }
}

void Haul::free_seats()
{
    for (unsigned i = 0; i < rows; i++)
        delete[] seats[i];
    delete[] seats;
}

Haul::Haul()
{
    id = 0;
    rows = 0;
    cols = 0;
}

Haul::Haul(const Haul& other)
{
    copyFrom(other);
}

Haul::Haul(unsigned new_id, unsigned new_rows, unsigned new_cols)
{
    id = new_id;
    rows = new_rows;
    cols = new_cols;
    allocate_seats();
}
    Haul& Haul::operator=(const Haul& other)
    {
        if (this != &other) 
        {
            free_seats();
            copyFrom(other);
        }
        return *this;
    }

    bool Haul::is_seat_free(unsigned row, unsigned col) const
    {
        return !seats[row][col] && row < rows && row >= 0 && col < cols && col >= 0;
    }

    void Haul::take_seat(unsigned row, unsigned col)
    {
        if (is_seat_free(row, col))
            seats[row][col] = true;
    }

    unsigned Haul::Id() const
    {
        return id;
    }

    unsigned Haul::Rows() const
    {
        return rows;
    }

    unsigned Haul::Cols() const
    {
        return cols;
    }

    void Haul::print() const
    {

    }

    Haul* Haul::clone() const
    {
        return new Haul(*this);
    }

    Haul::~Haul()
    {
        free_seats();
    }