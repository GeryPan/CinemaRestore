#include "Update_Movie_Title.h"
#include "User_Input.h"
#include "Constants.h"
#include <iostream>
#include <stdexcept>

const char* Name()
{
    return "update-movie-title";
}
bool need_admin()
{
    return true;
}
bool need_login()
{
    return true;
}

void execute(std::stringstream& args, User*& user, Cinema& cinema,
    Vector<User*>& users, Id_Counter_Manager& id_manager)
{
	unsigned movie_id = User_Input::get_unsigned(args);
	const char* new_title = User_Input::get_remaining(args, Constants::MAX_MOVIE_TITLE_LENGTH);
	Movie* movie = cinema.find_movie_by_id(movie_id);
	if (movie == nullptr) 
		throw std::runtime_error("Movie not found.");
	movie->set_title(new_title);
}
Command* clone()
{
    return new Update_Movie_Haul()
}
