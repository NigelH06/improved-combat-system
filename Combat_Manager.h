#ifndef COMBAT_MANAGER_H
#define COMBAT_MANAGER_H

#include "Ability.h"
#include "Combatant.h"
#include "Status_Effects.h"
#include <conio.h>
#include "Input_Command.h"
#define ONE_WINS true
#define TWO_WINS false

inline void press_space()
{
	cout << "PRESS SPACE TO CONTINUE!\n";
	char ch;
	do
	{
		ch = _getch();

	} while (ch != ' ');
}

class Combat_Manager
{
private:
	Combatant& combatant_one;
	Combatant& combatant_two; 
	Input_Command cmd;  
	int turn; 
	bool winner() const;
	void process_ability(Combatant& c); 
	void use_ability(Combatant& c, Combatant& opp); 
	void use_item(Combatant& c, Combatant& opp); 
	bool stats_low(Combatant& c); 
public:
	Combat_Manager(Combatant& c1, Combatant& c2);
	Combatant& get_combatant_one();
	Combatant& get_combatant_two(); 
	void run_auto_sim(); 
	void run_input_sim();
};

#endif