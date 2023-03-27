#ifndef petri_position_file
#define petri_position_file



#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Position
{
public:
	
	Position& operator=(const Position& other);

	Position(uint32_t index);

	Position(const Position& position_copy);

	~Position();
	void add_label(uint32_t count);

	void sub_label(uint32_t count);


	uint32_t get_amount_label();


	void set_connections(vector <pair<uint32_t, uint32_t>> connections);


	vector <pair<uint32_t, uint32_t>> get_transitions_indexes_and_count();


private:
	uint32_t label_count;
	uint32_t index;

	vector <pair<uint32_t, uint32_t>> connections;//<indesx, type_count> type_count - first bit - show dirrection, 0-in, 1-out
};





#endif // !petri_position_file