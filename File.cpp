#include "File.h"
#include "Serialize.h"
#include "Serialize_User.h"
#include "Help_Program.h"
#include <fstream>

static User* serialize_from(const Serialize_User* su, const Cinema& cinema)
{
	User* user = new User(su->id, su->username, su->password, su->balance, su->admin);

	for (unsigned i = 0; i < su->tickets_soon.Size(); i++)
	{
		const Serialize_Ticket* t = su->tickets_soon[i];
		Movie* m = cinema.find_movie_by_id(t->movie_id);
		if (!m)
			throw std::runtime_error("Invalid movie_id in Ticket.");
		user->add_ticket(new Ticket(m->Id(), t->row, t->col));
	}
	for (unsigned i = 0; i < su->watched_movies_id.Size(); i++)
	{
		unsigned mid = su->watched_movies_id[i]->Movie_id();
		Movie* m = cinema.find_movie_by_id(mid);
		if (!m) throw std::runtime_error("Invalid movieId in watched list.");
		user->add_watched_movie(m);
	}
	for (unsigned i = 0; i < su->rated_movies.Size(); i++)
	{
		const Serialize_Rating* r = su->rated_movies[i];
		Movie* m = cinema.find_movie_by_id(r->movie_id);
		if (!m) 
		throw std::runtime_error("Invalid movieId in rating.");
		user->rate_movie(m, r->rating);
	}

	return user;
}

static Vector<Serialize_User*> serialize_vector(const Vector<User*>& users)
{
	Vector<Serialize_User*> result;
	for (unsigned i = 0; i < users.Size(); i++)
		result.push(users[i]->serialize_user());
	return result;
}

static Vector<User*> serialize_vector_from(const Vector<Serialize_User*>& input, const Cinema& cinema)
{
	Vector<User*> result;
	for (unsigned i = 0; i < input.Size(); i++)
		result.push(serialize_from(input[i], cinema));
	return result;
}

namespace File
{
	void write_in_file(const Cinema& cinema, const Vector<User*>& users, Id_Counter_Manager& id_manager, const MyString& file_name)
	{
		std::ofstream file(file_name.c_str(), std::ios::binary | std::ios::trunc);
		if (!file) 
			throw std::runtime_error("Failed to create file for writing.");
		file.close();
		std::ofstream ofs(file_name.c_str(), std::ios::binary);
		if (!ofs) 
			throw std::runtime_error("Failed to open file for writing.");
		ofs << id_manager.Source();
		ofs << cinema.Hauls();
		ofs << cinema.Movies();
		Vector<Serialize_User*> serials = serialize_vector(users);
		ofs << serials;
		ofs.close();
	}

	Cinema read_in_file(Cinema& cinema, Vector<User*>& users, Id_Counter_Manager& id_manager, const MyString& file_name)
	{
		std::ifstream ifs(file_name.c_str(), std::ios::binary);
		if (!ifs) return Cinema();
		Vector<Id_Counter*> ids;
		ifs >> ids;
		id_manager.set_source(ids);
		Vector<Haul*> hauls;
		Vector<Movie*> movies;
		ifs >> hauls;
		ifs >> movies;
		cinema = Cinema(std::move(movies), std::move(hauls));
		Vector<Serialize_User*> serials;
		ifs >> serials;
		users = serialize_vector_from(serials, cinema);
		return cinema;
	}
}
