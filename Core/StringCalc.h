#pragma once

#include"type_c.h"
#include<fstream>
#include<iostream>

namespace pro{

class PRO_EXPORTS StringCalc
{
public:

	static const int STRNUM = 86;

public:
	StringCalc(void);
	~StringCalc(void);

	static void randomInit();
	static void randomStringOutput(int length,string filename);


};

}