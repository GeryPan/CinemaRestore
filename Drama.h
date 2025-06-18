#pragma once
#include "Movie.h"
#include "MyString.h"
#include <iostream>

class Drama : public Movie
{
    bool has_comedy_elements;
    void copyFrom(const Drama& other);
public:
    Drama(unsigned new_id, unsigned new_haul_id, const MyString& new_title, float new_rate,
        unsigned continuance, const MyString& new_date, unsigned new_year,
        const MyString& new_start, const MyString& new_finish, bool new_has_comedy_elements);
    Drama() = default;
    Drama(const Drama& other);
    Drama& operator=(const Drama& other);
    bool Comedy_elements() const;
    double calculate_ticket_price() const override;
    void print() const override;
    void serialize(std::ostream& os) const override;
    void deserialize(std::istream& is) override;
    Drama* clone() const override;
    virtual ~Drama() = default;
};