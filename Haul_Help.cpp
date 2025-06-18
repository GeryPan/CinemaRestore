#include "Haul_Help.h"
#include "MyString.h"

bool is_seat_free(unsigned row, unsigned col, const Movie& movie, const Haul& haul, Vector<User*> users)
{
	if (row < 0 || row >= haul.Rows() || col < 0 || col >= haul.Cols()) {
		return false; // Invalid seat position
	}

	for (unsigned i = 0; i < users.Size(); i++) 
	{
		Vector<Ticket*> userTickets = users[i]->Tickets_soon();

		for (unsigned j = 0; j < userTickets.Size(); j++) 
		{
			Ticket* userTicket = userTickets[j];
			if (userTicket->Movie_Id() != movie.Id()
				|| userTicket->Row() != row
				|| userTicket->Col() != col
				) {
				continue;
			}
			return false; // Seat is already taken
		}
	}
	return true;
}