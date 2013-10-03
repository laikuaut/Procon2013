#include "Dot4Point.h"

namespace pro{

Dot4Point::Dot4Point(void)
{
}


Dot4Point::~Dot4Point(void)
{
}

void Dot4Point::init(LineSegment line1,LineSegment line2,DotPoint center,DiceInfo::dtype type){
	line[0] = line1;
	line[1] = line2;
	this->center = center;
	this->type = type;
}

void Dot4Point::draw(Image& img,cv::Scalar dot_col,cv::Scalar line_col,int thickness){
	line[0].draw(img,dot_col,line_col,thickness);
	line[1].draw(img,dot_col,line_col,thickness);
}

void Dot4Point::drawCenter(Image& img,cv::Scalar scal){
	center.draw(img,scal);
}

}