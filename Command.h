#pragma once
#include <sstream>
#include "Cinema.h"
#include "User.h"
#include "Vector.hpp"
#include "Id_Counter_Manager.h"

class Command 
{
public:
    virtual const char* Name() const = 0;
    virtual bool need_login() const = 0;
    virtual bool need_admin() const = 0;
    virtual Command* clone() const = 0;
    virtual void execute(std::stringstream& args, User*& user, Cinema& cinema, 
        Vector<User*>& users, Id_Counter_Manager& id_manager) = 0;
    virtual ~Command() {}
};
