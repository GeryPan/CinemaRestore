#pragma once
#include "Command.h" 
#include "Id_Counter_Manager.h"
#include "MyString.h"

class Remove_Movie : public Command
{
public:
	const MyString Name() const override;
	bool need_admin() const override;
	bool need_login() const override;
	void execute(std::stringstream& args, User*& user, Cinema& cinema,
		Vector<User*>& users, Id_Counter_Manager& id_manager) override;
	Command* clone() const;
};