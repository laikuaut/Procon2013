#pragma once

#include"Procon2013\Core\Core.h"
#include"Procon2013\Core\Calc.h"
#include"DotPoint.h"

namespace pro{

// ������ۑ�����N���X
class PRO_EXPORTS LineSegment
{
public:

	DotPoint dot[2];	// ��_
	cv::Vec2f unit;		// �P�ʃx�N�g��
	double distance;	// 2�_�ԋ���

public:
	LineSegment(void);
	~LineSegment(void);

	void init(DotPoint dot1,DotPoint dot2);
	void init(DotPoint dot[2]);

	void draw(Image& img,cv::Scalar dot_col = cv::Scalar::all(0)
						,cv::Scalar line_col = cv::Scalar::all(0)
						,int thickness = 1);

};

// �T�C�R����2�̖ڂ̃N���X
class PRO_EXPORTS Dot2Point : public LineSegment
{
public:
	DiceInfo::dtype type;

	void init(DotPoint dot1,DotPoint dot2,DiceInfo::dtype type=DiceInfo::none);
	void init(DotPoint dot[2],DiceInfo::dtype type=DiceInfo::none);

};


}