#include "List_Movies.h"
const char* Name()
{
	return "list-movies";
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
	cinema.print_movies();
}