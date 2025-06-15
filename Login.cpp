#include "Login.h"
#include "Help_Program.h"
#include "Constants.h"
#include "User.h"
#include "User_Input.h"
#include <cstring>
#include <stdexcept>

const char* Name()
{
    return "login";
}
bool need_login()
{
    return false;
}
bool need_admin()
{
    return false;
}

void execute(std::stringstream& args, User*& user, Cinema& cinema,
    Vector<User*>& users, Id_Counter_Manager& id_manager)
{
    if (user != nullptr)
        throw std::runtime_error("You are already logged in.");
const char* username = User_Input::get_word(args, Constants::MAX_USERNAME_LENGTH);
const char* password = User_Input::get_word(args, Constants::MAX_PASSWORD_LENGTH);
for (unsigned i = 0; i < users.Size(); i++)
{
    if (strcmp(users[i]->Username(), username) == 0 &&
        users[i]->check_password(password)) {
        user = users[i];
        break;
    }
}
if (user == nullptr)
    throw std::runtime_error("Login failed: wrong username or password.");
char* today = Help_Program::current_time();
Vector<Ticket*>& tickets = user->Tickets_soon();
for (unsigned i = 0; i < tickets.Size(); i++) 
{
    if (tickets[i]->is_expired(today)) {
        user->add_watched_movie(tickets[i]->Movie());
        user->remove_ticket(tickets[i]);
        i--;
    }
}

delete[] today;
}