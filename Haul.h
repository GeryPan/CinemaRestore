#pragma once
class Haul 
{
    unsigned id;
    bool** seats;
    unsigned rows;
    unsigned cols;
    void copyFrom(const Haul& other);
    void allocate_seats();
    void free_seats();

public:
    Haul();
    Haul(const Haul& other);
    Haul(unsigned new_id, unsigned new_rows, unsigned new_cols);
    Haul& operator=(const Haul& other);
    bool is_seat_free(unsigned row, unsigned col) const;
    void take_seat(unsigned row, unsigned col);
    unsigned Id() const;
    unsigned Rows() const;
    unsigned Cols() const;
    void print() const;
    Haul* clone() const;
    ~Haul();
    };