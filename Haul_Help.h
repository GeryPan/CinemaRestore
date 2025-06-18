#pragma once
#include "Movie.h"
#include "Haul.h"
#include "Vector.hpp"
#include "User.h"

namespace Haul_Help
{
	bool is_seat_free(unsigned row, unsigned col, const Movie& movie, const Haul& haul, Vector<User*> users);
}

