#include <vector> 
#include "transition.h"
using namespace std;
	void Transition::set_connections(vector <pair<uint32_t, uint32_t>> connections)
	{
		for (uint32_t i = 0; i < connections.size(); i++)
			this->connections.push_back(connections[i]);
	}

	vector <pair<uint32_t, uint32_t>> Transition::get_positions_indexes_and_count()
	{
		return this->connections;
	}
	Transition& Transition::operator=(const Transition& other)
	{
		// Guard self assignment
		if (this == &other)
			return *this;

		this->index = other.index;
		this->connections = other.connections;
		return *this;
	}

	Transition::Transition(const Transition& transition_copy)
	{
		this->index = transition_copy.index;
		this->connections = transition_copy.connections;
	}

	Transition::Transition(uint32_t index)
	{
		this->index = index;
	}
	Transition::~Transition() {}

