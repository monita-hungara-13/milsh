#pragma once

#include "milsh_types.h"

namespace string
{

constexpr type::size length(const char* in_string)
{
	const char* p = in_string;
	for (; *p++;);
	return p - in_string;
}

constexpr type::size compare(const char* in_left, const char* in_right)
{
	while (*in_left && *in_right && *in_left == *in_right)
	{
		++in_left;
		++in_right;
	}

	return *in_left - *in_right;
}

constexpr void remove_whitespace(char* in_out_string)
{
	char* current = in_out_string;
	while (*in_out_string)
	{
		switch (*current)
		{
		case 9:   // TAB
		case 10:  // LF (line feed)
		case 11:  // VT (vertical tab)
		case 12:  // FF (form feed)
		case 13:  // CR (carriage return)
		case 32:  // Space
		case 133: // Elipsis (Windows)
		case 160: // Non-breaking space (ISO & Windows)
			break;
		default:
			*in_out_string++ = *current;
			break;
		};
		++current;
	}
}

} // namespace string
