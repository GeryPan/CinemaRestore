#include "Serialize_Watched_Movies.h"

Serialize_Watched_Movies::Serialize_Watched_Movies(unsigned new_movie_id)
{
	movie_id = new_movie_id;
}
void Serialize_Watched_Movies::set_movie_id(unsigned new_movie_id)
{
	movie_id = new_movie_id;
}

unsigned Serialize_Watched_Movies::Movie_id() const
{
	return movie_id;
}

Serialize_Watched_Movies* Serialize_Watched_Movies::clone() const
{
	return new Serialize_Watched_Movies(movie_id);
}