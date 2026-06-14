#include "Combatant.h"
#include <random>

static std::mt19937 gen(std::random_device{}());

int random_c(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(gen);
}


Combatant::Combatant()
{
	ab = Ability{};
	name = "None";
	health = 0, attack = 0, defense = 0, mana = 0;
	item = Item{}; 
	prog = Progression{}; 
}

Combatant::Combatant(string n, Ability new_ab)
	: name{ n }, health{ STARTER_HEALTH }, attack{ STARTER_ATK }, defense{ STARTER_DEF }, mana{ STARTER_MANA }, ab{ new_ab }, item{ Item{} }
{
	prog = Progression{};
}

Combatant::Combatant(string n, Ability new_ab, Item i, int hp, int atp, int def, int mp)
	: name{ n }, ab{ new_ab }, item{i}, health {hp}, attack{ atp }, defense{ def }, mana{ mp }
{
	prog = Progression{};
}

Combatant::Combatant(string n, Ability new_ab, Item i, Progression p, int hp, int atp, int def, int mp)
	: name{ n }, ab{ new_ab }, item{ i }, prog{p}, health {hp}, attack{ atp }, defense{ def }, mana{ mp }
{
}


bool Combatant::is_alive() const{return health > 0; }

string Combatant::get_name() const { return name;  }


Ability& Combatant::get_ability() { return ab; }

Item& Combatant::get_item() 
{
	return item;
}

int Combatant::get_mana() const { return mana; }
void Combatant::set_mana(int mp) {
	if (mp < 0)
		mana = 0;
	else
	    mana = mp; 
}


int Combatant::get_defense() const { return defense; }
void Combatant::set_defense(int def) {
	if (def < 0)
		defense = 0;
	else 
	    defense = def;  
}
int Combatant::get_attack() const { return attack; }
void Combatant::set_attack(int atp) { 

	if (atp < 0)
		attack = 0;
	else 
		attack = atp; 
}

int Combatant::get_health() const { return health; }

void Combatant::set_health(int hp) { 
	if (hp < 0)
		health = 0;
	else
		health = hp; 
}

int Combatant::basic_attack(Combatant& opp)
{
	int dmg_calc = random_c(0, attack) - opp.get_defense(); 
	if (dmg_calc > 0)
	{
		opp.set_health(opp.get_health() - dmg_calc);
		return dmg_calc;
	}
	else
		return NO_VAL;
}



void Combatant::display_stats()
{
	cout << "\n========== " << name << "'S STATS " << " ==========\n";
	cout << "LEVEL " << prog.level << '\n' << "CURRENT XP " << prog.xp << '\n'; 
	cout << "XP TO NEXT LEVEL " << prog.xp_to_next << '\n';
	cout << "HEALTH " << health << '\n'; 
	cout << "ATTACK " << attack << '\n'; 
	cout << "DEFENSE " << defense << '\n'; 
	cout << "MANA " << mana << '\n'; 
	cout << "ABILITY " << ab.get_ability_name() << '\n'; 
	cout << "ABILITY COST " << ab.get_mana_cost() << '\n'; 
	cout << "ABILITY COOLDOWN " << ab.get_cooldown() << '\n'; 
	cout << "ITEM " << item.get_name() << " [Stock]: " << item.get_stock() << '\n';
	cout << "=====================================================\n";
}

void Combatant::level_up()
{
	int threshold = prog.xp_to_next;
	prog.level++; 
	prog.xp -= threshold; 
	prog.xp_to_next += THRESH_UPDATE; 

	health += HEALTH_BOOST;
	attack += ATTACK_BOOST; 
	defense += DEFENSE_BOOST; 
	mana += MANA_BOOST; 

	cout << name << " LEVELED UP TO " << prog.level << '\n';
	cout << "HEALTH + " << HEALTH_BOOST << '\n'; 
	cout << "ATTACK + " << ATTACK_BOOST << '\n'; 
	cout << "DEFENSE + " << DEFENSE_BOOST << '\n'; 
	cout << "MANA + " << MANA_BOOST << '\n';
}

int Combatant::get_xp() const
{
	return prog.xp;
}

void Combatant::progress(Combatant& opp)
{
	int xp_gain = opp.get_xp();
	this->prog.xp += xp_gain; 
	while (this->prog.xp >= this->prog.xp_to_next)
		level_up();
}