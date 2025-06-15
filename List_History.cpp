#include "List_History.h"
#include "User.h"
#include <iostream>
#include <stdexcept>

const char* Name()
{
	return "list-history";
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
	Vector<Movie*>& watched = user->Watched_movies();
	if (watched.Size() == 0)
		throw std::runtime_error("No watched movies found.");
	for (unsigned i = 0; i < watched.Size(); i++)
		watched[i]->print();
}