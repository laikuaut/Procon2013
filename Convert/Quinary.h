#pragma once

#include"Procon2013\Core\Core.h"

namespace pro{

// 5�i�@(�����g�p)
class Quinary
{
private:

	vector<short> num;


public:
	Quinary(void);
	~Quinary(void);

	void init(int dec);
	void display();
	int getDec();

	short operator[](int i);

};

}