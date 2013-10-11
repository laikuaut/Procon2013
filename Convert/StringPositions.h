#pragma once

#include"Procon2013\Core\Core.h"

namespace pro{

class StringPositions
{
private:

	vector<char> value;
	vector<int> positions;
	vector<int> reversePositions;

public:
	StringPositions(void);
	~StringPositions(void);

	void init(vector<char> value,int i);
	void add(int i,bool rev=false);
	vector<char> getValue() const;
	void erase(int i,bool rev=false);

	int size(bool rev=false) const;
	int length() const;
	bool equal(vector<char> str,bool rev=false);

	int operator[](int i);

};

}