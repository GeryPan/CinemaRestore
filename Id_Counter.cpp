#include "Id_Counter.h"
#include "Help_Program.h"

void Id_Counter::free()
{
    if (name) 
    {
        delete[] name;
        name = nullptr;
    }
}

void Id_Counter::copyFrom(const Id_Counter& other)
{
    name = Help_Program::copy_str(other.name);
    value = other.value;
}

Id_Counter::Id_Counter()
{
    name = nullptr;
    value = 0;
    }

    Id_Counter::Id_Counter(const Id_Counter& other)
    {
        copyFrom(other);
    }
    Id_Counter::Id_Counter(const char* new_name, unsigned start)
    {
        value = start;
        name = Help_Program::copy_str(new_name);
    }
    Id_Counter& Id_Counter::operator=(const Id_Counter& other)
    {
        if (this != &other) 
        {
            free();
            copyFrom(other);
        }
        return *this;
    }

    void Id_Counter::increase()
    {
       value++;
    }

    const char* Id_Counter::Name() const
    {
        return name;
    }

    unsigned Id_Counter::Value() const
    {
        return value;
    }

    std::ostream& operator<<(std::ostream& os, const Id_Counter& id_counter);
    std::istream& operator>>(std::istream& is, Id_Counter& id_counter);
    Id_Counter* Id_Counter::clone() const
    {
        return new Id_Counter(*this);
    }

    Id_Counter::~Id_Counter()
    {
        free();
    }