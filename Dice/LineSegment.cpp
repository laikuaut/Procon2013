#include "LineSegment.h"

namespace pro{

LineSegment::LineSegment(void)
{
}


LineSegment::~LineSegment(void)
{
}

void LineSegment::init(DotPoint dot1,DotPoint dot2){
	dot[0] = dot1;
	dot[1] = dot2;
	unit = Calc::UnitVec(dot1,dot2);
	distance = Calc::getDistance(dot1,dot2);
}
void LineSegment::init(DotPoint dot[2]){
	this->dot[0] = dot[0];
	this->dot[1] = dot[1];
	unit = Calc::UnitVec(dot[0],dot[1]);
	distance = Calc::getDistance(dot[0],dot[1]);
}

void LineSegment::draw(Image& img,cv::Scalar dot_col,cv::Scalar line_col,int thickness){
	img.line(dot[0],dot[1],line_col,thickness);
	for(int i=0;i<2;i++)
		dot[i].draw(img,dot_col);
}

void Dot2Point::init(DotPoint dot1,DotPoint dot2,DiceInfo::dtype type){
	dot[0] = dot1;
	dot[1] = dot2;
	unit = Calc::UnitVec(dot1,dot2);
	distance = Calc::getDistance(dot1,dot2);
	this->type = type;
}

void Dot2Point::init(DotPoint dot[2],DiceInfo::dtype type){
	this->dot[0] = dot[0];
	this->dot[1] = dot[1];
	unit = Calc::UnitVec(dot[0],dot[1]);
	distance = Calc::getDistance(dot[0],dot[1]);
	this->type = type;
}

}