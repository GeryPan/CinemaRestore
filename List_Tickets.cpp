#include "List_Tickets.h"
#include "User.h"
#include "Id_Counter_Manager.h"
#include "MyString.h"
#include <stdexcept>
#include <iostream>

const MyString List_Ticket::Name() const
{
	return "list-tickets";
}
bool List_Ticket::need_login() const
{
	return true;
}
bool List_Ticket::need_admin() const
{
	return false;
}
void List_Ticket::execute(std::stringstream& args, User*& user, Cinema& cinema,
	Vector<User*>& users, Id_Counter_Manager& id_manager)
{
	Vector<Ticket*>& tickets = user->Tickets_soon();
	if (tickets.Size() == 0)
		throw std::runtime_error("You have no upcoming tickets.");
	for (unsigned i = 0; i < tickets.Size(); i++)
	{
		Movie* movie = cinema.find_movie_by_id(tickets[i]->Movie_Id());
		tickets[i]->print(movie);
	}
}
Command* List_Ticket::clone() const
{
	return new List_Ticket();
}