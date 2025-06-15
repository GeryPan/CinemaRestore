#include "List_User_History.h"
#include "User_Input.h"
#include "Constants.h"
#include <iostream>
#include <cstring>

const char* Name()
{
	return "list-user-history";
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
        if (strcmp(users[i]->Username(), username) == 0) {
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