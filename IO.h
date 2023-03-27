#ifndef petri_io_file
#define petri_io_file
#include <iostream>
#include <fstream>
#include <vector>

#include "definitions.h"

#ifdef WINDOWS_MODE
#include <windows.h>
#endif 


#include "condition.h"
#include "description.h"


using namespace std;
class IO
{
public:



	//void save_in_file(Condition cond, string filename = STD_FILENAME_OUTPUT "." FILE_EXTENSION);
	void save_in_file(pair<Condition, Description> data, string filename = STD_FILENAME_OUTPUT "." FILE_EXTENSION);

	pair<Condition, Description> read_from_file(string filename = STD_FILENAME_INPUT "." FILE_EXTENSION);
	


	IO();
	~IO();

	wstring get_current_filepath();
	

	


private:


	vector<uint32_t> get_labels_array(string s);
	

	template <typename T>
	T check_n_bit(T number, uint32_t pos_bit);


	template <typename T>
	void set_n_bit(T* number, uint32_t pos_bit);




	const static uint32_t len_buffer = 600;

	wchar_t wchar_buffer[len_buffer];
	char char_buffer[len_buffer];

	pair<uint32_t, vector<pair<uint32_t, uint32_t>>> parse_line_as_func_entry(string line, uint16_t flag);
	


};
#endif


