#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>
using std::cout; 
using std::string; 

#define NO_STOCK -2
#define NOT_OK -1
#define OK 0
enum class Items {HEALING_POTION = 0, ATK_POTION, DEF_POTION, MANA_POTION, EXPLOSION_POTION, ATK_DOWN_POTION, DEF_DOWN_POTION, MANA_DOWN_POTION, NONE};
enum class Item_Target{SELF = 0, OPPONENT, NO_TARGET};

inline constexpr const char* item_list[] =
{
	"HEALING ITEM",
	"ATTACK UP ITEM",
	"DEFENSE UP ITEM",
	"MANA UP ITEM",
	"EXPLOSION ITEM",
	"ATTACK DOWN ITEM",
	"DEFENSE DOWN ITEM",
	"MANA DOWN ITEM"
};

inline int items_to_int(Items i) { return static_cast<int>(i); }

class Combatant; 

class Item
{
private:
	Items item;
	Item_Target target;
	string name;
	int stock; 
	
public:
	Item(); 
	Item(Items i, Item_Target t, int q); 
	Items get_item() const; 
	Item_Target get_target() const;
	string get_name() const;
	int get_stock() const;
	void dec_stock();
	int use_item(Combatant& c); 
};

#endif // !ITEM_H

