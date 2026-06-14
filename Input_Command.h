#ifndef INPUT_COMMAND_H
#define INPUT_COMMAND_H

#include <iostream>
#include <string>
#include <vector>
#include <random>
using std::cin;
using std::cout; 
using std::string;

static std::mt19937 gen(std::random_device{}());

inline int random_num(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(gen);
}

enum class Command {BASIC = 1, ABILITY, ITEM, INVALID};
inline constexpr const char* commands[] = { "BASIC", "ABILITY", "ITEM"};
inline constexpr const char* INVALID = "INVALID";
inline int cmd_to_int(Command c) { return static_cast<int>(c); }

class Input_Command {
private:
	Command cmd; 

public:
	Input_Command(); 
	Command get_cmd(); 
	Command get_random_cmd(); 
};
#endif 
