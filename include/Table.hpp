#ifndef TABLE_HPP
#define TABLE_HPP
#include <iostream>
#include <string>
#include <vector>

class Table{

public:

	// read from a file located at path
    void read(std::string path);

	// read from a stream object
	void read(std::istream & is);

	// write to a file located at path
    void write(std::string path) const;

	// write to a stream object
	void write(std::ostream & os) const;

	// returns true if file has no rows or no columns
	bool isEmpty() const;

	// returns the number of rows
    unsigned rows() const;

	// returns the number of columns
    unsigned columns() const;

	// returns the value at row r and column c
    std::string cell(unsigned r, unsigned c) const;

private:
    std::vector< std::vector<std::string> > table;

};
#endif
