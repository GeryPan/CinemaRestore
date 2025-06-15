#pragma once
#include "Movie.h"
#include "Id_Counter_Manager.h"
#include <fstream>

class Movie_Factory 
{
public:
	static Movie* create_movie(Id_Counter_Manager& new_id, const char* genre);
	static Movie* copy_movie(const Movie& movie);
	static Movie* deserialize_movie(std::istream& is);
};