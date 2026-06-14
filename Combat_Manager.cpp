#include "Combat_Manager.h"
#include "Input_Command.h"
#include <random> 


Combat_Manager::Combat_Manager(Combatant& c1, Combatant& c2)
	: combatant_one{ c1 }, combatant_two{ c2 }
{
	turn = 1;
}

Combatant& Combat_Manager::get_combatant_one() { return combatant_one; }
Combatant& Combat_Manager::get_combatant_two() { return combatant_two; }

bool Combat_Manager::winner() const
{
	if (combatant_one.get_health() != 0)
		return ONE_WINS; 

	if (combatant_two.get_health() != 0)
		return TWO_WINS;
}

// Checks if the caller's stats are lower than the threshold values or not -> considering adding decision making when stats are low
bool Combat_Manager::stats_low(Combatant& c)
{
	int thresholds[] = { STARTER_HEALTH / 2, STARTER_ATK / 2, STARTER_DEF / 2, STARTER_MANA / 2 }; 
	int c_stats[] = { c.get_health(), c.get_attack(), c.get_defense(), c.get_mana() }; 
	int thresh_pos = 0;
	for (int stat : c_stats)
	{
		if (stat <= thresholds[thresh_pos++])
			return true;
	}
	return false;
}

void Combat_Manager::use_item(Combatant& c, Combatant& opp)
{
	Item& item = c.get_item(); 
	Item_Target target = item.get_target(); 
	if (target == Item_Target::NO_TARGET)
	{
		cout << "NO TARGET SELECTED!\n"; 
		return;
	}
	if (target == Item_Target::SELF)
	{
		int item_val = item.use_item(c); 
		if (item_val != NO_STOCK)
		{
			item.dec_stock();
			int s = item.get_stock(); 
			cout << c.get_name() << " USES " << item.get_name() << " [Qty]: " << s << '\n'; 
			cout << "INCREASES BY " << item_val << '\n';
			return;
		}
	}
	if (target == Item_Target::OPPONENT)
	{
		int item_val = item.use_item(opp); 
		if (item_val != NO_STOCK)
		{
			item.dec_stock();
			int s = item.get_stock(); 
			cout << c.get_name() << " USES " << item.get_name() << " [Qty]: " << s << '\n'; 
			cout << "DECREASES BY " << item_val << '\n';
			return;
		}
	}
	cout << "NO ITEMS IN STOCK!\n";
}


void Combat_Manager::process_ability(Combatant& c)
{
	Ability& ab = c.get_ability(); 
	int cooldown = ab.get_cooldown();
	bool ab_ready = ab.ability_ready(); 
	if (ab_ready)
	{
		cout << ab.get_ability_name() << " is ready to be used!\n";
		return;
	}
	if (cooldown != 0)
	{
		if (cooldown == 1)
			cout << ab.get_ability_name() << " will be ready next turn!\n";
		else
			cout << ab.get_ability_name() << " will be ready in " << cooldown << " turns!\n";
		ab.dec_cooldown();
		return;
	}
}

void Combat_Manager::use_ability(Combatant& c, Combatant& opp)
{
	Ability& ab = c.get_ability(); 
	bool ab_ready = ab.ability_ready(); 
	string ab_name = ab.get_ability_name();
	if (ab_ready)
	{
		int ab_val = ab.use_ability(c, opp); 
		if (ab_val == INV)
			return; 
		cout << ab_name << " IS USED, DEALS " << ab_val << std::endl; 
		ab.refresh_cooldown(); 
		bool state = ab.get_effect().get_status_state(); 
		if (state)
		{
			int ef_val = ab.get_effect().use_effect(c, opp); 
			if (ef_val == NO_EFFECT || ab_val == 0)
			{
				cout << "NO EFFECT APPLIED!\n";
				return;
			}
			cout << ab.get_effect().get_name() << " IS APPLIED, DEALS " << ef_val << std::endl;
			int tick_chance = random_num(1, 5);
			if (tick_chance != 3)
			{
				cout << "NO TICK DAMAGE APPLIED!\n";
				return;
			}
			cout << "TICK DAMAGE APPLIED!\n";
			ab.get_effect().apply_tick_dmg(c, opp);
		}
		return;
	}
	cout << ab_name << " CANNOT BE USED!\n"; 
}

// A Basic Combat Simulation where Combatant Objects linearly make decisions:
// -- Turn based order in which abilities are processed and used
// -- If abilities cannot be used, basic attack is used
// Note: Items are used before 'action' starts
// Note: Abilities have a chance to apply status effects, with status effects having a chance to apply tick damage
void Combat_Manager::run_auto_sim()
{
	Combatant& one = combatant_one;
	Items one_item = one.get_item().get_item();
	Combatant& two = combatant_two;
	Items two_item = two.get_item().get_item(); 
	while (one.is_alive() && two.is_alive())
	{
		one.display_stats();
		process_ability(one);
		press_space();
		two.display_stats();
		process_ability(two);
		press_space();
		cout << "\n=============== TURN " << turn++ << " ===============\n";
		use_item(one, two); 
		if (!one.get_ability().ability_ready())
		{
			int atk_val = one.basic_attack(two); 
			if (atk_val != NO_VAL)
				cout << one.get_name() << " USES BASIC ATTACK, DEALS " << atk_val << '\n';
			else
				cout << one.get_name() << "'S BASIC ATTACK DEALS NO DAMAGE!\n";
			press_space();
		}
		use_ability(one, two);
		if (!combatant_two.is_alive())
			break;
		use_item(two, one); 
		if (!two.get_ability().ability_ready())
		{
			int atk_val = two.basic_attack(one);
			if (atk_val != NO_VAL)
				cout << two.get_name() << " USES BASIC ATTACK, DEALS " << atk_val << '\n';
			else
				cout << two.get_name() << "'S BASIC ATTACK DEALS NO DAMAGE!\n";
			press_space();
		}
		press_space();
		use_ability(two, one);
		if (!combatant_one.is_alive())
			break;
	}
	if (winner() == ONE_WINS)
	{
		cout << one.get_name() << " WINS THE BATTLE!\n";
		one.progress(two);
		one.display_stats();
	}
		
	else if (winner() == TWO_WINS)
	{
		cout << combatant_two.get_name() << " WINS THE BATTLE!\n";
		two.progress(one);
		two.display_stats();
	}
}


/* USER IS COMBATANT ONE */
// An interactable basic Combat Simulation in which user can choose actions
// -- An 'AI' opponent chooses between 1 - 3 randomly, mapping to actions
// Actions: Basic Attack, Ability Usage, Item Usage
// Otherwise, follows the same rules as the auto simulation
void Combat_Manager::run_input_sim()
{
	Combatant& user  = combatant_one; 
	Combatant& ai = combatant_two; 
	while (user.is_alive() && ai.is_alive())
	{
		cout << "\n=============== TURN " << turn++ << " ===============\n";
		user.display_stats(); 
		press_space();
		ai.display_stats(); 
		press_space(); 
		process_ability(user);
		int user_cd = user.get_ability().get_cooldown(); 
		press_space(); 
		process_ability(ai); 
		int ai_cd = ai.get_ability().get_cooldown(); 
		press_space(); 

		Command user_cmd = cmd.get_cmd();
		while (user_cmd == Command::INVALID)
		{
			cout << "INVALID COMMAND!\n";
			user_cmd = cmd.get_cmd();
		}
			

		switch (user_cmd)
		{
			case Command::BASIC:
			{
				int dmg = user.basic_attack(ai); 
				if (dmg == NO_VAL)
				{
					cout << user.get_name() << "'S BASIC ATTACK DEALS NO DAMAGE!\n";
					break;
				}

				cout << user.get_name() << " USES BASIC ATTACK, DEALS " << dmg << "!\n";
				press_space(); 
				break;
			}
			case Command::ABILITY:
				if (user.get_ability().ability_ready())
				{
					use_ability(user, ai); 
					break;
				}
				if (user_cd == 1)
				{
					cout << user.get_ability().get_ability_name() << " IS IN COOLDOWN FOR ONE MORE TURN!\n";
					break;
				}
				cout << user.get_ability().get_ability_name() << " IS IN COOLDOWN FOR " << user_cd << " MORE TURNS!\n"; 
				press_space();
				break;
			case Command::ITEM:
				use_item(user, ai); 
				press_space();
				break;
		}
		if (!ai.is_alive())
			break;

		Command ai_cmd = cmd.get_random_cmd(); 
		switch (ai_cmd)
		{
			case Command::BASIC:
			{
				int dmg = ai.basic_attack(user);
				if (dmg == NO_VAL)
				{
					cout << ai.get_name() << "'S BASIC ATTACK DEALS NO DAMAGE!\n";
					break;
				}

				cout << ai.get_name() << " USES BASIC ATTACK, DEALS " << dmg << "!\n";
				press_space();
				break;
			}

			case Command::ABILITY:
				if (ai.get_ability().ability_ready())
				{
					use_ability(ai, user);
					break;
				}
				if (ai_cd == 1)
				{
					cout << ai.get_ability().get_ability_name() << " IS IN COOLDOWN FOR ONE MORE TURN!\n";
					break;
				}
				cout << ai.get_ability().get_ability_name() << " IS IN COOLDOWN FOR " << ai_cd << " MORE TURNS!\n";
				press_space();
				break;

			case Command::ITEM:
				use_item(ai, user); 
				break;
		}
		if (!user.is_alive())
			break;
	}
	if (winner() == ONE_WINS)
	{
		cout << user.get_name() << " WINS THE BATTLE!\n";
		user.progress(ai);
		user.display_stats();
	}
	else if (winner() == TWO_WINS)
	{
		cout << ai.get_name() << " WINS THE BATTLE!\n";
		ai.progress(user);
		ai.display_stats();
	}
}

