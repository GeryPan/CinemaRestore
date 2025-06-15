#include "Command_Handler.h"
#include "Register.h"
#include "Login.h"
#include "Logout.h"
#include "Buy_Ticket.h"
#include "List_History.h"
#include "List_Movies.h"
#include "List_Tickets.h"
#include "List_User_History.h"
#include "List_User_Tickets.h"
#include "List_Users.h"
#include "Update_Movie_Title.h"
#include "Update_Movie_Haul.h"
#include "Rate_Command.h"
#include "Exit_Command.h"
#include "Add_Movie.h"
#include "Open_Haul.h"
#include "Remove_User.h"
#include "Remove_Movie.h"
#include "Close_Haul.h"
#include "File.h"
#include <iostream>
#include <cstring>
#include <sstream>

void Command_Handler::copyFrom(const Command_Handler& other)
{
    user = other.user;
    cinema = other.cinema;
    users = other.users;
    commands = other.commands;
}

Command_Handler::Command_Handler()
{
    user = nullptr;
    register_command(new Register_Command());
    register_command(new Login());
    register_command(new Buy_Ticket());
    register_command(new List_History());
    register_command(new List_Movies());
    register_command(new List_Tickets());
    register_command(new Rated());
    register_command(new Logout());
    register_command(new Exit_Command());

    register_command(new Add_Movie());
    register_command(new Open_Haul());
    register_command(new Remove_Movie());
    register_command(new Close_Haul());
    register_command(new Update_Movie_Title());
    register_command(new Update_Movie_Haul());
    register_command(new List_User_History());
    register_command(new List_User_Tickets());
    register_command(new List_Users());
    register_command(new Remove_User());

    File::read_in_file(cinema, users, id_manager, "cinema_data.bin");
}
Command_Handler::Command_Handler(const Command_Handler& other)
{
    copyFrom(other);
}

    Command_Handler& Command_Handler::operator=(const Command_Handler& other)
    {
        if (this != &other) {
            free();
            copyFrom(other);
        }
        return *this;
    }

    void Command_Handler::handle(const std::string& line)
    {
        std::stringstream str(line);
        std::string cmd;
        str >> cmd;
        Command* matched = nullptr;

        for (unsigned i = 0; i < commands.Size(); i++)
        {
            if (strcmp(commands[i]->Name(), cmd.c_str()) == 0) 
            {
                matched = commands[i];
                break;
            }
        }
        if (!matched) 
            throw std::runtime_error("Don't have this command.");
        if (matched->need_login() && user == nullptr) 
            throw std::runtime_error("You must be logged in.");
        if (matched->need_admin() && (!user || !user->is_admin())) 
            throw std::runtime_error("You must be an administrator.");
       matched->execute(str, user, cinema, users, id_manager);
    }
    void Command_Handler::register_command(Command* command)
    {
        commands.push(command);
    }

    Command_Handler::~Command_Handler()
    {
        free();
    }