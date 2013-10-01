#pragma once

#include"Procon2013\Core\Core.h"
#include"Procon2013\Core\Calc.h"
#include"Dot1Point.h"

namespace pro{

// 線分を保存するクラス
class PRO_EXPORTS LineSegment
{
public:

	Dot1Point dot1[2];	// 基準点
	cv::Vec2f unit;		// 単位ベクトル
	double distance;	// 2点間距離

public:
	LineSegment(void);
	~LineSegment(void);

	void init(Dot1Point dot11,Dot1Point dot12);
	void init(Dot1Point dot1[2]);

	void draw(Image& img,cv::Scalar dot_col = cv::Scalar::all(0)
						,cv::Scalar line_col = cv::Scalar::all(0)
						,int thickness = 1);

};

// サイコロの2の目のクラス
typedef LineSegment Dot2Point;


}