
#ifndef COMBATANT_H
#define COMBATANT_H

#include "Status_Effects.h"
#include "Ability.h"
#include "Items.h"

#define STARTER_HEALTH 1500
#define STARTER_ATK 500
#define STARTER_DEF 200
#define STARTER_MANA 150
#define OK 0 
#define NO_VAL -111
#define HEALTH_BOOST 25
#define ATTACK_BOOST 15 
#define DEFENSE_BOOST 12
#define MANA_BOOST 10
#define THRESH_UPDATE 100 

class Ability; 

// Level Up Implementation
struct Progression
{
	int level = 0, xp = 0, xp_to_next = 50;

	// Another way to define default constructor if values already initialized
	Progression() = default; 

	Progression(int lvl, int new_xp, int new_next_xp)
		: level{ lvl }, xp{ new_xp }, xp_to_next{ new_next_xp }
	{
	}
};

class Combatant
{
private:
	string name;
	int health, attack, defense, mana;
	Ability ab;
	Item item;
	Progression prog; 
	void level_up();
public:
	Combatant();
	Combatant(string n, Ability new_ab); 
	Combatant(string n, Ability new_ab, Item i, int hp, int atp, int def, int mp); 
	Combatant(string n, Ability new_ab, Item i, Progression p, int hp, int atp, int def, int mp);
	bool is_alive() const;
	string get_name() const;
	void display_stats();
	int basic_attack(Combatant& opp);
	Ability& get_ability();
	Item& get_item(); 
	int get_mana() const; 
	void set_mana(int mp); 
	int get_defense() const;
	void set_defense(int def);
	int get_attack() const;
	void set_attack(int atp);
	int get_health() const;
	void set_health(int hp);
	int get_xp() const;  
	void progress(Combatant& opp);
};

#endif
