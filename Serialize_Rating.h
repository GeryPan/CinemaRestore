#pragma once
#include <iostream>

class Serialize_Rating 
{
public:
    unsigned movie_id;
    unsigned rating;

    Serialize_Rating() = default;
    Serialize_Rating(unsigned new_movie_id, unsigned new_rating);
    friend std::ostream& operator<<(std::ostream& os, const Serialize_Rating& sr);
    friend std::istream& operator>>(std::istream& is, Serialize_Rating& sr);
};
