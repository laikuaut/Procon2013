#pragma once

#include"Procon2013\Core\Core.h"
#include"DiceDraw.h"
#include"DiceRandomDraw.h"
#include"DiceInfo.h"

#include"Dot1Point.h"
#include"LineSegment.h"
#include"DiceDetection.h"

namespace pro{



class Dice
{
public:
	Dice(void);
	~Dice(void);

	static PRO_EXPORTS void disPlay();
};

}

