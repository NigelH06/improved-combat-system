
#ifndef STATUS_EFFECTS_H
#define STATUS_EFFECTS_H

#include <string>
using std::string;

#define NO_EFFECT -123
#define EFFECT_OK 678
#define NOT_RDY -1
#define SHOCK_TICK 1
#define BURN_TICK 3
#define FREEZE_TICK 2
#define CORRUPT_TICK 4
#define POISON_TICK 5
#define ON true
#define OFF false



/* 6/11/2026 - Refactoring Status_Effect to just apply ticks when chance matches, cooldowns and turns will be
			   handled by Ability and Combatant classes 
*/


class Combatant;

// This class needs to handle when it's own status effects are active or not-> inc/dec cooldowns/reset cooldowns when needed
enum class Effects {SHOCK = 0, BURN, FREEZE, CORRUPT, POISON, NONE };

inline constexpr const char* effects_list[] =
{
    "SHOCK", "BURN", "FREEZE",
	"CORRUPT", "POISON", "NONE"
};


inline int effect_to_int(Effects e)
{
	return static_cast<int>(e);
}

extern int (*status_list[5])(Combatant& c, Combatant& opp);

class Status_Effect
{
private:
	Effects e;
	string name;
	int tick;
	bool enabled; 
public:
	Status_Effect();
	Status_Effect(Effects ef, int tck);
	Effects get_effect() const; 
	string get_name() const;  
	void set_status_enabled(bool state);
	bool get_status_state() const;
	int use_effect(Combatant& c, Combatant& opp);
	void apply_tick_dmg(Combatant& c, Combatant& opp); 
};

#endif
