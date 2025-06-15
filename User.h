#pragma once
#include "Vector.hpp"
#include "Serialize_User.h"
#include "Movie.h"
#include "Ticket.h"
#include "Rated.h"

class User 
{
    unsigned id;
    char* username;
    char* password;
    double balance;
    bool admin;
    Vector<Movie*> watched_movies; 
    Vector<Ticket*> tickets_soon; 
    Vector<Rated*> rated_movies; 

    void free();
    void copyFrom(const User& other);
public:
    User();
    User(const User& other);
    User(unsigned new_id, const char* new_username, const char* new_password, double new_balance, bool new_admin);
    User& operator=(const User& other);
    unsigned Id() const;
    const char* Username() const;
    bool check_password(const char* try_password) const;
    double Balance() const;
    bool is_admin() const;
    unsigned Rating(Movie* movie) const;
    void add_balance(double maney);
    void add_watched_movie(Movie* new_movie);
    void add_ticket(Ticket* new_ticket);
    Vector<Movie*>& Watched_movies();
    Vector<Ticket*>& Tickets_soon();
    bool has_watched(Movie* movie) const;
    bool has_rated(Movie* movie) const;
    void rate_movie(Movie* movie, unsigned rating);
    void remove_movie(unsigned movie_id, bool has_passed);
    void remove_ticket(Ticket* ticket);
    Serialize_User* serialize_user();
    User* clone() const;
    ~User();
};