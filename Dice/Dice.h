#pragma once

#include"Procon2013\Core\Core.h"
#include"DiceDraw.h"
#include"DiceRandomDraw.h"
#include"DiceInfo.h"

#include"DotPoint.h"
#include"LineSegment.h"
#include"Dot3Point.h"
#include"DiceDetection.h"
#include"DiceEncode.h"

namespace pro{



class Dice
{
public:
	Dice(void);
	~Dice(void);

	static PRO_EXPORTS void disPlay();
};

}

