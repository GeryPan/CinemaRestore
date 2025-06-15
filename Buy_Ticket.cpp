#include "Buy_Ticket.h"
#include "User.h"
#include "User_Input.h"
#include "Ticket.h"
#include <stdexcept>

const char* Name() 
{
	return "buy-ticket"; 
}
bool need_login() 
{ 
	return true; 
}
bool need_admin() 
{ 
	return false; 
}
void execute(std::stringstream& args, User*& user, Cinema& cinema,
	Vector<User*>& users, Id_Counter_Manager& id_manager) 
{
    unsigned movie_id = User_Input::get_unsigned(args, 1, id_manager.peek_current_id("movie"));
Movie* movie = cinema.find_movie_by_id(movie_id);
 if (!movie)
        throw std::runtime_error("Movie doesn't found.");
    Haul* haul = cinema.find_haul_by_id(movie->Haul_id());
    if (!haul)
        throw std::runtime_error("Haul doesn't found for this movie.");
    unsigned row_in = User_Input::get_unsigned(args, 1, haul->Rows());
    unsigned col_in = User_Input::get_unsigned(args, 1, haul->Cols());
    unsigned row = row_in - 1;
    unsigned col = col_in - 1;

    if (!haul->is_seat_free(row, col))
        throw std::runtime_error("Is already taken.");
double price = movie->calculate_ticket_price();
    if (user->Balance() < price)
        throw std::runtime_error("Don't have enough money.");
    haul->take_seat(row, col);
    user->add_balance(-price);
    user->add_ticket(new Ticket(movie, row, col));
}