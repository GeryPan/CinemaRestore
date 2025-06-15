#include "User.h"
#include "Constants.h"
#include "Help_Program.h"
#include "Serialize_Watched_Movies.h"
#include <iostream>
#include <cstring>
#include <string>

void User::free()
{
    delete[] username;
    delete[] password;
    for (unsigned i = 0; i < tickets_soon.Size(); i++)
        delete tickets_soon[i];
    for (unsigned i = 0; i < rated_movies.Size(); i++)
        delete rated_movies[i];
}

void User::copyFrom(const User& other)
{
    id = other.id;
    username = Help_Program::copy_str(other.username);
    password = Help_Program::copy_str(other.password);
    balance = other.balance;
    admin = other.admin;
    tickets_soon = other.tickets_soon;
    watched_movies = other.watched_movies;
    rated_movies = other.rated_movies;
}

User::User()
{
    id = 0;
    username = nullptr;
    password = nullptr;
    balance = 0.0;
    admin = false;
    watched_movies = Vector<Movie*>();
    tickets_soon = Vector<Ticket*>();
    rated_movies = Vector<Rated*>();
 }

    User::User(const User& other)
    {
        copyFrom(other);
    }

    User::User(unsigned new_id, const char* new_username, const char* new_password, double new_balance, bool new_admin)
    {
        id = new_id;
        username = Help_Program::copy_str(new_username);
        password = Help_Program::copy_str(new_password);
        balance = new_balance;
        admin = new_admin;
        watched_movies.set_ownership(false);
    }
    User& User::operator=(const User& other)
    {
        if (this != &other) {
            free();
            copyFrom(other);
        }
        return *this;
    }

    unsigned User::Id() const
    {
        return id;
    }
    const char* User::Username() const
    {
        return username;
    }

    bool User::check_password(const char* try_password) const
    {
        return strcmp(try_password, password) == 0;
    }

    double User::Balance() const
    {
        return balance;
    }

    bool User::is_admin() const
    {
        return admin;
    }

    unsigned User::Rating(Movie* movie) const
    {
        for (unsigned i = 0; i < rated_movies.Size(); i++)
        {
            if (rated_movies[i]->Movie() == movie)
                return rated_movies[i]->Rate();
        }
        return -1;
    }

    void User::add_balance(double money)
    {
        balance += money;
    }

    void User::add_watched_movie(Movie* new_movie)
    {
        watched_movies.push(new_movie);
    }

    void User::add_ticket(Ticket* new_ticket)
    {
        tickets_soon.push(new_ticket);
    }

    Vector<Movie*>& User::Watched_movies()
    {
        return watched_movies;
    }

    Vector<Ticket*>& User::Tickets_soon()
    {
        return tickets_soon;
    }

    bool User::has_watched(Movie* movie) const
    {
        for (unsigned i = 0; i < watched_movies.Size(); i++)
            if (watched_movies[i] == movie)
                return true;
        return false;
    }

    bool User::has_rated(Movie* movie) const
    {
        for (unsigned i = 0; i < rated_movies.Size(); i++)
        {
            if (rated_movies[i]->Movie() == movie)
                return true;
        }
        return false;
    }

    void User::rate_movie(Movie* movie, unsigned rating)
    {
        if (!has_watched(movie)) 
            throw std::invalid_argument("You can't rate a movie you haven't watched.");
        if (has_rated(movie)) 
            throw std::runtime_error("You have already rated this movie.");
        if (rating < Constants::MIN_RATING || rating > Constants::MAX_RATING) 
            throw std::runtime_error("Rating must be between " + std::to_string(Constants::MIN_RATING)
                + " and " + std::to_string(Constants::MAX_RATING) + ".");
    
        rated_movies.push(new Rated(movie, rating));
        std::cout << "Successfully rated: \n" << movie->Title() << "\n";
        for (unsigned i = 0; i < rating; i++)
            std::cout << '*';
    }

    void User::remove_movie(unsigned movie_id, bool has_passed)
    {

        // passed
        if (has_passed == true) 
        {
            for (unsigned i = 0; i < watched_movies.Size(); i++) 
            {
                if (watched_movies[i]->Id() == movie_id) 
                {
                    watched_movies.remove_at(i);
                    break;
                }
            }

            for (unsigned i = 0; i < rated_movies.Size(); i++) 
            {
                if (rated_movies[i]->Movie()->Id() == movie_id) 
                {
                    rated_movies.remove_at(i);
                    break;
                }
            }
            return;
        }

        // in future
        for (unsigned i = 0; i < tickets_soon.Size(); i++)
        {
            Ticket* t = tickets_soon[i];
            if (t->Movie()->Id() == movie_id) 
            {
                balance += t->Movie()->calculate_ticket_price();
                remove_ticket(t);
                i--;
            }
        }
    }

    void User::remove_ticket(Ticket* ticket)
    {
        for (unsigned i = 0; i < tickets_soon.Size(); i++) 
        {
            if (tickets_soon[i] == ticket) 
            {
                delete ticket;
                for (unsigned j = i; j < tickets_soon.Size() - 1; j++)
                    tickets_soon[j] = tickets_soon[j + 1];
                tickets_soon.pop();
                return;
            }
        }
    }

    Serialize_User* User::serialize_user()
    {
        Serialize_User* su = new Serialize_User();
        su->id = id;
        su->username = Help_Program::copy_str(username);
        su->password = Help_Program::copy_str(password);
        su->balance = balance;
        su->admin = admin;

        for (unsigned i = 0; i < tickets_soon.Size(); i++)
        {
            Ticket* t = tickets_soon[i];
            su->tickets_soon.push(new Serialize_Ticket( t->Movie()->Id(), t->Row(), t->Col() ));
        }
        for (unsigned i = 0; i < watched_movies.Size(); i++) 
        {
           // unsigned* id = new unsigned(watched_movies[i]->Id());
           // su->watched_movies_id.push(id);

           Serialize_Watched_Movies* swm = new Serialize_Watched_Movies(watched_movies[i]->Id());
            su->watched_movies_id.push(swm);
        }
        for (unsigned i = 0; i < watched_movies.Size(); i++) 
        {
            Movie* m = watched_movies[i];
            if (has_rated(m)) 
                su->rated_movies.push(new Serialize_Rating(m->Id(), Rating(m)));
         }

        return su;
    }
    User* User::clone() const
    {
        return new User(*this);
    }

    User::~User()
    {
        free();
    }
