#pragma once
#include"Procon2013\Core\Core.h"

namespace pro{

class CharPositions
{
private:

	char value;
	vector<int> positions;

public:
	CharPositions(void);
	~CharPositions(void);

	void init(char value,int i);
	void add(int i);
	char getValue() const;
	int getNumAtStrNum(int i) const; 

	void erase(int i);

	int size() const;

	int operator[](int i);

};

}