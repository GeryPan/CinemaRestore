#include "Buy_Ticket.h"
#include "User.h"
#include "Haul_Help.h"
#include "User_Input.h"
#include "Id_Counter_Manager.h"
#include "MyString.h"
#include "Ticket.h"
#include <stdexcept>

const MyString Buy_Ticket::Name() const
{
    return "buy-ticket";
}
bool Buy_Ticket::need_login() const
{
    return true;
}
bool Buy_Ticket::need_admin() const
{
    return false;
}
void Buy_Ticket::execute(std::stringstream& args, User*& user, Cinema& cinema,
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

    if (!Haul_Help::is_seat_free(row, col, *movie, *haul, users))
        throw std::runtime_error("Is already taken.");
    double price = movie->calculate_ticket_price();
    if (user->Balance() < price)
        throw std::runtime_error("Don't have enough money.");
   user->add_balance(-price);
    user->add_ticket(new Ticket(movie->Id(), row, col));
}
Command* Buy_Ticket::clone() const
{
    return new Buy_Ticket();
}