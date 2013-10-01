#pragma once

#include"Procon2013\Core\Core.h"
#include"Procon2013\ImageProcessing\Image.h"

namespace pro{

// サイコロの1の点クラス
class PRO_EXPORTS Dot1Point
{
public:

	cv::Point2f pt;
	int size;

public:
	Dot1Point(void);
	~Dot1Point(void);

	void init(float x,float y,int size=0);
	void init(cv::Point2f pt,int size=0);

	void draw(Image& img,cv::Scalar scal = cv::Scalar::all(0));

	
	operator cv::Point ();
	operator cv::Point2f ();
	operator cv::Point2f* ();

};

}