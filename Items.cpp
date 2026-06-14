#include "Items.h"
#include "Combatant.h"

float healing_potion(Combatant& c)
{
	float potency = c.get_health() / 4; 
	c.set_health(c.get_health() + potency); 
	return potency;
}

float attack_up(Combatant& c)
{
	float potency = c.get_attack() / 4; 
	c.set_attack(c.get_attack() + potency); 
	return potency;
}

float defense_up(Combatant& c)
{
	float potency = c.get_defense() / 4; 
	c.set_defense(c.get_defense() + potency);
	return potency;
}

float mana_up(Combatant& c)
{
	float potency = c.get_mana() / 4; 
	c.set_mana(c.get_mana() + potency);
	return potency;
}

float explosion(Combatant& c)
{
	float potency = c.get_health() / 3; 
	c.set_health(c.get_health() - potency);
	return potency;
}

float attack_down(Combatant& opp)
{
	float reduction = opp.get_attack() / 4; 
	opp.set_attack(opp.get_attack() - reduction);
	return reduction;
}

float defense_down(Combatant& opp)
{
	float reduction = opp.get_defense() / 4; 
	opp.set_defense(opp.get_defense() - reduction);
	return reduction;
}


float mana_down(Combatant& opp)
{
	float reduction = opp.get_mana() / 4;
	opp.set_mana(opp.get_mana() - reduction);
	return reduction;
}


float(*item_func_list[8])(Combatant& c) = { healing_potion, attack_up, defense_up, mana_up, explosion, attack_down, defense_down, mana_down};

Item::Item()
{
	item = Items::NONE; 
	target = Item_Target::NO_TARGET;
	name = item_list[items_to_int(item)]; 
	stock = 0;
}

Item::Item(Items i, Item_Target t, int s)
	:item{ i }, target{t}, stock{ s }
{
	name = item_list[items_to_int(item)];
}

Items Item::get_item() const { return item; }

Item_Target Item::get_target() const { return target; }

string Item::get_name() const { return name;  }

int Item::get_stock() const { return stock;  }

void Item::dec_stock()
{
	if (stock != 0)
		stock--;
}

int Item::use_item(Combatant& c)
{
	if (stock == 0)
		return NO_STOCK; // just in case...I guess

	float (*item_func_ptr)(Combatant&) = item_func_list[items_to_int(item)]; 
	return item_func_ptr(c);
}
