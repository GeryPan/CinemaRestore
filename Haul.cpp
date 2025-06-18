#include "Haul.h"
#include <iostream>

void Haul::copyFrom(const Haul& other)
{
    id = other.id;
    rows = other.rows;
    cols = other.cols;
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
}
Haul& Haul::operator=(const Haul& other)
{
    if (this != &other)
    {
        copyFrom(other);
    }
    return *this;
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

Haul* Haul::clone() const
{
    return new Haul(*this);
}

Haul::~Haul()
{
}