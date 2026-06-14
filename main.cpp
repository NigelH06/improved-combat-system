#include "Combat_Manager.h"
#include "Input_Command.h"
using std::rand;

/* Interactive Simulation */

int main()
{
	srand(time(NULL));

	Combatant one{ "Ember Prime", Ability{Abilities::FIREBALL, Status_Effect{Effects::BURN, 3}, 12, 2}, Item{Items::ATK_POTION, Item_Target::SELF,  4}, 150, 30, 20, 50 };
	Combatant two{ "Trinity Prime", Ability{Abilities::INSIGHT, Status_Effect{Effects::FREEZE, 5}, 80, 1}, Item{Items::DEF_DOWN_POTION, Item_Target::OPPONENT, 3}, Progression{3, 1000, 5000}, 150,  25, 25, 80 };
	Combat_Manager manager{one, two};
	manager.run_input_sim(); 
	return 0;
}

