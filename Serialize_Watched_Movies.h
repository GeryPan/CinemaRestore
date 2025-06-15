#pragma once
#include <iostream>

class Serialize_Watched_Movies
{
	unsigned movie_id;
public:
	Serialize_Watched_Movies() = default;
	Serialize_Watched_Movies(unsigned new_movie_id);
	void set_movie_id(unsigned new_movie_id);
	unsigned Movie_id() const;
	friend std::ostream& operator<<(std::ostream& os, const Serialize_Watched_Movies& swm);
	friend std::istream& operator>>(std::istream& is, Serialize_Watched_Movies& swm);
	Serialize_Watched_Movies* clone() const;
};