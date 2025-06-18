#include "Update_Movie_Haul.h"
#include "Help_Program.h"
#include "User_Input.h"
#include <iostream>
#include "Id_Counter_Manager.h"
#include "MyString.h"
#include <cstring>

const MyString Update_Movie_Haul::Name() const
{
    return "update-movie-haul";
}
bool Update_Movie_Haul::need_admin() const
{
    return true;
}
bool Update_Movie_Haul::need_login() const
{
    return false;
}

void Update_Movie_Haul::execute(std::stringstream& args, User*& user, Cinema& cinema,
    Vector<User*>& users, Id_Counter_Manager& id_manager)
{
    unsigned movie_id = User_Input::get_unsigned(args);
    unsigned new_haul_id = User_Input::get_unsigned(args);
    Movie* movie = cinema.find_movie_by_id(movie_id);
    if (movie == nullptr)
        throw std::runtime_error("Movie not found.");
    cinema.update_movie_haul(movie, new_haul_id);
}
Command* Update_Movie_Haul::clone() const
{
    return new Update_Movie_Haul();
}