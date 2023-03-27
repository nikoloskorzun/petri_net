#ifndef petri_condition_file
#define petri_condition_file

#include <iostream>
#include <string>
#include <vector>
#include <time.h>

#include "position.h"
#include "transition.h"
#include "my_exceptions.h"

using namespace std;

class Condition
{
public:

	Condition& operator=(const Condition& other);

	Condition(const Condition& condition_copy);


	uint32_t perform();
	

	Condition();
	
	void set_pos_count(uint32_t count);
	
	void set_trans_count(uint32_t count);
	

	int check_connections();


	void print_table();
	


	void add_info_about_position(uint32_t pos_index, vector <pair<uint32_t, uint32_t>> connections);
	
	void add_info_about_transition(uint32_t trans_index, vector <pair<uint32_t, uint32_t>> connections);
	

	void add_info_about_labels(vector <uint32_t> labels);

	void debug();





	


	~Condition();

private:


	uint32_t get_random_uint32();

	int check(uint32_t index_trans);
	
	





	uint32_t position_count;
	uint32_t transition_count;
	vector<Position> positions;//positions[i] positions[i].index, i==index. not swaping in array! 
	vector<Transition> transitions;//transition[i] transition[i].index, i==index. not swaping in array! 

};

#endif
