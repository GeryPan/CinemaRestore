#pragma once
#include "Id_Counter.h"
#include "Vector.hpp"
class Id_Counter_Manager 
{
	Vector<Id_Counter*> counters;
	Id_Counter* find(const char* name) const;
public:
	Id_Counter_Manager();
	Id_Counter_Manager(const Id_Counter_Manager& other);
	Id_Counter_Manager& operator=(const Id_Counter_Manager& other);

	unsigned generate_next_id(const char* name);
	unsigned peek_current_id(const char* name) const;

	void set_source(Vector<Id_Counter*>& source);
	Vector<Id_Counter*> Source() const;
};
