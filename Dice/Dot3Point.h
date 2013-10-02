#pragma once

#include"Procon2013\Core\Core.h"
#include"DotPoint.h"

namespace pro{

class PRO_EXPORTS Dot3Point
{
public:

	DotPoint center;
	DotPoint dot[2];
	int angle;

	DiceInfo::dtype type;

public:
	Dot3Point(void);
	~Dot3Point(void);
};


}