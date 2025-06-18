#include "List_History.h"
#include "User.h"
#include "Id_Counter_Manager.h"
#include "MyString.h"
#include <iostream>
#include <stdexcept>

const MyString List_History::Name() const
{
	return "list-history";
}
bool List_History::need_login() const
{
	return true;
}
bool List_History::need_admin() const
{
	return false;
}
void List_History::execute(std::stringstream& args, User*& user, Cinema& cinema,
	Vector<User*>& users, Id_Counter_Manager& id_manager)
{
	Vector<Movie*>& watched = user->Watched_movies();
	if (watched.Size() == 0)
		throw std::runtime_error("No watched movies found.");
	for (unsigned i = 0; i < watched.Size(); i++)
		watched[i]->print();
}
Command* List_History::clone() const
{
	return new List_History();
}