#pragma once
#include <iostream>  
#include "Vector.hpp" 
#include "Ticket.h"  
#include "Drama.h"  
#include "Action.h"  
#include "Documentary.h" 
#include "Haul.h"    
#include "Movie_Factory.h"
#include "Serialize_Watched_Movies.h"  
#include "Serialize_Ticket.h"  
#include "Serialize_Rating.h"  
#include "Serialize_User.h"  
#include "MyString.h"

std::ostream& operator<<(std::ostream& os, const MyString& str);
std::istream& operator>>(std::istream& is, MyString& str);

std::ostream& operator<<(std::ostream& os, const Haul& h);
std::istream& operator>>(std::istream& is, Haul& h);

std::ostream& operator<<(std::ostream& os, const Serialize_Watched_Movies& swm);
std::istream& operator>>(std::istream& is, Serialize_Watched_Movies& swm);

std::ostream& operator<<(std::ostream& os, const Serialize_Ticket& st);
std::istream& operator>>(std::istream& is, Serialize_Ticket& st);

std::ostream& operator<<(std::ostream& os, const Serialize_Rating& sr);
std::istream& operator>>(std::istream& is, Serialize_Rating& sr);

std::ostream& operator<<(std::ostream& os, const Serialize_User& su);
std::istream& operator>>(std::istream& is, Serialize_User& su);

std::ostream& operator<<(std::ostream& os, const Id_Counter& id_counter);
std::istream& operator>>(std::istream& is, Id_Counter& id_counter);

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T*>& v);
template<typename T>
std::istream& operator>>(std::istream& is, Vector<T*>& v);

template<>
std::istream& operator>>(std::istream& is, Vector<Movie*>& v);

template<>
std::ostream& operator<<(std::ostream& os, const Vector<Movie*>& v);