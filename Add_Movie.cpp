#include "Add_Movie.h"
#include "User_Input.h"
#include "Movie_Factory.h"
#include "Constants.h"
#include <iostream>
#include <stdexcept>
#include <cstring>

const char* Name()
{ 
    return "add-movie"; 
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
    const char* genre = User_Input::get_word(args, Constants::MAX_GENRE_LENGTH);
Movie* movie = Movie_Factory::create_movie(id_manager, genre);
    cinema.add_movie(movie);
}