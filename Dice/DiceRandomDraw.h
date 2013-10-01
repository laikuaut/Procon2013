#pragma once

#include"Procon2013\Core\Core.h"
#include"DiceDraw.h"

namespace pro{

class PRO_EXPORTS DiceRandomDraw
{
public:

	DiceDraw dicedraw;

	Timer timer;
	int pattern;

	static int const patNum = 5;

private:
	
	void pattern0();
	void pattern1();
	void pattern2();
	void pattern3();
	void pattern4();
	void pattern5();
	void pattern6();
	void pattern7();
	void pattern8();
	void pattern9();
	
	void setPattern();

public:
	DiceRandomDraw(void);
	~DiceRandomDraw(void);

	void init(int rate=5);

	void run();


};

}