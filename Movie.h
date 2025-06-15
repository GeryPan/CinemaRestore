#pragma once
#include <iostream>

class Movie {
protected:
    unsigned id;
    unsigned haul_id;
    char* title;
    float rate;
    char* genre;
    unsigned continuance;
    char* date;
    unsigned year;
    char* start; 
    char* finish;    

    void free();
    void copyFrom(const Movie& other);
    void write(std::ostream& os) const;
    void read(std::istream& is);
public:
    Movie();
    Movie(const Movie& other);
    Movie(unsigned new_id, unsigned new_haul_id, const char* new_title, float new_rate,
        const char* new_genre, unsigned new_continuance, const char* new_date, unsigned new_year,
        const char* new_start, const char* new_finish);
    Movie& operator=(const Movie& other);
    unsigned Id() const;
    unsigned Haul_id() const;
    const char* Title() const;
    const char* Date() const;
    const char* Start() const;
    const char* Finish() const;

    void set_title(const char* new_title);
    void set_haul_id(unsigned new_haul_id);

    virtual double calculate_ticket_price() const = 0;
    virtual void serialize(std::ostream& os) const = 0;
    virtual void deserialize(std::istream& is) = 0;
    virtual void print() const = 0;
    virtual Movie* clone() const = 0;
    virtual ~Movie();
};