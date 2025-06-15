#include "Logout.h"
#include "Help_Program.h"
#include "Constants.h"
#include "User.h"
#include "User_Input.h"
#include <cstring>
#include <stdexcept>

const char* Name()
{
    return "logout";
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
    user = nullptr;
}