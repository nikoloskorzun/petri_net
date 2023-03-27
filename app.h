
#ifndef petri_app_file
#define petri_app_file

#include <iostream>

#include "IO.h"

#include "my_exceptions.h"

#include "condition.h"
#include "description.h"



using namespace std;

inline ostream& operator<<(ostream& os, wstring l)
{
	for (uint32_t i = 0; (i < l.length()) && (l[i] != 0); i++)
	{
		if (l[i] <= 0x007F)
			os << (char)l[i];
		else
			os << "\\\\" << l[i] << "\\\\";

	}
	return os;
}


class App
{
private:

public:
	App();
	~App();

	void print_logo();


	void print_contributors();
	void print_version();



	int menu();
	
private:
	pair<Condition, Description> state;
	Condition petri_net;
	IO save_load_helper;
	void input_from_file_menu();
	
	void save_in_file_menu();
	

	void execute_petri_net_menu();
	

};

#endif