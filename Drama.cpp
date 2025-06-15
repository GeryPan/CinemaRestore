#include "Drama.h"
#include <iostream>

void Drama::copyFrom(const Drama& other)
{
    Movie::copyFrom(other);
    has_comedy_elements = other.has_comedy_elements;
}

Drama::Drama(unsigned new_id, unsigned new_haul_id, const char* new_title, float new_rate,
    unsigned continuance, const char* new_date, unsigned new_year,
    const char* new_start, const char* new_finish, bool new_has_comedy_elements)
    : Movie(new_id, new_haul_id, new_title, new_rate, "Drama", continuance,
        new_date, new_year, new_start, new_finish)
    {
     has_comedy_elements = new_has_comedy_elements;
    }

Drama::Drama(const Drama & other)
{
    copyFrom(other);
}

    Drama& Drama::operator=(const Drama & other)
    {
        if (this != &other) {
            free();
            copyFrom(other);
        }
        return *this;
    }

    bool Drama::Comedy_elements() const
    {
        return has_comedy_elements;
    }

    double Drama::calculate_ticket_price() const
    {
        const double basePrice = 8.0;
        return basePrice + (has_comedy_elements ? 2.0 : 0.0);
    }

    void Drama::print() const 
    {
        std::cout << "[Drama] " << Title()
            << (has_comedy_elements ? " (Comedy)" : "")
            << "\n Price: " << calculate_ticket_price()
            << "\n Date: " << Date()
            << "\n Start: " << Start()
            << "\n Finish: " << Finish()
            << "\n Haul: " << Haul_id()
            << std::endl;
    }

    void Drama::serialize(std::ostream & os) const 
    {
        char tag = 'D';
        os.write(&tag, sizeof(char));
        write(os);
        os.write((const char*)&has_comedy_elements, sizeof(bool));
    }

    void Drama::deserialize(std::istream & is) 
    {
        read(is);
        is.read((char*)&has_comedy_elements, sizeof(bool));
    }

    Drama* Drama::clone() const 
    {
        return new Drama(*this);
    }
