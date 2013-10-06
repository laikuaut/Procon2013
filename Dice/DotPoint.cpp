#include "DotPoint.h"

namespace pro{

DotPoint::DotPoint(void)
{
}


DotPoint::~DotPoint(void)
{
}

void DotPoint::init(float x,float y,int size){
	this->pt.x = x;
	this->pt.y = y;
	this->size = size;
}
void DotPoint::init(cv::Point2f pt,int size){
	this->pt = pt;
	this->size = size;
}

void DotPoint::draw(Image& img,cv::Scalar scal){
	img.circle(pt,sqrt(size/CV_PI),scal);
}

void DotPoint::draw(Image& img,double sizeRate,cv::Scalar scal){
	img.circle(pt,sqrt(size*sizeRate/CV_PI),scal);
}

DotPoint::operator cv::Point(){
	return pt;
}
DotPoint::operator cv::Point2f(){
	return pt;
}
DotPoint::operator cv::Point2f*(){
	return &pt;
}

void Dot1Point::init(float x,float y,int size,DiceInfo::dtype type){
	this->pt.x = x;
	this->pt.y = y;
	this->size = size;
	this->type = type;
}
void Dot1Point::init(cv::Point2f pt,int size,DiceInfo::dtype type){
	this->pt = pt;
	this->size = size;
	this->type = type;
}
void Dot1Point::init(DotPoint dot,DiceInfo::dtype type){
	this->pt = dot.pt;
	this->size = dot.size;
	this->type = type;
}

}