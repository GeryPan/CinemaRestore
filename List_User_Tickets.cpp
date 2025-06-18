#include "List_User_Tickets.h"
#include "Help_Program.h"
#include "User_Input.h"
#include "Id_Counter_Manager.h"
#include "MyString.h"
#include "Constants.h"
const MyString List_User_Tickets::Name() const
{
    return "list-user-tickets";
}
bool List_User_Tickets::need_login() const
{
    return true;
}
bool List_User_Tickets::need_admin() const
{
    return true;
}
void List_User_Tickets::execute(std::stringstream& args, User*& user, Cinema& cinema,
    Vector<User*>& users, Id_Counter_Manager& id_manager)
{
    MyString username = User_Input::get_word(args, Constants::MAX_USERNAME_LENGTH);
    User* target = nullptr;
    for (unsigned i = 0; i < users.Size(); i++)
    {
        if (Help_Program::compare_strings(users[i]->Username(), username) == 0)
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
        Movie* movie = cinema.find_movie_by_id(tickets[i]->Movie_Id());
        tickets[i]->print(movie);
    }
}
Command* List_User_Tickets::clone() const
{
    return new List_User_Tickets();
}