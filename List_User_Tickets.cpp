#include "List_User_Tickets.h"

const char* Name()
{
    return "list-user-tickets";
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
    const char* username = User_Input::get_word(args, Constants::MAX_USERNAME_LENGTH);
     User* target = nullptr;
    for (unsigned i = 0; i < users.Size(); i++)
    {
        if (strcmp(users[i]->Username(), username) == 0) 
        {
            target = users[i];
            break;
        }
    }
    if (target == nullptr) 
        throw std::runtime_error("User not found.");
    Vector<Ticket*> tickets = target->Tickets_soon();
    if (tickets.Size() == 0) 
        throw std::runtime_error("No upcoming tickets.");
    std::cout << "Upcoming tickets for " << username << ":\n";
    for (unsigned i = 0; i < tickets.Size(); i++) 
    {
        std::cout << "- ";
        tickets[i]->print();
    }
}