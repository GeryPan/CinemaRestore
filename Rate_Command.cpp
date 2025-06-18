#include "Rate_Command.h"
#include "Help_Program.h"
#include "User_Input.h"
#include "Id_Counter_Manager.h"
#include "MyString.h"
#include "Constants.h"
#include <cstring>
#include <stdexcept>

const MyString Rate_Command::Name() const
{
    return "rate-movie";
}
bool Rate_Command::need_login() const
{
    return true;
}
bool Rate_Command::need_admin() const
{
    return false;
}

void Rate_Command::execute(std::stringstream& args, User*& user, Cinema& cinema,
    Vector<User*>& users, Id_Counter_Manager& id_manager)
{
    unsigned rating = User_Input::get_unsigned(args, Constants::MIN_RATING, Constants::MAX_RATING);
    unsigned movie_id = User_Input::get_unsigned(args, 1, id_manager.peek_current_id("movie"));

    Vector<Movie*>& history = user->Watched_movies();
    Movie* target = nullptr;

    for (unsigned i = 0; i < history.Size(); i++)
    {
        if (history[i]->Id() == movie_id) {
            target = history[i];
            break;
        }
    }

    if (!target)
        throw std::runtime_error("You have not watched this movie.");

    if (user->has_rated(target))
        throw std::runtime_error("You have already rated this movie.");

    user->rate_movie(target, rating);
    std::cout << "Successfully rated \"" << target->Title().c_str() << "\" with " << rating << " stars.\n";
}
Command* Rate_Command::clone() const
{
    return new Rate_Command();
}