#pragma once
#include "Movie.h"
#include <iostream>

class Action : public Movie 
{
    unsigned intensity; 
    void copyFrom(const Action& other);
public:
    Action() = default;
    Action(const Action& other);
    Action(unsigned new_id, unsigned new_haul_id, const char* new_title, float new_rate,
    unsigned continuance, const char* new_date, unsigned new_year,
        const char* new_start, const char* new_finish, unsigned new_intensity);
    Action& operator=(const Action& other);
    unsigned Intensity() const; 
    void print() const override;
    double calculate_ticket_price() const override;
    void serialize(std::ostream& os) const override;
    void deserialize(std::istream& is) override;
    Action* clone() const override;
    virtual ~Action() = default;
};
