#pragma once

#include"Procon2013\Core\Core.h"
#include"Procon2013\Core\Calc.h"
#include"DotPoint.h"

namespace pro{

// 線分を保存するクラス
class PRO_EXPORTS LineSegment
{
public:

	DotPoint dot[2];	// 基準点
	cv::Vec2f unit;		// 単位ベクトル
	double distance;	// 2点間距離

public:
	LineSegment(void);
	~LineSegment(void);

	void init(DotPoint dot1,DotPoint dot2);
	void init(DotPoint dot[2]);

	void draw(Image& img,cv::Scalar dot_col = cv::Scalar::all(0)
						,cv::Scalar line_col = cv::Scalar::all(0)
						,int thickness = 1);

};

// サイコロの2の目のクラス
class PRO_EXPORTS Dot2Point : public LineSegment
{
public:
	DiceInfo::dtype type;

	void init(DotPoint dot1,DotPoint dot2,DiceInfo::dtype type=DiceInfo::none);
	void init(DotPoint dot[2],DiceInfo::dtype type=DiceInfo::none);

};


}