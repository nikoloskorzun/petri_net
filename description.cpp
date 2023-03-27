#include "description.h"

Description::Description() {}
Description::~Description() {}
void Description::add_position_discription(string str)
{
	this->description_positions.push_back(str);
}
void Description::add_transition_discription(string str)
{
	this->description_transitions.push_back(str);
}

uint32_t Description::get_count_positions()
{
	return this->description_positions.size();
}
uint32_t Description::get_count_transitions()
{
	return this->description_transitions.size();
}

vector<string> Description::get_description_positions()
{
	return this->description_positions;
}
vector<string> Description::get_description_transitions()
{
	return this->description_transitions;
}



Description& Description::operator=(const Description& other)
{
	// Guard self assignment
	if (this == &other)
		return *this;

	this->description_positions = other.description_positions;
	this->description_transitions = other.description_transitions;
	
	return *this;
}


Description::Description(const Description& description_copy)
{
	this->description_positions = description_copy.description_positions;
	this->description_transitions = description_copy.description_transitions;
}