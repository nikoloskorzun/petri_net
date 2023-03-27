#include <iostream>
#include "app.h"

using namespace std;



App::App() {}
App::~App() {}

void App::print_logo()
{
	ifstream file;
	file.open(LOGO_FILENAME, ios_base::in);
	if (!file.is_open())
		cout << "Petri net. execute and analyze.\n";
	else
	{
		string line;
		while (getline(file, line))
			cout << line << endl;
		file.close();
	}
	cout << endl;

}


void App::print_contributors()
{
	ifstream file;
	file.open(CONTRIBUTORS_FILENAME, ios_base::in);
	if (file.is_open())
	{
		string line;
		cout << "Contributors: ";
		while (getline(file, line))
			cout << line << ", ";
		cout << endl;
		file.close();
	}
}


void App::print_version()
{
	cout << "Version: " << VERSION << endl;
}



	int App::menu()
	{
		uint32_t smart_exit_flag; // == number_option, but if input error detect = 0xFFFFFFFF.
		uint32_t number_option = 0;

		cout << endl;
		cout << "\t[1] >> Input structure and labels from specially formatting text file\n";
		cout << "\t[2] >> Input structure and labels manually from console in M=(P, T, I, O, m) format\n";
		cout << "\t[3] >> Save structure and labels current petri net in specially formatting text file\n";
		cout << "\t[4] >> Print structure and labels current petri net in console in table format\n";
		cout << "\t[5] >> Execute petri net\n";
		cout << "\t[6] >> Analyze petri net\n";
	#ifdef DEBUG_FUNCTIONAL
		cout << "\t[7] >> Temporaly functional\n";
	#endif
		cout << "\t[0] >> Exit\n";

		cout << "Options: ";
		try
		{
			cin >> number_option;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(32767, '\n');
				throw My_exception(ERRORS::not_a_uint32_number);
			}
			else
				cin.ignore(32767, '\n');

		#ifdef DEBUG_FUNCTIONAL
			if (number_option > 7)
				throw My_exception(0, 7);
		#else
			if (number_option > 6)
				throw My_exception(0, 6);
		#endif


			smart_exit_flag = number_option;
		}
		catch (const std::exception& e)
		{
			smart_exit_flag = 0xFFFFFFFF;
			cout << CLEAR_CONSOLE_AND_MOVE_POINTER_TO_BEGIN_STRING;
			cout << e.what();
		}

		if (~smart_exit_flag)
			cout << CLEAR_CONSOLE_AND_MOVE_POINTER_TO_BEGIN_STRING;


		switch (number_option)
		{
		case 1:
			input_from_file_menu();
			break;
		case 2:
			cout << "Not available in this version\n";
			break;
		case 3:
			cout << "no\n"; break;
			save_in_file_menu();

			break;
		case 4:
			try
			{
				petri_net.print_table();
			}
			catch (const std::exception& e)
			{
				cout << e.what();
			}
			break;
		case 5:

			execute_petri_net_menu();

			break;
		case 6:
			cout << "Not available in this version\n";

			break;
#ifdef DEBUG_FUNCTIONAL
		case 7:
			petri_net.debug();
			break;
#endif

		default:
			break;
		}

		return smart_exit_flag;
	}



	void App::input_from_file_menu()
	{
		try
		{
			wstring ws = save_load_helper.get_current_filepath();
			cout << "Input full <filepath\\filename." << FILE_EXTENSION << "> or " << ws << "\\<filename." << FILE_EXTENSION << "> or <STD> for open " << STD_FILENAME_INPUT << "." << FILE_EXTENSION << "\n";
		}
		catch (const std::exception& e)
		{
			cout << e.what();
			cout << "Input full <filepath\\filename." << FILE_EXTENSION << ">\n";
		}


		try
		{
			cout << "\n>>>";
			string filename;

			getline(cin, filename);

			state = (filename != "STD" ? save_load_helper.read_from_file(filename) : save_load_helper.read_from_file());

			petri_net = state.first;
		}
		catch (const std::exception& e)
		{
			cout << e.what();

		}




	}
	void App::save_in_file_menu()
	{

		state.first = petri_net;
		try
		{
			wstring ws = save_load_helper.get_current_filepath();
			cout << "Input full <filepath\\filename." << FILE_EXTENSION << "> or " << ws << "\\<filename." << FILE_EXTENSION << "> or <STD> for save in " << STD_FILENAME_OUTPUT << "." << FILE_EXTENSION << "\n";
		}
		catch (const std::exception& e)
		{
			cout << e.what();
			cout << "Input full <filepath\\filename." << FILE_EXTENSION << ">\n";
		}
		cout << "\n>>>";
		string filename;

		getline(cin, filename);

		try
		{
			(filename != "STD" ? save_load_helper.save_in_file(state, filename) : save_load_helper.save_in_file(state));
		}
		catch (const std::exception& e)
		{
			cout << e.what();

		}




	}

void App::execute_petri_net_menu()
{
	cout << "Enter the number of executions (zero for \"infinity\" count): ";
	uint32_t count = 0;

	try
	{
		cin >> count;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(32767, '\n');
			throw My_exception(ERRORS::not_a_uint32_number);
		}
		else
			cin.ignore(32767, '\n');


	}
	catch (const std::exception& e)
	{
		cout << CLEAR_CONSOLE_AND_MOVE_POINTER_TO_BEGIN_STRING;
		cout << e.what();
	}

	vector<uint32_t> trans;


	if (!count)
	{
		cout << "Not available\n";
	}
	else
	{
		try
		{
			for (uint32_t i = 0; i < count; i++)
				trans.push_back(petri_net.perform());
		}
		catch (const std::exception& e)
		{
			cout << e.what();
		}
		cout << "Count of executions: " << trans.size() << "\n";
		cout << "Sequence of transitions: ";

		for (uint32_t i = 0; i < trans.size(); i++)
			cout << trans[i] << ", ";
		cout << endl;

	}


}






