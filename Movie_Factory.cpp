#include "Movie_Factory.h"
#include "Help_Program.h"
#include "User_Input.h"
#include "Action.h"
#include "Drama.h"
#include "Documentary.h"
#include "Constants.h"
#include <cstring>
#include <stdexcept>

Movie* Movie_Factory::create_movie(Id_Counter_Manager& new_id_manager, MyString genre)
{
    if (Help_Program::compare_strings(genre, "Action") != 0 &&
        Help_Program::compare_strings(genre, "Documentary") != 0 &&
        Help_Program::compare_strings(genre, "Drama") != 0) {
        throw std::invalid_argument("Genre cannot be empty.");
    }
    MyString title = User_Input::enter_text("Enter name: ", Constants::MAX_MOVIE_NAME_LENGTH);
    float rating = User_Input::enter_float("Enter rating: ", Constants::MIN_RATING, Constants::MAX_RATING);
    unsigned continuance = User_Input::enter_unsigned("Enter continuance in minutes: ", 1, Constants::MAX_MOVIE_CONTINUANCE);
    unsigned year = User_Input::enter_unsigned("Enter release year: ", Constants::MIN_MOVIE_RELEASE_YEAR, Constants::MAX_MOVIE_RELEASE_YEAR);
    unsigned haul_id = User_Input::enter_unsigned("Enter haul ID: ");
    MyString date = User_Input::enter_date("Enter date (YYYY-MM-DD): ");
    MyString start = User_Input::enter_time("Enter start time (HH:MM): ");
    MyString finish = User_Input::enter_time("Enter finish time (HH:MM): ");
    MyString releaseYearDate = MyString((std::to_string(year) + "-01-01").c_str());
    MyString now = Help_Program::getCurrentDateStr();
    MyString minReleaseDate = Help_Program::compare_strings(releaseYearDate, now) > 0 ? releaseYearDate : now;
    MyString maxStartTime = Help_Program::remove_time("23:59", continuance);
    MyString minEndTime = Help_Program::add_time(start, continuance);
   
    if (Help_Program::compare_strings(genre, "Action") == 0) {
        unsigned intensity = User_Input::enter_unsigned("Enter action intensity (0–20): ", Constants::MIN_MOVIE_INTENSITY, Constants::MAX_MOVIE_INTENSITY);
        return new Action(new_id_manager.generate_next_id("movie"), haul_id, title, rating, continuance, date, year, start, finish, intensity);
    }
    else if (Help_Program::compare_strings(genre, "Drama") == 0) {
        bool has_comedy = User_Input::enter_bool("Has comedy elements? (Yes/No)");
        return new Drama(new_id_manager.generate_next_id("movie"), haul_id, title, rating, continuance, date, year, start, finish, has_comedy);
    }
    else if (Help_Program::compare_strings(genre, "Documentary") == 0) {
        MyString theme = User_Input::enter_text("Enter theme (nature/history/person...): ", Constants::MAX_MOVIE_THEME_LENGTH);
        bool is_based = User_Input::enter_bool("Is based on true events? ");
        return new Documentary(new_id_manager.generate_next_id("movie"), haul_id, title, rating, continuance, date, year, start, finish, theme, is_based);
    }
    else {
        throw std::invalid_argument("Unsupported movie genre. Valid: Action, Drama, Documentary.");
    }
}

Movie* Movie_Factory::copy_movie(const Movie& movie) {
    if (const Action* action = dynamic_cast<const Action*>(&movie)) {
        return new Action(*action);
    }
    else if (const Drama* drama = dynamic_cast<const Drama*>(&movie)) {
        return new Drama(*drama);
    }
    else if (const Documentary* documentary = dynamic_cast<const Documentary*>(&movie)) {
        return new Documentary(*documentary);
    }
    else {
        throw std::invalid_argument("Unsupported movie type for copying.");
    }
}

Movie* Movie_Factory::deserialize_movie(std::istream& is) {
    char tag;
    is >> tag;
    is.ignore();
    Movie* movie = nullptr;
    switch (tag) {
    case 'A':
        movie = new Action();
        break;
    case 'D':
        movie = new Drama();
        break;
    case 'C':
        movie = new Documentary();
        break;
    default:
        throw std::invalid_argument("Unsupported movie type for deserialization.");
    }
    movie->deserialize(is);
    return movie;
}