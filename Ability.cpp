
#include "Ability.h"
#include "Combatant.h"
#include "Status_Effects.h"
static std::mt19937 gen(std::random_device{}());

int random(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(gen);
}

int fireball(Combatant& c, Combatant& opp)
{
	int fireball_dmg = c.get_attack() + 25;
	int new_health = opp.get_health() - fireball_dmg;
	opp.set_health(new_health);
	return fireball_dmg;
}

int heal(Combatant& c, Combatant& opp)
{
	int heal_val = c.get_attack() + 15;
	int new_health = c.get_health() + heal_val;
	c.set_health(new_health);
	return heal_val;
}

int drain(Combatant& c, Combatant& opp)
{
	int drain_val = c.get_attack();
	opp.set_health(opp.get_health() - drain_val);
	c.set_health(c.get_health() + drain_val);
	return drain_val;
}

int strike(Combatant& c, Combatant& opp)
{
	int strike_dmg = c.get_attack() + 35 - opp.get_defense();
	int total_dmg = opp.get_health() - strike_dmg;
	int chance = random(1, 10);
	if (chance == 5)
	{
		opp.set_health(total_dmg);
		return strike_dmg;
	}
	return 0;
}

int empower(Combatant& c, Combatant& opp)
{
	int empower_val = c.get_attack() + 10; 
	c.set_attack(c.get_attack() + empower_val); 
	return empower_val;
}

int fortify(Combatant& c, Combatant& opp)
{
	int fortify_val = c.get_defense() + 10; 
	c.set_defense(c.get_defense() + fortify_val); 
	return fortify_val;
}

int insight(Combatant& c, Combatant& opp)
{
	int insight_val = c.get_mana() + 10; 
	c.set_mana(c.get_mana() + insight_val); 
	return insight_val;
}

int heat_up(Combatant& c, Combatant& opp)
{
	int buff_val = random(1, 25); 
	c.set_health(c.get_health() + buff_val); 
	c.set_defense(c.get_defense() + buff_val);
	c.set_attack(c.get_attack() + buff_val);
	return buff_val; 
}

int (*ability_list[8])(Combatant&, Combatant&) = { fireball, heal, drain, strike, empower, fortify, insight, heat_up };




Ability::Ability()
{
	ability = Abilities::NONE;
	name = abilities[abilities_to_int(Abilities::NONE)]; 
	mana_cost = 0; 
	cooldown = 0;
	max_cooldown = 0; 
}

Ability::Ability(Abilities new_ab, Status_Effect ef, int mc, int mcd)
	: ability{ new_ab }, effect{ ef }, mana_cost {mc}, max_cooldown{ mcd }
{
	cooldown = 0;
	name = abilities[abilities_to_int(ability)]; 
}

string Ability::get_ability_name() const
{
	return name;
}

int Ability::get_mana_cost() const
{
	return mana_cost;
}


int Ability::get_cooldown() const { return cooldown;  }


Status_Effect& Ability::get_effect() 
{
	return effect; 
}


void Ability::dec_cooldown()
{
	if (cooldown != 0)
		cooldown--;
}

bool Ability::ability_ready() const
{
	return cooldown == 0;
}

void Ability::refresh_cooldown() { cooldown = max_cooldown; }


int Ability::use_ability(Combatant& c, Combatant& opp)
{
	if (ability == Abilities::NONE)
		return INV; 
	if (c.get_mana() < mana_cost)
	{
		cout << "NOT ENOUGH MANA TO USE " << name << "!\n"; 
		return INV;
	}
	c.set_mana(c.get_mana() - mana_cost);
	int (*ab_func_ptr)(Combatant&, Combatant&) = ability_list[abilities_to_int(ability)];
	int result = ab_func_ptr(c, opp);
	int s_chance = random(1, 3); 
	if (result == 0 || s_chance != 2)
		effect.set_status_enabled(OFF);
	else
		effect.set_status_enabled(ON);
	return result;
}

