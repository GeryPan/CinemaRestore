#include "Serialize_User.h"
#include "Help_Program.h"
#include "Serialize.h"
#include <cstring>

void Serialize_User::free()
{
    delete[] username;
    delete[] password;
    for (unsigned i = 0; i < watched_movies_id.Size(); i++)
        delete watched_movies_id[i];
    watched_movies_id.clear();
}

void Serialize_User::copyFrom(const Serialize_User& other)
{
    id = other.id;
    username = Help_Program::copy_str(other.username);
    password = Help_Program::copy_str(other.password);
    balance = other.balance;
    admin = other.admin;
    tickets_soon = other.tickets_soon;
    rated_movies = other.rated_movies;
    for (unsigned i = 0; i < other.watched_movies_id.Size(); i++)
        watched_movies_id.push(new unsigned(*other.watched_movies_id[i]));
}

Serialize_User::Serialize_User()
{
    username = nullptr;
    password = nullptr;
    balance = 0.0;
    admin = false;
}

Serialize_User::Serialize_User(const Serialize_User& other)
{
    copyFrom(other);
}
Serialize_User& Serialize_User::operator=(const Serialize_User& other)
{
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}
Serialize_User::~Serialize_User()
{
    free();
    }