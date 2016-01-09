#include "Table.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

void Table::read(istream & inFile)
{
	string line;
	while(getline(inFile, line, '\n')){
		vector<string> row_vector;
		istringstream ss(line);
		string word;
		while(getline(ss, word, '|')){
			row_vector.push_back(word);
		}
		table.push_back(row_vector);
	}

	// check for uneven rows
	for(unsigned i = 0; i < rows(); i++) {
		if(columns() != table[i].size()) {
			throw UnevenRow(i, columns(), table[i].size());
		}
	}
}

void Table::write(ostream & outFile) const
{
	for(unsigned a = 0; a < rows(); a ++){
		outFile << table[a][0];
		for(unsigned b = 1; b < columns(); b ++){
			outFile  << "|" << table[a][b];
		}
		outFile << "\n";
	}

}

bool Table::isEmpty() const
{
	return rows() * columns() == 0;
}

unsigned Table::rows() const
{
	return table.size();
}

unsigned Table::columns() const
{
	if(rows() == 0) {
		return 0;
	} else {
		return table[0].size();
	}
}

string & Table::cell(unsigned r, unsigned c)
{
	if(r >= rows() || c >= columns()) {
		throw OutOfBounds(r, c);
	} else {
		return table[r][c];
	}
}


// Exceptions
Table::OutOfBounds::OutOfBounds(unsigned row, unsigned column)
{
	this->row = row;
	this->column = column;
}

Table::UnevenRow::UnevenRow(unsigned row, unsigned expectedColumns, unsigned gotColumns)
{
	this->row = row;
	this->expectedColumns = expectedColumns;
	this->gotColumns = gotColumns;
}
