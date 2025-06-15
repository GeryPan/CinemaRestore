#include "Serialize.h"
#include "Vector.hpp"
#include "Ticket.h"
#include "Drama.h"
#include "Action.h"
#include "Documentary.h"
#include "Haul.h"
#include "Serialize_Ticket.h"
#include "Serialize_Rating.h"
#include "Serialize_User.h"
#include "Movie_Factory.h"
#include "Help_Program.h"
#include <iostream>
#include <cstring>

std::ostream& operator<<(std::ostream& os, const Haul& h)
{
	unsigned id = h.Id(),
		rows = h.Rows(), 
		cols = h.Cols();
	os.write((const char*)&id, sizeof(unsigned));
	os.write((const char*)&rows, sizeof(unsigned));
	os.write((const char*)&cols, sizeof(unsigned));
	for (unsigned i = 0; i < rows; i++)
	{
		for (unsigned j = 0; j < cols; j++) {
			bool taken = !h.is_seat_free(i, j);
			os.write((const char*)&taken, sizeof(bool));
		}
	}
	return os;
}
std::istream& operator>>(std::istream& is, Haul& h)
{
	unsigned id, rows, cols;
	is.read((char*)&id, sizeof(unsigned));
	is.read((char*)&rows, sizeof(unsigned));
	is.read((char*)&cols, sizeof(unsigned));
	h = Haul(id, rows, cols);
	for (unsigned i = 0; i < rows; ++i)
	{
		for (unsigned j = 0; j < cols; ++j) {
			bool taken;
			is.read((char*)&taken, sizeof(bool));
			if (taken) h.take_seat(i, j);
		}
	}
	return is;
}

std::ostream& operator<<(std::ostream& os, const Ticket& t)
{
	unsigned movie_id = t.Movie()->Id();
	os.write((const char*)&movie_id, sizeof(unsigned));
	unsigned row = t.Row(), col = t.Col();
	os.write((const char*)&row, sizeof(unsigned));
	os.write((const char*)&col, sizeof(unsigned));
	return os;
}
std::istream& operator>>(std::istream& is, Ticket& t)
{
	unsigned movieId, row, col;
	is.read((char*)&movieId, sizeof(unsigned));
	is.read((char*)&row, sizeof(unsigned));
	is.read((char*)&col, sizeof(unsigned));
	t = Ticket(nullptr, row, col);
	return is;
}

std::ostream& operator<<(std::ostream& os, const Serialize_Ticket& st)
{
	os.write((const char*)&st.movie_id, sizeof(unsigned));
	os.write((const char*)&st.row, sizeof(unsigned));
	os.write((const char*)&st.col, sizeof(unsigned));
	return os;
}
std::istream& operator>>(std::istream& is, Serialize_Ticket& st)
{
	is.read((char*)&st.movie_id, sizeof(unsigned));
	is.read((char*)&st.row, sizeof(unsigned));
	is.read((char*)&st.col, sizeof(unsigned));
	return is;
}

std::ostream& operator<<(std::ostream& os, const Serialize_Rating& sr)
{
	os.write((const char*)&sr.movie_id, sizeof(unsigned));
	os.write((const char*)&sr.rating, sizeof(unsigned));
	return os;
}
std::istream& operator>>(std::istream& is, Serialize_Rating& sr)
{
	is.read((char*)&sr.movie_id, sizeof(unsigned));
	is.read((char*)&sr.rating, sizeof(unsigned));
	return is;
}

std::ostream& operator<<(std::ostream& os, const Serialize_User& su)
{
	os.write((const char*)&su.id, sizeof(unsigned));
	Help_Program::write(os, su.username);
	Help_Program::write(os, su.password);
	os.write((const char*)&su.balance, sizeof(double));
	os.write((const char*)&su.admin, sizeof(bool));

	unsigned ticket_count = su.tickets_soon.Size();
	os.write((const char*)&ticket_count, sizeof(unsigned));
	for (unsigned i = 0; i < ticket_count; i++)
		os << *su.tickets_soon[i];

	unsigned watched_count = su.watched_movies_id.Size();
	os.write((const char*)&watched_count, sizeof(unsigned));
	for (unsigned i = 0; i < watched_count; i++)
		os.write((const char*)su.watched_movies_id[i], sizeof(unsigned));

	unsigned rated_count = su.rated_movies.Size();
	os.write((const char*)&rated_count, sizeof(unsigned));
	for (unsigned i = 0; i < rated_count; i++)
		os << *su.rated_movies[i];

	return os;
}
std::istream& operator>>(std::istream& is, Serialize_User& su)
{
	su.free(); 
	is.read((char*)&su.id, sizeof(unsigned));
	su.username = Help_Program::read(is);
	su.password = Help_Program::read(is);
	is.read((char*)&su.balance, sizeof(double));
	is.read((char*)&su.admin, sizeof(bool));

	unsigned ticket_count;
	is.read((char*)&ticket_count, sizeof(unsigned));
	for (unsigned i = 0; i < ticket_count; i++)
	{
		Serialize_Ticket* ts = new Serialize_Ticket();
		is >> *ts;
		su.tickets_soon.push(ts);
	}

	unsigned watched_count;
	is.read((char*)&watched_count, sizeof(unsigned));
	for (unsigned i = 0; i < watched_count; i++)
	{
		unsigned* m = new unsigned();
		is.read((char*)m, sizeof(unsigned));
		su.watched_movies_id.push(m);
	}

	unsigned rated_count;
	is.read((char*)&rated_count, sizeof(unsigned));
	for (unsigned i = 0; i < rated_count; i++)
	{
		Serialize_Rating* sr = new Serialize_Rating();
		is >> *sr;
		su.rated_movies.push(sr);
	}
	return is;
}

std::ostream& operator<<(std::ostream& os, const Id_Counter& id_counter)
{
	Help_Program::write(os, id_counter.name);
	os.write((const char*)&id_counter.value, sizeof(unsigned));
	return os;
}
std::istream& operator>>(std::istream& is, Id_Counter& id_counter)
{
	id_counter.free(); 
	id_counter.name = Help_Program::read(is);
	is.read((char*)&id_counter.value, sizeof(unsigned));
	return is;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T*>& v) {
	unsigned size = v.Size();
	os.write((const char*)&size, sizeof(unsigned));

	for (unsigned i = 0; i < size; i++)
	{
		os << *v[i];
	}
	return os;
}

template<typename T>
std::istream& operator>>(std::istream& is, Vector<T*>& v) {
	unsigned size;
	is.read((char*)&size, sizeof(unsigned));

	for (unsigned i = 0; i < size; i++)
	{
		T* obj = new T();
		is >> *obj;
		vec.push_back(obj);
	}
	return is;
}
template<>
std::ostream& operator<<(std::ostream& os, const Vector<Movie*>& v)
{
	unsigned size = v.Size();
	os.write((const char*)&size, sizeof(unsigned));
	for (unsigned i = 0; i < size; i++)
		v[i]->serialize(os);  
	return os;
}

template<>
std::istream& operator>>(std::istream& is, Vector<Movie*>& v)
{
	unsigned size;
	is.read((char*)&size, sizeof(unsigned));
	for (unsigned i = 0; i < size; i++)
	{
		Movie* m = Movie_Factory::deserialize_movie(is);
		v.push(m);
	}
	return is;
}
