#include "Update_Movie_Haul.h"
#include "Help_Program.h"
#include "User_Input.h"
#include <iostream>
#include <cstring>

const char* Name()
{
    return "pdate-movie-haul";
}
bool need_admin()
{
    return true;
}
bool need_login()
{
    return false;
}

void execute(std::stringstream& args, User*& user, Cinema& cinema,
    Vector<User*>& users, Id_Counter_Manager& id_manager)
{
	unsigned movie_id = User_Input::get_unsigned(args);
	unsigned new_haul_id = User_Input::get_unsigned(args);
    Movie* movie = cinema.find_movie_by_id(movie_id);
    if (movie == nullptr) 
		throw std::runtime_error("Movie not found.");
	cinema.updateMovieHaul(movie, new_haul_id);
}
Command* Update_Movie_Haul::clone()
{
    return new Update_Movie_Haul()
}