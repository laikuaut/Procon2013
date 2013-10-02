#pragma once

#include"Procon2013\Core\Core.h"
#include"DotPoint.h"
#include"LineSegment.h"
#include"Dot3Point.h"
#include"DiceInfo.h"

#include"Procon2013\ImageProcessing\LabelingCenter.h"


namespace pro{

// �T�C�R������N���X
class DiceDetection
{
private:

	// ���摜
	Image src;

	// �_�Q�f�[�^
	std::vector<DotPoint> allPoints;
	std::vector<short> ptFlags;
	std::vector<DiceInfo::dtype> ptTypes;
	int ptNum;
	
	// �����f�[�^
	std::vector<LineSegment> allLine;
	std::vector<short> lineFlags;
	int lineNum;
	int maxLineRadius;  // �����F���̍Œ����a

	// �T�C�R���̖ڃf�[�^
	std::vector<Dot1Point> dot1Points;
	std::vector<Dot2Point> dot2Points;
	std::vector<Dot3Point> dot3Points;


public:
	DiceDetection(void);
	~DiceDetection(void);

	// ������
	//void init(int num,std::vector<cv::Point2f> points,std::vector<int> sizes);
	//void init(LabelingCenter lc);
	void init(Image src);

	// �K�v�v�f�̎擾
	void getAllPoints();
	void getAllLines(int maxRadius = 10);
	//void getAllDot3Points();

	// �ڂ̔��菈��
	void getDot1Points();

	// �폜����
	void eraseDot1Points();

	// �`��
	void drawAllPoints(Image& img,cv::Scalar scal = cv::Scalar::all(0));
	void drawTruePoints(Image& img,cv::Scalar scal = cv::Scalar::all(0));
	void drawFalsePoints(Image& img,cv::Scalar scal = cv::Scalar::all(0));
	
	void drawAllLine(Image& img,cv::Scalar dot_col = cv::Scalar::all(0)
						,cv::Scalar line_col = cv::Scalar::all(0)
						,int thickness = 1);
	void drawTrueLine(Image& img,cv::Scalar dot_col = cv::Scalar::all(0)
						,cv::Scalar line_col = cv::Scalar::all(0)
						,int thickness = 1);
	void drawFalseLine(Image& img,cv::Scalar dot_col = cv::Scalar::all(0)
						,cv::Scalar line_col = cv::Scalar::all(0)
						,int thickness = 1);

	void drawDot1Points(Image& img,cv::Scalar scal = cv::Scalar::all(0));
	

};

}