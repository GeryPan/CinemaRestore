#pragma once
#include "Vector.hpp"
#include "User.h"
#include "Movie.h"
#include "Haul.h"
#include "MyString.h"

class Cinema
{
    Vector<Movie*> movies;
    Vector<Haul*> hauls;
    void free();
    void copyFrom(const Cinema& other);
public:
    Cinema();
    Cinema(const Cinema& other);
    Cinema(Vector<Movie*>& new_movies, Vector<Haul*>& new_hauls);
    Cinema(Vector<Movie*>&& m, Vector<Haul*>&& h);
    Cinema& operator=(const Cinema& other);
    Cinema& operator=(Cinema&& other);
    const Vector<Movie*>& Movies() const;
    const Vector<Haul*>& Hauls() const;
    void add_haul(Haul* new_haul);
    bool is_haul_available(unsigned haul_id, const MyString& date, const MyString& start, const MyString& finish, const Movie* ignore = nullptr);
    Haul* find_haul_by_id(unsigned haul_id) const;
    void remove_haul_by_id(unsigned haul_id);
    void add_movie(Movie* new_movie);
    Movie* find_movie_by_id(unsigned movie_id) const;
    void remove_movie_by_id(unsigned movie_id);
    void update_movie_haul(Movie* new_movie, unsigned new_haul_id);
    void close_haul(unsigned haul_id, Vector<User*>& users);
    void print_movies() const;
    ~Cinema();
};