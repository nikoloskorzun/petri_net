
#include <iostream>
#include <string>
#include <vector>

#include "position.h"

using namespace std;

	Position& Position::operator=(const Position& other)
	{
		// Guard self assignment
		if (this == &other)
			return *this;

		this->label_count = other.label_count;
		this->index = other.index;
		this->connections = other.connections;
		return *this;
	}


	Position::Position(uint32_t index)
	{
		this->label_count = 0;
		this->index = index;
	}

	Position::Position(const Position& position_copy)
	{
		this->label_count = position_copy.label_count;
		this->index = position_copy.index;
		this->connections = position_copy.connections;
	}

	Position::~Position() {}
	void Position::add_label(uint32_t count)
	{



		this->label_count += count;


	}
	void Position::sub_label(uint32_t count)
	{
		this->label_count -= count;
	}

	uint32_t Position::get_amount_label()
	{
		return this->label_count;
	}

	void Position::set_connections(vector <pair<uint32_t, uint32_t>> connections)
	{
		for (uint32_t i = 0; i < connections.size(); i++)
			this->connections.push_back(connections[i]);
	}

	vector <pair<uint32_t, uint32_t>> Position::get_transitions_indexes_and_count()
	{
		return this->connections;
	}
