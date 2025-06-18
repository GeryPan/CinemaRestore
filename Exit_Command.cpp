#include "Exit_Command.h"
#include "File.h"
#include <iostream>
#include "Id_Counter_Manager.h"
#include "MyString.h"
#include <cstdlib> 

const MyString Exit_Command::Name() const
{
	return "exit";
}
bool Exit_Command::need_login() const
{
	return false;
}
bool Exit_Command::need_admin() const
{
	return false;
}

void  Exit_Command::execute(std::stringstream& args, User*& user, Cinema& cinema,
	Vector<User*>& users, Id_Counter_Manager& id_manager)
{
	File::write_in_file(cinema, users, id_manager, "cinema_data.bin");
	std::cout << "Exiting the program...\n";
	std::terminate();
}
Command* Exit_Command::clone() const
{
	return new Exit_Command();
}