#include "Remove_Movie.h"
#include "User_Input.h"
#include "Id_Counter_Manager.h"
#include "MyString.h"
#include <iostream>
#include <stdexcept>
const MyString Remove_Movie::Name() const
{
    return "remove-movie";
}
bool Remove_Movie::need_admin() const
{
    return true;
}
bool Remove_Movie::need_login() const
{
    return true;
}

void Remove_Movie::execute(std::stringstream& args, User*& user, Cinema& cinema,
    Vector<User*>& users, Id_Counter_Manager& id_manager)
{
    unsigned movie_id = User_Input::get_unsigned(args);
    unsigned new_haul_id = User_Input::get_unsigned(args);
    Movie* movie = cinema.find_movie_by_id(movie_id);
    if (movie == nullptr)
        throw std::runtime_error("Movie not found.");
    cinema.update_movie_haul(movie, new_haul_id);
}
Command* Remove_Movie::clone() const
{
    return new Remove_Movie();
}