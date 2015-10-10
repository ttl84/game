#include "file_util.hpp"
#include <iterator>
#include <fstream>
bool stringFromFile(std::string & dst, char const * fileName)
{
	std::ifstream fs(fileName);
	if(fs.is_open()) {
		std::istreambuf_iterator<char> begin(fs), end;
		dst = std::string(begin, end);
		return true;
	} else {
		return false;
	}
}
