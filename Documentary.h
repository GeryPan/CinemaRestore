#pragma once
#include "Movie.h"
#include <iostream>

class Documentary : public Movie 
{
private:
    MyString theme;
    bool based_on_true_story;
    void free();
    void copyFrom(const Documentary& other);
public:
    Documentary();
    Documentary(const Documentary& other);
    Documentary(unsigned new_id, unsigned new_haul_id, const MyString& new_title, float new_rate,
        unsigned continuance, const MyString& new_date, unsigned new_year, 
        const MyString& new_start, const MyString& new_finish, const MyString& new_theme, bool new_based_on_true_story);
    Documentary& operator=(const Documentary& other);
    MyString Theme() const;
    bool Based_on_true_story() const;
    double calculate_ticket_price() const override;
    void print() const override;
    void serialize(std::ostream& os) const override;
    void deserialize(std::istream& is) override;
    Documentary* clone() const override;
    virtual ~Documentary();
};