#ifndef petri_my_exceptions_file
#define petri_my_exceptions_file

#include <iostream>
#include <fstream>

#include <string>
#include <vector>
#include <exception>
using namespace std;

enum class ERRORS {
	unexpected_error = 0x7fffffff,
	input_file_not_exist = 0,
	too_big_option_in_menu,
	not_a_uint32_number,
	could_not_get_filepath_win,
	string_in_input_file_incorrect,
	ñannot_parse_file,
	empty_petri_net,
	impossible_to_perform_petri_net,
	unable_open_file_for_recording,


	

};

class My_exception : public exception
{
public:

	My_exception();
	My_exception(ERRORS code, string comment = "", ostream* out_stream = &cout);

	My_exception(uint32_t left, uint32_t right, ostream* out_stream = &cout);

	~My_exception();

	virtual const char* what() const throw();

private:
	ERRORS code;
	string optionally_text;
	uint32_t* params;
	ostream* stream_to_additional_information;
};
#endif
