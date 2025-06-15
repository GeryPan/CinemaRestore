#include "File.h"
#include "Serialize.h"
#include "Serialize_User.h"
#include "Help_Program.h"
#include <fstream>

static User* serialize_from(const Serialize_User* us, const Cinema& cinema) 
{
	User* user = new User(us->id, Help_Program::copy_str(us->username), Help_Program::copy_str(us->password), us->balance, us->admin);

	for (unsigned i = 0; i < us->tickets_soon.Size(); i++)
	{
		const Serialize_Ticket* t = us->upcomingTickets[i];
		Movie* m = cinema.find_movie_by_id(t->movie_id);
		if (!m) 
			throw std::runtime_error("Invalid movie_id in Ticket.");
		user->addTicket(new Ticket(m, t->row, t->col));
	}
	for (unsigned i = 0; i < us->watched_movies_id.Size(); i++) 
	{
		unsigned mid = *us->watched_movies_id[i];
		Movie* m = cinema.find_movie_by_id(mid);
		if (!m) throw std::runtime_error("Invalid movieId in watched list.");
		user->addWatchedMovie(m);
	}
	for (unsigned i = 0; i < us->rated_movies.Size(); i++) 
	{
		const Serialize_Rating* r = us->ratedMovies[i];
		Movie* m = cinema.find_movie_by_id(r->movie_id);
		if (!m) throw std::runtime_error("Invalid movieId in rating.");
		user->rateMovie(m, r->rating);
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
		result.push_back(serialize_from(input[i], cinema));
	return result;
}

namespace File 
{
	void write_in_file(const Cinema& cinema, const Vector<User*>& users, Id_Counter_Manager& id_manager, const char* file_name)
	{
		std::ofstream file(file_name, std::ios::binary | std::ios::trunc);
		if (!file) throw std::runtime_error("Failed to create file for writing.");
		file.close();
		std::ofstream ofs(file_name, std::ios::binary);
		if (!ofs) throw std::runtime_error("Failed to open file for writing.");
		ofs << id_manager.Source();
		ofs << cinema.Hauls();
		ofs << cinema.Movies();
		Vector<Serialize_User*> serials = serialize_vector(users);
		ofs << serials;
		ofs.close();
	}

	void read_in_file(Cinema& cinema, Vector<User*>& users, Id_Counter_Manager& id_manager, const char* file_name)
	{
		std::ifstream ifs(file_name, std::ios::binary);
		if (!ifs) return; 
		PointerVector<IdCounter*> ids;
		in >> ids;
		idManager.setSource(ids);
		PointerVector<Haul*> hauls;
		PointerVector<Movie*> movies;
		ifs >> hauls;
		ifs >> movies;
		cinema = Cinema(movies, hauls);
		PointerVector<UserSerializable*> serials;
		ifs >> serials;
		users = fromSerializableVector(serials, cinema);
	}
}

