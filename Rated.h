#pragma once
#include "Movie.h"

class Rated 
{
    Movie* movie;
    unsigned rate;
    void copyFrom(const Rated& other);
public:
    Rated(Movie* new_movie, unsigned new_rate);
    Rated(const Rated& other);
    Rated& operator=(const Rated& other);

    Rated* clone() const;

    Movie* get_movie() const;
    unsigned get_rate() const;
};
