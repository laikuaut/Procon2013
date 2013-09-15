#pragma once

#include"Procon2013/Core/Core.h"
#include"opencv2\core\core.hpp"
#include"opencv2\highgui\highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include<string>

class PRO_EXPORTS cv::Mat;

namespace pro{

class PRO_EXPORTS Image
{

private:

	cv::Mat img;
	int w,h;

public:

	Dir path;

private:

	void w_h_reset();

public:
	
	Image(void);
	
	void init(int w,int h);

	void release();
	void clone(const Image& src);
	void swap(Image& src);
	void resize(const Image& src);
	void resize(const Image& src,double fx,double fy);
	void resize(const Image& src,cv::Size size);
	
	void grayeScale(const Image& src);
	void binarization(const Image& src);
	void adaptiveBinarization(const Image& src);

	void load(string name);
	void save(string name);

	void circle(cv::Point center,int radius,cv::Scalar scal = cv::Scalar(0,0,0));
	void rectangle(cv::Point pt1,cv::Point pt2,cv::Scalar scal = cv::Scalar(0,0,0),int thickness=1);
	void rectangle(cv::Point center,int w,int h,cv::Scalar scal = cv::Scalar(0,0,0),int thickness=1);
	void line(cv::Point pt1,cv::Point pt2,cv::Scalar scal = cv::Scalar(0,0,0),int thickness=1);
	void triangle(cv::Point pt1,cv::Point pt2,cv::Point pt3,cv::Scalar scal = cv::Scalar(0,0,0),int thickness=1);

	operator cv::Mat &(); 


};

}
