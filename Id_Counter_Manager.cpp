#include "Id_Counter_Manager.h"
#include <cstring>
#include "Help_Program.h"

Id_Counter* Id_Counter_Manager::find(const char* name) const
{
	for (unsigned i = 0; i < counters.Size(); i++)
	{
		if (std::strcmp(counters[i]->Name(), name) == 0)
			return counters[i];
	}
	return nullptr;
}

Id_Counter_Manager::Id_Counter_Manager()
{}

Id_Counter_Manager::Id_Counter_Manager(const Id_Counter_Manager& other)
{
	counters = other.counters;
}

	Id_Counter_Manager& Id_Counter_Manager::operator=(const Id_Counter_Manager& other)
	{
		if (this != &other) 
		{
			counters = other.counters;
		}
		return *this;
	}

	unsigned Id_Counter_Manager::generate_next_id(const char* name)
	{
		Id_Counter* found = find(name);
		if (!found) 
		{
			Id_Counter* new_counter = new Id_Counter(name, 1);
			counters.push(new_counter);
			return 1;
		}
	}

	unsigned Id_Counter_Manager::peek_current_id(const char* name) const
	{
		Id_Counter* found = find(name);
		return found == nullptr ? 0 : found->Value();
	}

	void Id_Counter_Manager::set_source(Vector<Id_Counter*>& source)
	{
		counters = source;
	}

	Vector<Id_Counter*> Id_Counter_Manager::Source() const
	{
		return counters;
	}