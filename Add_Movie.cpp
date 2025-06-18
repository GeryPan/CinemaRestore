
#include "Add_Movie.h"
#include "User_Input.h"
#include "Movie_Factory.h"
#include "Constants.h"
#include "Id_Counter_Manager.h"
#include "MyString.h"
#include <iostream>
#include <stdexcept>
#include <cstring>

const MyString Add_Movie::Name() const
{
    return "add-movie";
}
bool Add_Movie::need_admin() const
{
    return true;
}
bool Add_Movie::need_login() const
{
    return true;
}
Command* Add_Movie::clone() const
{ 
    return new Add_Movie();
}
void Add_Movie::execute(std::stringstream& args, User*& user, Cinema& cinema,
    Vector<User*>& users, Id_Counter_Manager& id_manager)
{
    MyString genre = User_Input::get_word(args, Constants::MAX_GENRE_LENGTH);
    Movie* movie = Movie_Factory::create_movie(id_manager, genre);
    cinema.add_movie(movie);
}