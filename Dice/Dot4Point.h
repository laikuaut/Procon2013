#pragma once

#include"Procon2013\Core\Core.h"
#include"LineSegment.h"

namespace pro{

class Dot4Point
{
public:

	LineSegment line[2];
	DotPoint center;
	DiceInfo::dtype type;

public:
	Dot4Point(void);
	~Dot4Point(void);

	void init(LineSegment line1,LineSegment line2,DotPoint center,DiceInfo::dtype type);

	void draw(Image& img,cv::Scalar dot_col = cv::Scalar::all(0)
						,cv::Scalar line_col = cv::Scalar::all(0)
						,int thickness = 1);
	void drawCenter(Image& img,cv::Scalar scal = cv::Scalar::all(0));

};

}