#pragma once

#include"Procon2013\Core\Core.h"
#include"Procon2013\Core\Calc.h"
#include"Dot1Point.h"

namespace pro{

// ������ۑ�����N���X
class PRO_EXPORTS LineSegment
{
public:

	Dot1Point dot1[2];	// ��_
	cv::Vec2f unit;		// �P�ʃx�N�g��
	double distance;	// 2�_�ԋ���

public:
	LineSegment(void);
	~LineSegment(void);

	void init(Dot1Point dot11,Dot1Point dot12);
	void init(Dot1Point dot1[2]);

	void draw(Image& img,cv::Scalar dot_col = cv::Scalar::all(0)
						,cv::Scalar line_col = cv::Scalar::all(0)
						,int thickness = 1);

};

// �T�C�R����2�̖ڂ̃N���X
typedef LineSegment Dot2Point;


}