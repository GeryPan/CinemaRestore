#include "Open_Haul.h"
#include "Constants.h"
#include "Help_Program.h"
#include "User_Input.h"
#include <iostream>
#include <stdexcept>

const MyString Open_Haul::Name() const
{
    return "open-haul";
}
bool Open_Haul::need_login() const
{
    return true;
}
bool Open_Haul::need_admin() const
{
    return true;
}

void Open_Haul::execute(std::stringstream& args, User*& user, Cinema& cinema,
    Vector<User*>& users, Id_Counter_Manager& id_manager)
{
    unsigned rows = User_Input::get_unsigned(args, 1, Constants::MAX_HAUL_ROW_COUNT);
    unsigned cols = User_Input::get_unsigned(args, 1, Constants::MAX_HAUL_COL_COUNT);
    unsigned new_haul_id = id_manager.generate_next_id("haul");
    cinema.add_haul(new Haul(new_haul_id, rows, cols));
}
Command* Open_Haul::clone() const
{
    return new Open_Haul();
}