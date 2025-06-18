#pragma once
class Haul
{
    unsigned id;
    unsigned rows;
    unsigned cols;
    void copyFrom(const Haul& other);

public:
    Haul();
    Haul(const Haul& other);
    Haul(unsigned new_id, unsigned new_rows, unsigned new_cols);
    Haul& operator=(const Haul& other);
    unsigned Id() const;
    unsigned Rows() const;
    unsigned Cols() const;
    Haul* clone() const;
    ~Haul();
};