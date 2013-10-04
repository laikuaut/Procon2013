#pragma once

#include"Procon2013\Core\Core.h"
#include"DotPoint.h"
#include"Dot3Point.h"

namespace pro{

class PRO_EXPORTS Dot5Point
{
public:

	DotPoint center;
	Dot3Point dot3[2];

	DiceInfo::dtype type;

public:
	Dot5Point(void);
	~Dot5Point(void);

	void init(Dot3Point dot3p1,Dot3Point dot3p2,DiceInfo::dtype type);

	void draw(Image& img
			,cv::Scalar dot_col = cv::Scalar::all(0)
			,cv::Scalar line_col = cv::Scalar::all(0)
			,int thickness = 1);
	void drawCenter(Image& img,cv::Scalar scal = cv::Scalar::all(0));

};


}