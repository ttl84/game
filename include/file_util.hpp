#ifndef FILE_UTIL_HPP
#define FILE_UTIL_HPP
#include <string>

// Tries to read file and store contents in dst.
// Returns bool indicating success.
bool stringFromFile(std::string & dst, char const * fileName);

#endif
