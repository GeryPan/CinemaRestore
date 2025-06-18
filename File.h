#pragma once
#include "Vector.hpp"
#include "User.h"
#include "Id_Counter_Manager.h"
#include "Cinema.h"

namespace File
{
    void write_in_file(const Cinema& cinema, const Vector<User*>& users, Id_Counter_Manager& id_manager, const MyString& file_name);
    Cinema read_in_file(Cinema& cinema, Vector<User*>& users, Id_Counter_Manager& id_manager, const MyString& file_name);
}