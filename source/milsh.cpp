#include "milsh_types.h"
#include "milsh_string.h"

#include <windows.h>

#define MILSH_ERROR -1
#define MILSH_EXIT 0

int WINAPI WinMain(HINSTANCE in_instance, HINSTANCE in_prev_instance, PSTR in_cmd_line,
                   int in_cmd_show)
{
	MILSH_UNUSED(in_instance);
	MILSH_UNUSED(in_prev_instance);
	MILSH_UNUSED(in_cmd_line);
	MILSH_UNUSED(in_cmd_show);

	HANDLE std_out = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE std_in = GetStdHandle(STD_INPUT_HANDLE);
	if (!std_out || !std_in)
	{
		return MILSH_ERROR;
	}

	{
		constexpr const char* header = 
			"   *       (    (       )  \n"
			" (  `      )\\ ) )\\ ) ( /(  \n"
			" )\\))(  ( (()/((()/( )\\()) \n"
			"((_)()\\ )\\ /(_))/(_)|(_)\\  \n"
			"(_()((_|(_|_)) (_))  _((_) \n"
			"|  \\/  |(_) |  / __|| || | \n"
			"| |\\/| || | |__\\__ \\| __ | \n"
			"|_|  |_||_|____|___/|_||_| \n";
		DWORD header_length = static_cast<DWORD>(string::length(header));
		DWORD bytes_written;
		WriteConsoleA(std_out, header, header_length, &bytes_written, NULL);
	}

	do
	{
		constexpr const char* prompt = "\n> ";
		DWORD prompt_length = static_cast<DWORD>(string::length(prompt));
		DWORD bytes_written;
		WriteConsoleA(std_out, prompt, prompt_length, &bytes_written, NULL);

		constexpr unsigned int buffer_size = 32;
		char buffer[buffer_size] = { };
		DWORD bytes_read;
		if (ReadConsoleA(std_in, &buffer, buffer_size, &bytes_read, NULL))
		{
			string::remove_whitespace(buffer);
			if ((string::compare(buffer, "quit") == 0) || (string::compare(buffer, "exit") == 0))
			{
				break;
			}
		}
		else
		{
			return MILSH_ERROR;	
		}
	}
	while (true);

	return MILSH_EXIT;
}
