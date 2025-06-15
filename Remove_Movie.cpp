#include "Remove_Movie.h"
#include "User_Input.h"
#include <iostream>
#include <stdexcept>
const char* Name()
{
    return "remove-movie";
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
    unsigned new_haul_id = User_Input::get_unsigned(args);
    Movie* movie = cinema.find_movie_by_id(movie_id);
    if (movie == nullptr)
        throw std::runtime_error("Movie not found.");
    cinema.update_movie_haul(movie, new_haul_id);
}
Remove_Movie* clone()
{
    return new Remove_Movie();
}