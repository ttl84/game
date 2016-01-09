#include "Table.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

void Table::read(string path)
{
	std::ifstream inFile(path);
	if(inFile.is_open()){
		this->read(inFile);
	}
}

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
}

void Table::write(string path) const
{
	ofstream outFile(path);
	if(outFile.is_open()){
		this->write(outFile);
	}
}

void Table::write(ostream & outFile) const
{
	for(int a = 0; a < rows(); a ++){
		outFile << table[a][0];
		for(int b = 1; b < columns(); b ++){
			outFile  << "|" << table[a][b];
		}
		outFile << "\n";
	}

}

bool Table::isEmpty() const
{
	return rows() * columns() == 0;
}

int Table::rows() const
{
	return table.size();
}

int Table::columns() const
{
	if(rows() == 0) {
		return 0;
	} else {
		return table[0].size();
	}
}

string Table::cell(int r, int c) const
{
	return table[r][c];
}
