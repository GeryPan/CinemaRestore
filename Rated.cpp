#include "Rated.h"
#include "Movie_Factory.h"

void Rated::copyFrom(const Rated& other)
{
    movie = Movie_Factory::copy_movie(*other.movie);
    rate = other.rate;
}

Rated::Rated(const Rated& other)
{
    copyFrom(other);
}

Rated::Rated(Movie* new_movie, unsigned new_rate)
{
    movie = new_movie;
    rate = new_rate;
}

Rated& Rated::operator=(const Rated& other)
{
    copyFrom(other);
    return *this;
}

Rated* Rated::clone() const
{
    return new Rated(*this);
}

Movie* Rated::get_movie() const
{
    return movie;
}

unsigned Rated::get_rate() const
{
    return rate;
}
