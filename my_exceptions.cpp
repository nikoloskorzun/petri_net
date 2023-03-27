
#include <iostream>
#include <fstream>

#include <string>
#include <vector>
#include <exception>
#include "my_exceptions.h"


using namespace std;

	My_exception::My_exception()
	{
		this->code = ERRORS::unexpected_error;
		this->params = NULL;
	}
	My_exception::My_exception(ERRORS code, string comment, ostream* out_stream)
	{
		this->code = code;
		this->params = NULL;
		this->optionally_text = comment;
		this->stream_to_additional_information = out_stream;

	}

	My_exception::My_exception(uint32_t left, uint32_t right, ostream* out_stream)
	{
		this->code = ERRORS::too_big_option_in_menu;
		this->params = new uint32_t[2];
		this->params[0] = left;
		this->params[1] = right;
		this->stream_to_additional_information = out_stream;
		this->optionally_text = "Input option must be between ";
		this->optionally_text += to_string(this->params[0]) + " and " + to_string(this->params[1]) + "\n";
	}

	My_exception::~My_exception()
	{
		if (this->code == ERRORS::too_big_option_in_menu)
			delete[] this->params;
	}

	const char* My_exception::what() const throw()
	{
		switch (this->code)
		{
		case ERRORS::unexpected_error:
			return "Unexpected exception.\n";
			
		case ERRORS::input_file_not_exist:
			(*stream_to_additional_information) << "Unable to open <" << this->optionally_text << "> for reading\n";
			return "";		
		case ERRORS::unable_open_file_for_recording:
			(*stream_to_additional_information) << "Unable to open <" << this->optionally_text << "> for writing\n";
			return "";
		case ERRORS::too_big_option_in_menu:
			(*stream_to_additional_information) << this->optionally_text;
			return "";
		case ERRORS::not_a_uint32_number:
			return "Input param must be unsigned integer number less 2^32 - 1\n";
		case ERRORS::could_not_get_filepath_win:
			return "The program failed to get the current working directory in WIN mode\n";


		case ERRORS::string_in_input_file_incorrect:
			(*stream_to_additional_information) << this->optionally_text << "\n";
			return "";
		case ERRORS::ñannot_parse_file:
			(*stream_to_additional_information) << "Cannot parse file because of " << this->optionally_text << "\n";
			return "";
		case ERRORS::empty_petri_net:
			(*stream_to_additional_information) << "Petri net empty: " << this->optionally_text << "\n";
			return "";
		case ERRORS::impossible_to_perform_petri_net:
			return "There are no transitions that can be performed\n";

		default:
			return "No information about this code\n";
		}

	}

