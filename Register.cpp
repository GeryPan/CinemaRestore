#include "Register.h"
#include "Constants.h"
#include "User.h"
#include "User_Input.h"
#include <iostream>
#include <cstring>

const char* Name()
{
    return "add-movie";
}
bool need_admin()
{
    return false;
}
bool need_login()
{
    return false;
}

void execute(std::stringstream& args, User*& user, Cinema& cinema,
    Vector<User*>& users, Id_Counter_Manager& id_manager)
{
    if (user != nullptr)
        throw std::runtime_error("You are already logged in.");

    char* username = User_Input::get_word(args, Constants::MAX_USERNAME_LENGTH);
    char* password = User_Input::get_word(args, Constants::MAX_PASSWORD_LENGTH);

    for (unsigned i = 0; i < users.Size(); i++)
    {
        if (strcmp(users[i]->Username(), username) == 0)
            throw std::runtime_error("Username already exists.");
    }

    unsigned next_id = id_manager.generate_next_id("user");
    users.push(new User(next_id, username, password, Constants::USER_REGISTER_START_BALANCE, false));
}
Command* clone()
{
    return new Register();
}
