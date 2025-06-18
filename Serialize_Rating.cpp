#include "Serialize_Rating.h"
Serialize_Rating::Serialize_Rating(unsigned new_movie_id, unsigned new_rating)
{
	movie_id = new_movie_id;
	rating = new_rating;
}
Serialize_Rating* Serialize_Rating::clone() const
{
	return new Serialize_Rating(*this);
}