#pragma once

#include"Procon2013\Core\Core.h"
#include"Procon2013\ImageProcessing\Image.h"
#include"DiceInfo.h"

namespace pro{

// 
class PRO_EXPORTS DotPoint{
public:

	cv::Point2f pt;
	int size;

public:
	DotPoint(void);
	~DotPoint(void);

	void init(float x,float y,int size=0);
	void init(cv::Point2f pt,int size=0);

	void draw(Image& img,cv::Scalar scal = cv::Scalar::all(0));

	
	operator cv::Point ();
	operator cv::Point2f ();
	operator cv::Point2f* ();
};

// サイコロの1の点クラス
class PRO_EXPORTS Dot1Point : public DotPoint
{
public:

	DiceInfo::dtype type;

	void init(float x,float y,int size,DiceInfo::dtype type=DiceInfo::none);
	void init(cv::Point2f pt,int size,DiceInfo::dtype type=DiceInfo::none);

};

}