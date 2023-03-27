#include <iostream>
#include <string>
#include <vector>
#include "definitions.h"

#include "my_exceptions.h"

#include "condition.h"

uint32_t Condition::perform()
{
	vector<uint32_t> indexes;
	for (uint32_t i = 0; i < this->transition_count; i++)
	{
		if (check(i))
			indexes.push_back(i);
	}
	if (indexes.empty())
		throw My_exception(ERRORS::impossible_to_perform_petri_net);

#ifdef DEBUG_FUNCTIONAL			
	cout << "Indexes of possible transitions: ";

	for (uint32_t i = 0; i < indexes.size(); i++)
	{
		cout << indexes[i] << ", ";
	}
	cout << endl;
#endif 


	uint32_t choice = indexes[get_random_uint32() % indexes.size()];
	


	vector<pair<uint32_t, uint32_t>>connections = this->transitions[choice].get_positions_indexes_and_count();


	for (uint32_t i = 0; i < connections.size(); i++)
	{
		if (connections[i].second & 0x80000000)
		{
			this->positions[connections[i].first].sub_label(connections[i].second & 0x7fffffff);
		}
		else
		{
			this->positions[connections[i].first].add_label(connections[i].second & 0x7fffffff);
		}

	}

	return choice;

		

}

Condition::Condition()
{
#ifdef DEBUG_FUNCTIONAL
	srand(5);
#else
	srand(time(NULL));
#endif


	this->position_count = 0;
	this->transition_count = 0;
}

void Condition::set_pos_count(uint32_t count)
{
	for (uint32_t i = 0; i < count; i++)
	{
		this->positions.push_back(Position(i));
	}

	this->position_count = count;
}


void Condition::set_trans_count(uint32_t count)
{
	for (uint32_t i = 0; i < count; i++)
	{
		this->transitions.push_back(Transition(i));
	}
	this->transition_count = count;
}



int Condition::check_connections()
{


	return 1;
}

void Condition::print_table()
{
	if (!(this->transition_count && this->position_count))
		throw My_exception(ERRORS::empty_petri_net, "impossible to display the table");

	vector<pair<uint32_t, uint32_t>> s;


	for (uint32_t j = 0; j < transition_count; j++)
		cout << "\t" << j;
	cout << endl;
	int flag = 0;
	for (uint32_t i = 0; i < position_count; i++)
	{
		cout << i << ":" << positions[i].get_amount_label() << "\t";
		s = positions[i].get_transitions_indexes_and_count();



		for (uint32_t j = 0; j < transition_count; j++)
		{
			flag = 1;
			for (uint32_t iter = 0; iter < s.size(); iter++)
			{
				//cout << "[" << (s[iter].second && 0x7fffffff) << "]" << endl;
				if (s[iter].first == j)
				{
					flag = 0;
					if (s[iter].second >= 0x80000000)
						cout << "<";
					else
						cout << ">";

					cout << (s[iter].second & 0x7fffffff) << " ";
				}
			}
			if (flag)
				cout << "()";
			cout << "\t";
				//cout << positions[i].get_positions_indexes_and_count();
		}

		cout << "\n";

	}

}


void Condition::add_info_about_position(uint32_t pos_index, vector <pair<uint32_t, uint32_t>> connections)
{
	this->positions[pos_index].set_connections(connections);
}
void Condition::add_info_about_transition(uint32_t trans_index, vector <pair<uint32_t, uint32_t>> connections)
{
	this->transitions[trans_index].set_connections(connections);
}

void Condition::add_info_about_labels(vector <uint32_t> labels)
{
	for (uint32_t i = 0; i < labels.size(); i++)
	{
		this->positions[i].add_label(labels[i]);
	}

}

void Condition::debug()
{


	cout << check(0) << endl;
	cout << check(1) << endl;
	cout << check(2) << endl;
	perform();

		//printf("%#x\n", get_random_uint32());
		/*


		*/
}



Condition& Condition::operator=(const Condition& other)
{
	if (this == &other)
		return *this;

	this->position_count = other.position_count;
	this->transition_count = other.transition_count;
	this->positions = other.positions;
	this->transitions = other.transitions;

	return *this;
}
Condition::Condition(const Condition& condition_copy)
{

	this->position_count = condition_copy.position_count;
	this->transition_count = condition_copy.transition_count;
	this->positions = condition_copy.positions;
	this->transitions = condition_copy.transitions;


}




Condition::~Condition()
{
}




uint32_t Condition::get_random_uint32()
{
	return (uint32_t)((rand() << 17) | ((rand() % 4) << 15) | rand());
}

int Condition::check(uint32_t index_trans)
{
	vector <pair<uint32_t, uint32_t>> connections = this->transitions[index_trans].get_positions_indexes_and_count();

	for (uint32_t i = 0; i < connections.size(); i++)
	{
		if ((connections[i].second) & 0x80000000)
		{
			if (this->positions[connections[i].first].get_amount_label() < ((connections[i].second) & 0x7fffffff))
				return 0;

		}
	}
	return 1;

	

		vector <pair<uint32_t, uint32_t>>::iterator iter = connections.begin();

		while (iter < connections.begin())
		{
			if ((iter->second & 0x80000000) && (this->positions[iter->first].get_amount_label() < (iter->second)))
				return 0;
			iter++;
		}
		return 1;
}

