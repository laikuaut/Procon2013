#pragma once

#include"Procon2013\Core\Core.h"
#include"DotPoint.h"
#include"LineSegment.h"

namespace pro{

class PRO_EXPORTS Dot3Point
{
public:

	DotPoint center;
	DotPoint dot[2];
	int formedAngle;
	int angle;

	DiceInfo::dtype type;

public:
	Dot3Point(void);
	~Dot3Point(void);

	// èåèÅFlseg1Ç∆lseg2ÇÃénì_dot[0]Ç™ìØÇ∂Ç≈Ç†ÇÈÇ±Ç∆
	void init(LineSegment lseg1,LineSegment lseg2,DiceInfo::dtype type);
	void init(Dot3Point dot3);

	void draw(Image& img
			,cv::Scalar dot_col = cv::Scalar::all(0)
			,cv::Scalar line_col = cv::Scalar::all(0)
			,int thickness = 1);
	void drawCenter(Image& img,cv::Scalar scal = cv::Scalar::all(0));

};


}