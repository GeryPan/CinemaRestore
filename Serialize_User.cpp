#include "Serialize_User.h"
#include "Help_Program.h"
#include "Serialize.h"
#include <cstring>

void Serialize_User::free()
{
}

void Serialize_User::copyFrom(const Serialize_User& other)
{
    id = other.id;
    username = other.username;
    password = other.password;
    balance = other.balance;
    admin = other.admin;
    tickets_soon = other.tickets_soon;
    rated_movies = other.rated_movies;
    watched_movies_id = other.watched_movies_id;
}

Serialize_User::Serialize_User()
{
    balance = 0.0;
    admin = false;
}

Serialize_User::Serialize_User(const Serialize_User& other)
{
    copyFrom(other);
}
Serialize_User& Serialize_User::operator=(const Serialize_User& other)
{
    if (this != &other) 
    {
        free();
        copyFrom(other);
    }
    return *this;
}
Serialize_User::~Serialize_User()
{
    free();
}
Serialize_User* Serialize_User::clone() const 
{
    return new Serialize_User(*this);
}