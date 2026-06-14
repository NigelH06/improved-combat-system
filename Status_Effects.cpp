#include "Status_Effects.h"
#include "Combatant.h"
#include <random>

static std::mt19937 gen(std::random_device{}());

int random_s(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(gen);
}

int shock(Combatant& c, Combatant& opp)
{
	int shock_bonus = random_s(1, 10);
	int shock_val = c.get_attack() + shock_bonus; 
	int new_attack = opp.get_attack() - shock_val; 
	opp.set_attack(new_attack); 
	return shock_val; 
}

int burn(Combatant& c, Combatant& opp)
{
	int burn_bonus = random_s(2, 12); 
	int burn_val = c.get_attack() + burn_bonus; 
	int new_health = opp.get_health() - burn_val; 
	opp.set_health(new_health); 
	return burn_val; 
}

int freeze(Combatant& c, Combatant& opp)
{
	int freeze_bonus = random_s(5, 15); 
	int freeze_val = c.get_defense() + freeze_bonus; 
	int new_defense = opp.get_defense() - freeze_val; 
	opp.set_defense(new_defense); 
	return freeze_val;
}

int corrupt(Combatant& c, Combatant& opp)
{
	// A lazy check for the combatant attack NOT being 0 
	int corrupt_bonus = random_s(1, 20); 
	int corrupt_val = random_s(1, 10) + corrupt_bonus; 
	opp.set_health(opp.get_health() - corrupt_val); 
	opp.set_attack(opp.get_attack() - corrupt_val); 
	opp.set_defense(opp.get_defense() - corrupt_val); 
	opp.set_mana(opp.get_mana() - corrupt_val); 
	return corrupt_val;
}

int poison(Combatant& c, Combatant& opp)
{
	int poison_val = random_s(10, 20);
	opp.set_health(opp.get_health() - poison_val); 
	opp.set_mana(opp.get_mana() - poison_val); 
	return poison_val;
}

// Function Pointer Set up (Just in case I forget the name of the technique)
int (*status_list[5])(Combatant& c, Combatant& opp) = { shock, burn, freeze, corrupt, poison };


Status_Effect::Status_Effect()
{
	e = Effects::NONE; 
	name = effects_list[effect_to_int(e)];
    tick = 0; 
	enabled = false;
}

Status_Effect::Status_Effect(Effects ef,int tck)
	:e{ ef }, name{ effects_list[effect_to_int(e)] }, tick{ tck }
{
	enabled = true; 
}

Effects Status_Effect::get_effect() const
{
	return e;
}


string Status_Effect::get_name() const
{
	return name;
}



void Status_Effect::set_status_enabled(bool state)
{
	enabled = state;
}

bool Status_Effect::get_status_state() const
{
	return enabled; 
}

int Status_Effect::use_effect(Combatant& c, Combatant& opp)
{
	if (e == Effects::NONE)
		return NO_EFFECT;  

	if (enabled)
	{
		int (*effect)(Combatant & c, Combatant & opp) = status_list[effect_to_int(e)];
		return effect(c, opp);
	}
	
	return EFFECT_OK; // just a placeholder 
}

void Status_Effect::apply_tick_dmg(Combatant& c, Combatant& opp)
{
	if (enabled)
	{
		int t_dmg = 0;
		switch (e)
		{
		case Effects::SHOCK:
			t_dmg = SHOCK_TICK;
			break;
		case Effects::BURN:
			t_dmg = BURN_TICK;
			break;
		case Effects::FREEZE:
			t_dmg = FREEZE_TICK;
			break;

		case Effects::CORRUPT:
			t_dmg = CORRUPT_TICK;
			break;
		case Effects::POISON:
			t_dmg = POISON_TICK;
			break;
		default:
			cout << "INVALID TICK DAMAGE!\n";
			return;
		}

		int t = tick;
		while (t > 0)
		{
			opp.set_health(opp.get_health() - t_dmg);
			cout << "HIT FOR " << t_dmg << std::endl;
			t--;
		}
		return;
	}
}
