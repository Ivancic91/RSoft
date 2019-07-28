#include <iostream>
#include <string>
#include "DumpIO.hpp"

/*
 * Finds the next element in a space separated list starting from
 * position start.
 *
 * User Inputs:
 * const std::string& line  A space separated list in string form
 * int start                An integer denoting where to start search
 *                          for the next element in the list
 * std::string& elem        The next element in the string array
 *
 * Guaranteed Outputs:
 * int RETURN               Integer denoting where to start search for
 *                          next element in string array. If there is
 *                          no next element -1 is returned
 * const std::string& line  NO CHANGE
 * std::string& elem        If there is a next element, returns next
 *                          element. Else return ""
 */
int DumpIO::NextElem(const std::string& line, int start, std::string& elem){

	int end = line.find(" ", start);

	// Ensures that multiple white spaces don't
	// cause problems
	while (end-start == 0)
	{
		start++;
		end = line.find(" ", start);
	}

	// If not at end of string then get substring
	// between end and start
	if (end != std::string::npos)
	{
		end += 1;
		elem = line.substr(start,end-start);
	}
	else
	{

		// If ended on a space, elem="";
		// else get substring from start to end of
		// line
		if(start != line.length())
		{
			elem = line.substr(start);
		}
		else
		{
			elem="";
		}
	}

	char last_ch = *elem.rbegin();
	if(last_ch==' ')
	{
		elem = elem.substr(0, elem.size()-1);
	}

	return end;
}
