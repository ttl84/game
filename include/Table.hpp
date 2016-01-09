#ifndef TABLE_HPP
#define TABLE_HPP
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Table{

public:

	// read from a stream object
	void read(std::istream & is);

	// write to a stream object
	void write(std::ostream & os) const;

	// returns true if file has no rows or no columns
	bool isEmpty() const;

	// returns the number of rows
    unsigned rows() const;

	// returns the number of columns
    unsigned columns() const;

	// returns reference to value at row r and column c
    std::string & cell(unsigned r, unsigned c);


	// The requested cell location is out of bounds
	class OutOfBounds {
	public:
		unsigned row;
		unsigned column;
	
		OutOfBounds(unsigned r, unsigned c);
	};

	// The table has unequal row lengths
	class UnevenRow {
	public:
		UnevenRow(unsigned row, unsigned expected, unsigned got);
		unsigned row;
		unsigned expectedColumns;
		unsigned gotColumns;
	};

private:
    std::vector< std::vector<std::string> > table;

};

// helpers
template<class T>
bool readFormat(Table & t, unsigned row, unsigned col, T & val)
{
	std::istringstream iss(t.cell(row, col));
	iss >> val;
	return iss;
}

template<class T>
bool writeFormat(Table & t, unsigned row, unsigned col, const T& val)
{
	std::ostringstream oss;
	if(oss << val) {
		t.cell(row, col) = oss.str();
	} else {
		return false;
	}
}

#endif
