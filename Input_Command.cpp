#include "Input_Command.h"


Input_Command::Input_Command()
{
	cmd = Command::INVALID; 
}

Command Input_Command::get_cmd()  { 
	cout << "\n==================== Enter a Command ===============\n"; 
	int cmd_num = 1;
	for (string cmd : commands)
		cout << cmd_num++ << "." << cmd << '\n';
	cout << "====================================================\n";
	int c; 
	cin >> c; // if cin fails-> probably causes issues in a larger system
	Command cmd = static_cast<Command>(c); 
	switch (cmd)
	{
	case Command::BASIC:
	case Command::ABILITY:
	case Command::ITEM:
		return cmd; 
	default:
		return Command::INVALID; 
	}
}

Command Input_Command::get_random_cmd()
{
	return static_cast<Command>(random_num(1, 3));
}