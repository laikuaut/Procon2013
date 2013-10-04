#include "Dot3Point.h"

namespace pro{

Dot3Point::Dot3Point(void)
{
}


Dot3Point::~Dot3Point(void)
{
}

void Dot3Point::init(LineSegment lseg1,LineSegment lseg2,DiceInfo::dtype type){
	this->type = type;
	center.init(lseg1.dot[0],lseg1.dot[0].size);
	dot[0].init(lseg1.dot[1],lseg1.dot[1].size);
	dot[1].init(lseg2.dot[1],lseg2.dot[1].size);
	formedAngle = Calc::InnerProductAngle(lseg1.unit,lseg2.unit)/CV_PI*180;
	angle = Calc::getAngle(dot[0],dot[1]);
}

void Dot3Point::init(Dot3Point dot3){
	center.init(dot3.center,dot3.center.size);
	dot[0].init(dot3.dot[0],dot3.dot[0].size);
	dot[1].init(dot3.dot[1],dot3.dot[1].size);
	formedAngle = dot3.formedAngle;
	angle = dot3.angle;
}

void Dot3Point::draw(Image& img,cv::Scalar dot_col,cv::Scalar line_col,int thickness){
	LineSegment lseg;
	lseg.init(center,dot[0]);
	lseg.draw(img,dot_col,line_col,thickness);
	lseg.init(center,dot[1]);
	lseg.draw(img,dot_col,line_col,thickness);
}

void Dot3Point::drawCenter(Image& img,cv::Scalar scal){
	center.draw(img,scal);
}

}