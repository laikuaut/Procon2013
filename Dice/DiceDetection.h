#pragma once

#include"Procon2013\Core\Core.h"
#include"Dot1Point.h"
#include"Procon2013\ImageProcessing\LabelingCenter.h"

namespace pro{

// �T�C�R������N���X
class DiceDetection
{
private:

	// �_�f�[�^
	std::vector<cv::Point2f> points;
	std::vector<int> sizes;
	std::vector<short> flags;
	int num;

	// �T�C�R���̖ڃf�[�^
	std::vector<Dot1Point> dot1points;

public:
	DiceDetection(void);
	~DiceDetection(void);

	// ������
	void init(int num,std::vector<cv::Point2f> points,std::vector<int> sizes);
	void init(LabelingCenter lc);

	// �ڔ��菈��


	// �폜����


	// �`��
	void drawAllPoints(Image& img,cv::Scalar scal = cv::Scalar::all(0));
	//void drawDot1Points(Image img,cv::Scalar scal = cv::Scalar::all(0));
	
	// 

};

}