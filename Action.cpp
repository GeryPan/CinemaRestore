
#include "Action.h"
#include <iostream>

void Action::copyFrom(const Action& other)
{
    Movie::copyFrom(other);
    intensity = other.intensity;
}

Action::Action(const Action& other)
{
    copyFrom(other);
}

Action::Action(unsigned new_id, unsigned new_haul_id, const MyString& new_title, float new_rate,
    unsigned continuance, const MyString& new_date, unsigned new_year,
    const MyString& new_start, const MyString& new_finish, unsigned new_intensity)
    : Movie(new_id, new_haul_id, new_title, new_rate,
         continuance, new_date, new_year, "Action", new_start, new_finish)
{
    intensity = new_intensity;
}
Action& Action::operator=(const Action& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

unsigned Action::Intensity() const
{
    return intensity;
}

void Action::print() const
{
    std::cout << "[Action] " << Title()
        << "\n Intensity: " << Intensity()
        << "\n Price: " << calculate_ticket_price()
        << "\n Date: " << Date()
        << "\n Start: " << Start()
        << "\n Finish: " << Finish()
        << "\n Haul: " << Haul_id()
        << std::endl;
}

double Action::calculate_ticket_price() const
{
    const double base_price = 10.0;
    return base_price + intensity * 1.5;
}

void Action::serialize(std::ostream& os) const
{
    char tag = 'A';
    os.write(&tag, sizeof(char));
    write(os);
    os.write((const char*)&intensity, sizeof(unsigned));
}

void Action::deserialize(std::istream& is)
{
    read(is);
    is.read((char*)&intensity, sizeof(unsigned));
}

Action* Action::clone() const
{
    return new Action(*this);
}
