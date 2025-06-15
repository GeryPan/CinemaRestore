#include "Close_Haul.h"
#include "Help_Program.h"
#include "User_Input.h"
#include <iostream>
#include <stdexcept>

const char* Name()
{ 
	return "close-haul"; 
}
bool need_login()
{ 
	return true; 
}
bool need_admin()
{ 
	return true;
}
void execute(std::stringstream& args, User*& user, Cinema& cinema,
	Vector<User*>& users, Id_Counter_Manager& id_manager)
{
	unsigned haul_id = User_Input::get_unsigned(args);
	cinema.close_haul(haul_id, users);
}