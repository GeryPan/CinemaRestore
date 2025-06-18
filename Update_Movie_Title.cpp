#include "Update_Movie_Title.h"
#include "User_Input.h"
#include "Id_Counter_Manager.h"
#include "MyString.h"
#include "Constants.h"
#include <iostream>
#include <stdexcept>

const MyString Update_Movie_Title::Name() const
{
	return "update-movie-title";
}
bool Update_Movie_Title::need_admin() const
{
	return true;
}
bool Update_Movie_Title::need_login() const
{
	return true;
}

void Update_Movie_Title::execute(std::stringstream& args, User*& user, Cinema& cinema,
	Vector<User*>& users, Id_Counter_Manager& id_manager)
{
	unsigned movie_id = User_Input::get_unsigned(args);
	MyString new_title = User_Input::get_remaining(args, Constants::MAX_MOVIE_NAME_LENGTH);
	Movie* movie = cinema.find_movie_by_id(movie_id);
	if (movie == nullptr)
		throw std::runtime_error("Movie not found.");
	movie->set_title(new_title);
}
Command* Update_Movie_Title::clone() const
{
	return new Update_Movie_Title();
}
