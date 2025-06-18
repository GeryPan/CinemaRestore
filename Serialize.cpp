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
#include "Serialize_Watched_Movies.h"
#include "Movie_Factory.h"
#include "Help_Program.h"
#include "MyString.h"
#include <iostream>
#include <cstring>

std::ostream& operator<<(std::ostream& os, const MyString& str)
{
	unsigned len = static_cast<unsigned>(str.size);
	os.write((char*)&len, sizeof(unsigned));
	os.write(str.data, len);
	return os;
}

std::istream& operator>>(std::istream& is, MyString& str)
{
	unsigned len;
	is.read((char*)&len, sizeof(unsigned));
	if (!is || len < 0) throw std::runtime_error("Invalid string length during read");
	char* buffer = new char[len + 1];
	is.read(buffer, len);
	if (!is) {
		delete[] buffer;
		throw std::runtime_error("Failed to read string data");
	}
	buffer[len] = '\0';
	str = MyString(buffer);
	delete[] buffer;
	return is;
}

std::ostream& operator<<(std::ostream& os, const Haul& h)
{
	int id = h.Id(), rows = h.Rows(), cols = h.Cols();
	os.write((const char*)&id, sizeof(unsigned));
	os.write((const char*)&rows, sizeof(unsigned));
	os.write((const char*)&cols, sizeof(unsigned));
	return os;
}
std::istream& operator>>(std::istream& is, Haul& h)
{
	unsigned id, rows, cols;
	is.read((char*)&id, sizeof(unsigned));
	is.read((char*)&rows, sizeof(unsigned));
	is.read((char*)&cols, sizeof(unsigned));
	h = Haul(id, rows, cols);
	return is;
}

std::ostream& operator<<(std::ostream& os, const Serialize_Watched_Movies& swm)
{
	unsigned id = swm.Movie_id();
	os.write((const char*)&id, sizeof(unsigned));
	return os;
}
std::istream& operator>>(std::istream& is, Serialize_Watched_Movies& swm)
{
	unsigned id;
	is.read((char*)&id, sizeof(unsigned));
	return is;
	swm.set_movie_id(id);
}

std::ostream& operator<<(std::ostream& os, const Serialize_Ticket& st)
{
	std::cout << "Saving: " << st.movie_id << " " << st.row << " " << st.col << std::endl;
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
	os.write((char*)&su.id, sizeof(unsigned));
	os << su.username;
	os << su.password;
	os.write((char*)&su.balance, sizeof(double));
	os.write((char*)&su.admin, sizeof(bool));
	os << su.tickets_soon;
	os << su.watched_movies_id;
	os << su.rated_movies;
	return os;
}
std::istream& operator>>(std::istream& is, Serialize_User& su)
{
	su.free();
	is.read((char*)&su.id, sizeof(unsigned));
	is >> su.username;
	is >> su.password;
	is.read((char*)&su.balance, sizeof(double));
	is.read((char*)&su.admin, sizeof(bool));
	unsigned ticket_count;
	is.read((char*)&ticket_count, sizeof(unsigned));
	is >> su.tickets_soon;
	is >> su.watched_movies_id;
	is >> su.rated_movies;
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
		v.push(obj);
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