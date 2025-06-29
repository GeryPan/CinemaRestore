#pragma once
#include "Vector.hpp"  
#include "Serialize_Ticket.h"  
#include "Serialize_Rating.h"  
#include "Serialize_Watched_Movies.h"
#include "MyString.h"
#include <iostream>  

class Serialize_User
{
	void free();
	void copyFrom(const Serialize_User& other);
public:
	unsigned id;
	MyString username;
	MyString password;
	double balance;
	bool admin;
	Vector<Serialize_Ticket*> tickets_soon;
	Vector<Serialize_Watched_Movies*> watched_movies_id;
	Vector<Serialize_Rating*> rated_movies;
	Serialize_User* clone() const;
	Serialize_User();
	Serialize_User(const Serialize_User& other);
	Serialize_User& operator=(const Serialize_User& other);
	friend std::istream& operator>>(std::istream& is, Serialize_User& su);
	friend std::ostream& operator<<(std::ostream& os, const Serialize_User& su);
	~Serialize_User();
};