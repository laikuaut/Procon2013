#include "Calc.h"

namespace pro{

Calc::Calc(void)
{
}


Calc::~Calc(void)
{
}

// êßìxí·
cv::Point Calc::PointRotate(cv::Point pt,int angle){
	double s = sin((double)angle*CV_PI/180.),c = cos((double)angle*CV_PI/180.);
	cv::Point point;
	if(abs(s)<0.000001) s=0;
	if(abs(c)<0.000001) c=0;
	point.x = pt.x * c + pt.y * s;
	point.y = -pt.x * s + pt.y * c;
	return point;
}
cv::Point Calc::PointRotate(double dx,double dy,int angle){
	double s = sin((double)angle*CV_PI/180.);
	double c = cos((double)angle*CV_PI/180.);
	cv::Point point;
	if(abs(s)<0.000001) s=0;
	if(abs(c)<0.000001) c=0;
	//std::cout << "s=" << s << std::endl;
	//std::cout << "c=" << c << std::endl;
	point.x = dx * c + dy * s;
	point.y = -dx * s + dy * c;
	return point;
}

}