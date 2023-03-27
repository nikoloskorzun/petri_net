#ifndef petri_transition_file
#define petri_transition_file
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Transition
{
public:

	void set_connections(vector <pair<uint32_t, uint32_t>> connections);

	vector <pair<uint32_t, uint32_t>> get_positions_indexes_and_count();
	Transition& operator=(const Transition& other);
	Transition(uint32_t index);
	Transition(const Transition& transition_copy);
	~Transition();

private:
	uint32_t index;

	vector <pair<uint32_t, uint32_t>> connections;//<index, type_count>
};

#endif