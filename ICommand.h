#pragma once
#include <sstream>
#include "Cinema.h"
#include "User.h"
#include "Vector.hpp"
#include "Id_Counter_Manager.h"

class ICommand {
public:
    virtual const char* Name() const = 0;
    virtual bool insist_login() const = 0;
    virtual bool insist_admin() const = 0;
    virtual void execute(
        std::stringstream& args, User*& currentUser, Cinema& cinema,
        Vector<User*>& users, Id_Counter_Manager& idManager) = 0;
    virtual ~ICommand() {}
};