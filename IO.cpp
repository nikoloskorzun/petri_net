#include "IO.h"

using namespace std;
//
//void IO::save_in_file(Condition cond, string filename)
//{
//}
void IO::save_in_file(pair<Condition, Description> data, string filename)
{
	Condition cond = data.first;
	Description desc = data.second;


	ifstream file;
	file.open(filename, ios_base::out);
	if (!file.is_open())
		throw My_exception(ERRORS::unable_open_file_for_recording, filename);
	

	


	file.close();

}


pair<Condition, Description> IO::read_from_file(string filename)
{
	Condition cond;
	Description desc;

	uint32_t num_buff1 = 1;
	size_t num_buff2 = 0;


	//cout << filename << endl;

	ifstream file;
	file.open(filename, ios_base::in);
	if (!file.is_open())
		throw My_exception(ERRORS::input_file_not_exist, filename);

	if (file.is_open())
	{
		string line;

		try
		{
			getline(file, line);
			num_buff1 = stoul(line, &num_buff2);
		}
		catch (const std::exception& e)
		{
				throw My_exception(ERRORS::string_in_input_file_incorrect, "The first line in the file must start with a number describing the number of positions.");
		}

		if (line[num_buff2] != '.' && line[num_buff2] != ':')
			throw My_exception(ERRORS::string_in_input_file_incorrect, "After number must be \":\" for description name the positions or \".\" if not");

		cond.set_pos_count(num_buff1);

		uint32_t counter = 0;
		if (line[num_buff2] == '.')
			counter = num_buff1;
		while ((counter < num_buff1) && (getline(file, line)))
		{
			desc.add_position_discription(line);
			counter++;
		}

		if (counter != num_buff1)
			throw My_exception(ERRORS::ñannot_parse_file, "missing lines");


		try
		{
			getline(file, line);
			num_buff1 = stoul(line, &num_buff2);
		}
		catch (const std::exception&)
		{
			throw My_exception(ERRORS::string_in_input_file_incorrect, "In the line to describe the number of transition a number not found");
		}

		if (line[num_buff2] != '.' && line[num_buff2] != ':')
			throw My_exception(ERRORS::string_in_input_file_incorrect, "In the line to describe the number of transition after number must be \":\" for description name the positions or \".\" if not");

		cond.set_trans_count(num_buff1);

		counter = 0;
		while ((counter < num_buff1) && (getline(file, line)))
		{
			desc.add_transition_discription(line);


			counter++;
		}

		if (counter != num_buff1)
			throw My_exception(ERRORS::ñannot_parse_file, "missing lines");
		pair<uint32_t, vector<pair<uint32_t, uint32_t>>> func_string_res;
		uint16_t flag = 0;
		while (getline(file, line))
		{
			if (line.find("I_p:") != string::npos)
			{
				flag &= 0b0000000000011111;
				flag |= 0b1000000000000001;

				continue;
			}
			if (line.find("I_t:") != string::npos)
			{
				flag &= 0b0000000000011111;
				flag |= 0b0100000000000010;
				continue;
			}
			if (line.find("O_p:") != string::npos)
			{
				flag &= 0b0000000000011111;
				flag |= 0b0010000000000100;
				continue;
			}
			if (line.find("O_t:") != string::npos)
			{
				flag &= 0b0000000000011111;
				flag |= 0b0001000000001000;
				continue;
			}
			if (line.find("M=") != string::npos)
			{

				flag &= 0b0000000000011111;
				flag |= 0b0000100000010000;

				vector<uint32_t> labels_array = get_labels_array(line);

				cond.add_info_about_labels(labels_array);
				continue;
			}

				//cout << flag << "\n";
			func_string_res = parse_line_as_func_entry(line, flag);

				//cout << func_string_res.first << " " << func_string_res.second[0].first<< func_string_res.second[0].second<< endl;
			if (check_n_bit(flag, 15))
			{
				cond.add_info_about_position(func_string_res.first, func_string_res.second);
				continue;
			}
			if (check_n_bit(flag, 14))
			{
				cond.add_info_about_transition(func_string_res.first, func_string_res.second);
				continue;
			}
			if (check_n_bit(flag, 13))
			{
				cond.add_info_about_position(func_string_res.first, func_string_res.second);
				continue;
				}
			if (check_n_bit(flag, 12))
			{
				cond.add_info_about_transition(func_string_res.first, func_string_res.second);
				continue;
			}


		}
		flag &= 0b0000000000011111;
		flag = ~flag;
		if (flag != 0b1111111111100000)
			throw My_exception(ERRORS::ñannot_parse_file, string("missing lines: ") + (check_n_bit(flag, 0) ? "I(p) function" : "") + (check_n_bit(flag, 1) ? ", I(t) function" : "") + (check_n_bit(flag, 2) ? ", O(p) function" : "") + (check_n_bit(flag, 3) ? ", O(t) function" : "") + (check_n_bit(flag, 4) ? ", M - marking status" : "") + " are not described");

	}
	return pair<Condition, Description>(cond, desc);
}


IO::IO() {}
IO::~IO() {}

wstring IO::get_current_filepath()
{
#ifdef WINDOWS_MODE
	if (GetCurrentDirectory(len_buffer, wchar_buffer))
	{
		return wstring(wchar_buffer);
	}
	else
		throw My_exception(ERRORS::could_not_get_filepath_win);
#endif


#ifdef UNIX_MODE
	//#TODO realize this func in unix mode.
	return wstring(L"kill me please");
#endif

}







vector<uint32_t> IO::get_labels_array(string s)
{
	string buf = "";
	uint32_t b;
	vector<uint32_t> res;
	for (uint32_t i = 2; i < s.length(); i++)
	{
		if (s[i] == ',')
		{

			try
			{
				b = stoul(buf);

			}
			catch (const std::exception& e)
			{
				throw My_exception(ERRORS::ñannot_parse_file, "the description line of the label array is incorrect");
			}
			buf = "";

			if (s[i] == ',')
			{
				res.push_back(b);
			}
		}
		else
			buf += (s[i]);

	}
	return res;

}

template <typename T>
T IO::check_n_bit(T number, uint32_t pos_bit)
{
	return ((1 << pos_bit) & number);
}

template <typename T>
void IO::set_n_bit(T* number, uint32_t pos_bit)
{
	*number = ((1 << pos_bit) | (*number));
}



pair<uint32_t, vector<pair<uint32_t, uint32_t>>> IO::parse_line_as_func_entry(string line, uint16_t flag)
{

	uint32_t index_arg;
	uint32_t pos;
	vector<pair<uint32_t, uint32_t>> connections;//<index, count>



	try
	{
		index_arg = stoul(line, &pos);

	}
	catch (const std::exception& e)
	{
		throw My_exception(ERRORS::ñannot_parse_file, "the description line of the function record is incorrect");
	}
	pair<uint32_t, vector<pair<uint32_t, uint32_t>>> a;
	a.first = index_arg;
	uint32_t iter = pos + 1;
	string buf = "";
	uint32_t b;
	while (iter < line.length())
	{

			//cout << "(" << line[iter] << ")";
		if ((line[iter] == '*') || (line[iter] == ','))
		{


			try
			{
				index_arg = stoul(buf);

			}
			catch (const std::exception& e)
			{
				throw My_exception(ERRORS::ñannot_parse_file, "the description line of the function record is incorrect");
			}
			buf = "";

			if (line[iter] == '*')
				b = index_arg;
			if ((line[iter] == ','))
			{
				if (check_n_bit(flag, 14) || check_n_bit(flag, 15))
					set_n_bit(&index_arg, 31);
				connections.push_back(pair<uint32_t, uint32_t>(b, index_arg));
			}
		}
		else
			buf += (line[iter]);


		iter++;

	}


	a.second = connections;
	return a;

}

