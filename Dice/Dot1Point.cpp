#include "Dot1Point.h"

namespace pro{

Dot1Point::Dot1Point(void)
{
}


Dot1Point::~Dot1Point(void)
{
}

void Dot1Point::init(float x,float y,int size){
	this->pt.x = x;
	this->pt.y = y;
	this->size = size;
}
void Dot1Point::init(cv::Point2f pt,int size){
	this->pt = pt;
	this->size = size;
}

void Dot1Point::draw(Image& img,cv::Scalar scal){
	img.circle(pt,sqrt(size/CV_PI),scal);
}

Dot1Point::operator cv::Point(){
	return pt;
}
Dot1Point::operator cv::Point2f(){
	return pt;
}
Dot1Point::operator cv::Point2f*(){
	return &pt;
}

}