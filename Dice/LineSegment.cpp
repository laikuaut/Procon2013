#include "LineSegment.h"

namespace pro{

LineSegment::LineSegment(void)
{
}


LineSegment::~LineSegment(void)
{
}

void LineSegment::init(Dot1Point dot11,Dot1Point dot12){
	dot1[0] = dot11;
	dot1[1] = dot12;
	unit = Calc::UnitVec(dot11,dot12);
	distance = Calc::getDistance(dot11,dot12);
}
void LineSegment::init(Dot1Point dot1[2]){
	this->dot1[0] = dot1[0];
	this->dot1[1] = dot1[1];
	unit = Calc::UnitVec(dot1[0],dot1[1]);
	distance = Calc::getDistance(dot1[0],dot1[1]);
}

void LineSegment::draw(Image& img,cv::Scalar dot_col,cv::Scalar line_col,int thickness){
	img.line(dot1[0],dot1[1],line_col,thickness);
	for(int i=0;i<2;i++)
		dot1[i].draw(img,dot_col);
}

}