#include "Rate_Command.h"
#include "Help_Program.h"
#include "User_Input.h"
#include <cstring>
#include <stdexcept>

const char* Name()
{
    return "rate-movie";
}
bool need_login()
{
    return true;
}
bool need_admin()
{
    return false;
}

void execute(std::stringstream& args, User*& user, Cinema& cinema,
    Vector<User*>& users, Id_Counter_Manager& id_manager)
{
    unsigned movie_id = User_Input::get_unsigned(args);
    Movie* movie = cinema.find_movie_by_id(movie_id);
    if (movie == nullptr) 
        throw std::runtime_error("Movie doesn't found.");
    const char* today = Help_Program::current_time();
    bool has_passed = Help_Program::is_before(movie->Date(), today);
    delete[] today;
    for (unsigned i = 0; i < users.Size(); i++) 
    {
        users[i]->remove_movie(movie_id, has_passed);
    }
    cinema.remove_movie_by_id(movie_id);
}