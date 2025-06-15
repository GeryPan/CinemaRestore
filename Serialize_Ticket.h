#pragma once
#include <iostream>

class Serialize_Ticket
{
public:
    unsigned movie_id;
    unsigned row;
    unsigned col;
    Serialize_Ticket() = default;
    Serialize_Ticket(unsigned new_movie_d, unsigned new_row, unsigned new_col);
};

namespace Operators {
    std::ostream& operator<<(std::ostream& os, const Serialize_Ticket& st);
    std::istream& operator>>(std::istream& is, Serialize_Ticket& st);
}
