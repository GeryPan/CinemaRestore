#include "Login.h"
#include "Help_Program.h"
#include "Constants.h"
#include "User.h"
#include "Id_Counter_Manager.h"
#include "MyString.h"
#include "User_Input.h"
#include <cstring>
#include <stdexcept>

const MyString Login::Name() const
{
    return "login";
}
bool Login::need_login() const
{
    return false;
}
bool Login::need_admin() const
{
    return false;
}

void Login::execute(std::stringstream& args, User*& user, Cinema& cinema,
    Vector<User*>& users, Id_Counter_Manager& id_manager)
{
    if (user != nullptr)
        throw std::runtime_error("You are already logged in.");

    MyString username = User_Input::get_word(args, Constants::MAX_USERNAME_LENGTH);
    MyString password = User_Input::get_word(args, Constants::MAX_PASSWORD_LENGTH);

    for (unsigned i = 0; i < users.Size(); i++)
    {
        if (Help_Program::compare_strings(users[i]->Username(), username) == 0 &&
            users[i]->check_password(password)) {
            user = users[i];
            break;
        }
    }

    if (user == nullptr)
        throw std::runtime_error("Login failed: wrong username or password.");

    MyString today = Help_Program::getCurrentDateStr();
    Vector<Ticket*>& tickets = user->Tickets_soon();

    for (unsigned i = 0; i < tickets.Size(); ++i)
    {
        Movie* movie = cinema.find_movie_by_id(tickets[i]->Movie_Id());

        if (tickets[i]->is_expired(movie, today)) {
            user->add_watched_movie(movie);
            tickets.remove_at(i);
            i--; 
        }
    }
}
Command* Login::clone() const
{
    return new Login();
}