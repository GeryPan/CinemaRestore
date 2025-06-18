#include "Close_Haul.h"
#include "Help_Program.h"
#include "User_Input.h"
#include "Vector.hpp"
#include "Id_Counter_Manager.h"
#include "MyString.h"
#include <iostream>
#include <stdexcept>

const MyString Close_Haul::Name() const
{
	return "close-haul";
}
bool Close_Haul::need_login() const
{
	return true;
}
bool Close_Haul::need_admin() const
{
	return true;
}
void Close_Haul::execute(std::stringstream& args, User*& user, Cinema& cinema,
	Vector<User*>& users, Id_Counter_Manager& id_manager)
{
	unsigned haul_id = User_Input::get_unsigned(args);
	cinema.close_haul(haul_id, users);
}
Command* Close_Haul::clone() const
{
	return new Close_Haul();
}