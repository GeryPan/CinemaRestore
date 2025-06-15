#include "List_Tickets.h"
#include "User.h"
#include <stdexcept>
#include <iostream>

const char* Name()
{
	return "list-tickets";
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
	Vector<Ticket*>& tickets = user->Tickets_soon();
if (tickets.Size() == 0)
		throw std::runtime_error("You have no upcoming tickets.");
for (unsigned i = 0; i < tickets.Size(); i++)
		tickets[i]->print();
}