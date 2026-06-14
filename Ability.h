
#ifndef ABILITY_H
#define ABILITY_H

#include <string>
#include <iostream>
#include <random>
#include "Status_Effects.h"
#define BASE_PERCENT 0.2
#define K 25
#define INV_CDWN 9999
#define INV -11111
#define NOT_RDY -1
using std::string;
using std::cout; 




class Combatant;


enum class Abilities {FIREBALL = 0, HEAL, DRAIN, STRIKE, EMPOWER, FORTIFY, INSIGHT, HEAT_UP, NONE};
inline constexpr const char* abilities[] = { "FIREBALL", "HEAL", "DRAIN", "STRIKE", "EMPOWER", "FORTIFY", "INSIGHT", "HEAT UP", "NONE"};
inline int abilities_to_int(Abilities ab) { return static_cast<int>(ab); }





class Ability
{
private:
	string name;
	Abilities ability; 
	Status_Effect effect; 
	int mana_cost, max_cooldown, cooldown;
public:
	Ability(); 
	Ability(Abilities ability, Status_Effect ef, int mc, int mcd);
	string get_ability_name() const;
	Status_Effect& get_effect(); 
	int get_mana_cost() const;
	int get_cooldown() const; 
	bool ability_ready() const; 
	void dec_cooldown();
	void refresh_cooldown(); 
	int use_ability(Combatant& c, Combatant& opp);
};


#endif
