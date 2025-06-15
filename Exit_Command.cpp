#include "Exit_Command.h"
#include "File.h"
#include <iostream>
#include <cstdlib> 

const char* Name()
{ 
	return "exit";
}
bool need_login()
{ 
	return false;
}
bool need_admin()
{ 
	return false; 
}

void  execute(std::stringstream& args, User*& user, Cinema& cinema,
	Vector<User*>& users, Id_Counter_Manager& id_manager)
{
	File::write_in_file(cinema, users, id_manager, "cinema_data.bin");
	std::cout << "Exiting the program...\n";
	std::terminate();
}