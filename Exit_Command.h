#pragma once
#include "Command.h" 
#include "Id_Counter_Manager.h"

class Exit_Command : public Command 
{
public:
	const char* Name();
	bool need_login();
	bool need_admin();
	void execute(std::stringstream& args, User*& user, Cinema& cinema,
		Vector<User*>& users, Id_Counter_Manager& id_manager) override;
};