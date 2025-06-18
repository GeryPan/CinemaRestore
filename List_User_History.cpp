#include "List_User_History.h"
#include "Help_Program.h"
#include "User_Input.h"
#include "Id_Counter_Manager.h"
#include "MyString.h"
#include "Constants.h"
#include <iostream>
#include <cstring>

const MyString List_User_History::Name() const
{
    return "list-user-history";
}
bool List_User_History::need_login() const
{
    return true;
}
bool List_User_History::need_admin() const
{
    return true;
}
void List_User_History::execute(std::stringstream& args, User*& user, Cinema& cinema,
    Vector<User*>& users, Id_Counter_Manager& id_manager)
{
    MyString username = User_Input::get_word(args, Constants::MAX_USERNAME_LENGTH);
    User* target = nullptr;
    for (unsigned i = 0; i < users.Size(); i++)
    {
        if (Help_Program::compare_strings(users[i]->Username(), username) == 0) {
            target = users[i];
            break;
        }
    }
    if (target == nullptr) {
        throw std::runtime_error("User not found.");
    }
    Vector<Movie*> history = target->Watched_movies();
    if (history.Size() == 0) {
        throw std::runtime_error("No watched movies.");
    }
    std::cout << "Watched movies for " << username << ":\n";
    for (unsigned i = 0; i < history.Size(); i++)
    {
        std::cout << "- ";
        history[i]->print();
    }
}
Command* List_User_History::clone() const
{
    return new List_User_History();
}