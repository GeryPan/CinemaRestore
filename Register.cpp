#include "Register.h"
#include "Help_Program.h"
#include "Constants.h"
#include "User.h"
#include "User_Input.h"
#include <iostream>
#include "Id_Counter_Manager.h"
#include "MyString.h"
#include <cstring>

const MyString Register::Name() const
{
    return "add-movie";
}
bool Register::need_admin() const
{
    return false;
}
bool Register::need_login() const
{
    return false;
}

void Register::execute(std::stringstream& args, User*& user, Cinema& cinema,
    Vector<User*>& users, Id_Counter_Manager& id_manager)
{
    if (user != nullptr)
        throw std::runtime_error("You are already logged in.");

    MyString username = User_Input::get_word(args, Constants::MAX_USERNAME_LENGTH);
    MyString password = User_Input::get_word(args, Constants::MAX_PASSWORD_LENGTH);

    for (unsigned i = 0; i < users.Size(); i++)
    {
        if (Help_Program::compare_strings(users[i]->Username(), username) == 0)
            throw std::runtime_error("Username already exists.");
    }

    unsigned next_id = id_manager.generate_next_id("user");
    users.push(new User(next_id, username, password, Constants::USER_REGISTER_START_BALANCE, false));
}
Command* Register::clone() const
{
    return new Register();
}