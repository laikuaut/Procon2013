#pragma once

#include"type_c.h"
#include<opencv2\core\core.hpp>
#include<iostream>

namespace pro{

class PRO_EXPORTS Calc
{
public:
	Calc(void);
	~Calc(void);

	static cv::Point PointRotate(cv::Point pt,int angle);
	static cv::Point PointRotate(double dx,double dy,int angle);
};

}