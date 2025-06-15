#pragma once
#include "Command.h" 
#include "Id_Counter_Manager.h"

class Add_Movie : public Command 
{
public:
	const char* Name() const override;
	bool need_admin() const override;
	bool need_login() const override;
	void execute(std::stringstream& args, User*& user, Cinema& cinema, 
		Vector<User*>& users, Id_Counter_Manager& id_manager) override;
};