#include "Cinema.h"
#include "Constants.h"
#include "Help_Program.h"
#include "Movie_Factory.h"
#include "Vector.hpp"
#include <iostream>
#include <cstring>  

void Cinema::free()
{
}

void Cinema::copyFrom(const Cinema& other) {
	movies = other.movies;
	hauls = other.hauls;
}

Cinema::Cinema() {}
Cinema::Cinema(const Cinema& other)
{
	copyFrom(other);
}

Cinema::Cinema(Vector<Movie*>& new_movies, Vector<Haul*>& new_hauls)
{
	movies = new_movies;
	hauls = new_hauls;
}

Cinema::Cinema(Vector<Movie*>&& m, Vector<Haul*>&& h)
{
	movies = std::move(m);
	hauls = std::move(h);
}

Cinema& Cinema::operator=(const Cinema& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Cinema& Cinema::operator=(Cinema&& other) {
	if (this != &other) {
		movies = std::move(other.movies);
		hauls = std::move(other.hauls);
	}
	return *this;
}

const Vector<Movie*>& Cinema::Movies() const
{
	return movies;
}

const Vector<Haul*>& Cinema::Hauls() const
{
	return hauls;
}
void Cinema::add_haul(Haul* new_haul)
{
	if (find_haul_by_id(new_haul->Id()) != nullptr)
	{
		delete new_haul;
		throw std::runtime_error("This haul already exists.");
	}
	hauls.push(new_haul);
}

bool Cinema::is_haul_available(unsigned haul_id, const MyString& date, const MyString& start, const MyString& finish, const Movie* ignore)
{
	Haul* h = find_haul_by_id(haul_id);
	if (!h) return false;
	for (unsigned i = 0; i < movies.Size(); i++)
	{
		Movie* m = movies[i];
		if (m == ignore) continue;
		if (m->Haul_id() == haul_id && Help_Program::compare_strings(m->Date(), date) == 0) {
			if (Help_Program::coincident_time(m->Start(), m->Finish(), start, finish))
				return false;
		}
	}
	return true;
}

Haul* Cinema::find_haul_by_id(unsigned haul_id) const
{
	for (unsigned i = 0; i < hauls.Size(); i++)
	{
		if (hauls[i]->Id() == haul_id)
			return hauls[i];
	}

	return nullptr;
}
void Cinema::remove_haul_by_id(unsigned haul_id)
{
	for (unsigned i = 0; i < hauls.Size(); i++)
	{
		if (hauls[i]->Id() == haul_id) {
			hauls.remove_at(i);
			return;
		}
	}
	throw new std::invalid_argument("The haul doesn't found.");
}

void Cinema::add_movie(Movie* new_movie)
{
	Haul* haul = find_haul_by_id(new_movie->Haul_id());
	if (haul == nullptr) {
		delete new_movie;
		throw std::invalid_argument("Haul does not exist.");
	}
	for (unsigned i = 0; i < movies.Size(); i++)
	{
		if (movies[i]->Id() == new_movie->Id())
		{
			delete new_movie;
			throw std::runtime_error("Movie with the same ID already exists.");
		}
	}
	if (!is_haul_available(new_movie->Haul_id(), new_movie->Date(), new_movie->Start(), new_movie->Finish())) {
		delete new_movie;
		throw std::runtime_error("Conflict: another movie overlaps in the selected haul.");
	}
	movies.push(new_movie);
}
Movie* Cinema::find_movie_by_id(unsigned movie_id) const
{
	for (unsigned i = 0; i < movies.Size(); i++)
	{
		if (movies[i]->Id() == movie_id)
			return movies[i];
	}
	return nullptr;
}

void Cinema::remove_movie_by_id(unsigned movie_id)
{
	for (unsigned i = 0; i < movies.Size(); i++)
	{
		if (movies[i]->Id() == movie_id)
		{
			movies.remove_at(i);
			return;
		}
	}
	throw new std::invalid_argument("Movie not found.");
}

void Cinema::update_movie_haul(Movie* new_movie, unsigned new_haul_id)
{
	MyString today = Help_Program::getCurrentDateStr();
	bool passed = Help_Program::is_before(new_movie->Date(), today);
	if (passed) {
		throw std::runtime_error("Movie has already been played. Cannot update haul.");
	}
	if (!find_haul_by_id(new_haul_id)) {
		throw std::invalid_argument("Haul does not exist.");
	}
	if (!is_haul_available(new_haul_id, new_movie->Date(), new_movie->Start(), new_movie->Finish(), new_movie)) {
		throw std::runtime_error("Another movie will be projectored in this haul.");
	}
	new_movie->set_haul_id(new_haul_id);
}

void Cinema::close_haul(unsigned haul_id, Vector<User*>& users)
{
	Haul* haul = find_haul_by_id(haul_id);
	if (!haul) {
		throw new std::runtime_error("Haul not found.");
	}
	MyString today = Help_Program::getCurrentDateStr();

	for (unsigned i = 0; i < movies.Size(); i++)
	{
		Movie* m = movies[i];
		if (m->Haul_id() != haul_id)
			continue;
		bool hasPassed = Help_Program::is_before(m->Date(), today);
		if (hasPassed)
			m->set_haul_id(Constants::UNKNOWN_HAUL_ID);
		else 
		{
			for (unsigned j = 0; j < users.Size(); j++)
			{
				users[j]->remove_movie(m, false);
			}
			remove_movie_by_id(m->Id());
		}
	}
	remove_movie_by_id(haul_id);
}

void Cinema::print_movies() const
{
	for (int i = 0; i < movies.Size(); i++)
		movies[i]->print();
}

Cinema::~Cinema()
{
	free();
}