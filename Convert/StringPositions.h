#pragma once

#include"Procon2013\Core\Core.h"

namespace pro{

class StringPositions
{
private:

	vector<char> value;
	vector<int> positions;

public:
	StringPositions(void);
	~StringPositions(void);

	void init(vector<char> value,int i);
	void add(int i);
	vector<char> getValue() const;
	void erase(int i);

	int size() const;
	int length() const;
	bool equal(vector<char> str);

	int operator[](int i);

};

}