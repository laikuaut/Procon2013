#pragma once

#include"Procon2013\Core\Core.h"

namespace pro{

class Senary
{
private:

	vector<short> num;


public:
	Senary(void);
	~Senary(void);

	void init(int dec);
	void inits(vector<short> senary);

	void display();
	int getDec();

	int size() const;

	short operator[](int i);
};


}