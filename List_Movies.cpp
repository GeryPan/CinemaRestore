#include "List_Movies.h"
#include "Id_Counter_Manager.h"
#include "MyString.h"
const MyString List_Movies::Name() const
{
	return "list-movies";
}
bool List_Movies::need_login() const
{
	return true;
}
bool List_Movies::need_admin() const
{
	return false;
}
void List_Movies::execute(std::stringstream& args, User*& user, Cinema& cinema,
	Vector<User*>& users, Id_Counter_Manager& id_manager)
{
	cinema.print_movies();
}
Command* List_Movies::clone() const
{
	return new List_Movies();
}