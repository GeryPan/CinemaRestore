#include "Logout.h"
#include "Help_Program.h"
#include "Constants.h"
#include "Id_Counter_Manager.h"
#include "MyString.h"
#include "User.h"
#include "User_Input.h"
#include <cstring>
#include <stdexcept>

const MyString Logout::Name() const
{
    return "logout";
}
bool Logout::need_login() const
{
    return true;
}
bool Logout::need_admin() const
{
    return false;
}

void Logout::execute(std::stringstream& args, User*& user, Cinema& cinema,
    Vector<User*>& users, Id_Counter_Manager& id_manager)
{
    user = nullptr;
}
Command* Logout::clone() const
{
    return new Logout();
}