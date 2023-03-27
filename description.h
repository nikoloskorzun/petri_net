#ifndef petri_description_file
#define petri_description_file



#include <iostream>
#include <vector>

using namespace std;
class Description
{
public:
	Description();

	Description& operator=(const Description& other);

	Description(const Description& description_copy);

	~Description();
	void add_position_discription(string str);
	void add_transition_discription(string str);
	uint32_t get_count_positions();
	uint32_t get_count_transitions();
	vector<string> get_description_positions();
	vector<string> get_description_transitions();
private:
	vector<string> description_positions;
	vector<string> description_transitions;

};
#endif