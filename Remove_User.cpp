#include "Remove_User.h"
#include "User_Input.h"
#include "Constants.h"
#include <iostream>
#include <cstring>
const char* Name()
{
    return "remove-user";
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
    unsigned user_id = User_Input::get_unsigned(args, 0, id_manager.peek_current_id("user"));

    for (unsigned i = 0; i < users.Size(); i++) 
    {
        if (users[i]->Id() == user_id) {
            if (users[i]->is_admin()) {
                throw std::runtime_error("Cannot remove the admin user.");
            }

            users.remove_at(i);

            std::cout << "User \n" << users[i]->Username() << "\n removed successfully.\n";
            return;
        }
    }

    throw std::runtime_error("User not found.");
}
Command* clone()
{
    return new Remove_User();
}
