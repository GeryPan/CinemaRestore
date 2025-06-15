#pragma once
#include "Cinema.h"
#include "User.h"
#include "Command.h" 
#include "Vector.hpp"
#include "Id_Counter_Manager.h"

class Command_Handler 
{
    Cinema cinema;
    Id_Counter_Manager id_manager;
    Vector<User*> users;
    User* user;
    Vector<Command*> commands;

    void free();
    void copyFrom(const Command_Handler& other);
public:
    Command_Handler();
    Command_Handler(const Command_Handler& other);
    Command_Handler& operator=(const Command_Handler& other);
    void handle(const std::string& line);
    void register_command(Command* command);
    ~Command_Handler();
};