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

	/***************
	 *   �萔��`
	 */

	// �T�C�R���̃T�C�Y���ʂɎg�p����萔�Q
	static const int dotSmallMinSize = 30;
	static const int dotSmallMaxSize = 99;
	static const int dotMiddleMinSize = 100;
	static const int dotMiddleMaxSize = 280;
	static const int dotLargeMinSize = 281;
	static const int dotLargeMaxSize = 600;
	static const int dotNoneMinSize = 601;
	static const int dotNoneMaxSize = 2000;
	static const int dot1MinSize = 200;
	static const int dot1MaxSize = 2000;

	// �咆�T�C�R����1�̖ڂ̔��ʂɎg�p
	//	-> �אڂ���T�C�R���Ƃ̌���苗��
	static const int dot1LMDetectRadius = 70;
	static const int dot1LMCorrectRadius = 80;

	// �咆�T�C�R���Ɍ딻�肵�����T�C�R���̓_�C���̂��߂̔��a
	static const int correctMiddleRadius = 30*2;
	static const int correctLargeRadius = 50*2;
	static const int correctMiddleMaxSize = 500;
	static const int correctLargeMinSize = 250;

	// �������o���a
	static const int lineSmallRadius = 40;
	static const int lineMiddleRadius = 55;
	static const int lineLargeRadius = 70;

	// �Q�̖ڌ��o�̔��a
	static const int dot2SmallMinDistance = 0;
	static const int dot2MiddleMinDistance = 0;
	static const int dot2LargeMinDistance = 0;
	static const int dot2SmallMaxDistance = 23;
	static const int dot2MiddleMaxDistance = 40;
	static const int dot2LargeMaxDistance = 58;
	static const int dot2SmallDistance = 35;
	static const int dot2MiddleDistance = 55;
	static const int dot2LargeDistance = 70;

protected:


	/***************
	 *   �N���X��`
	 */
	class DotPoints{
	private:
		int num;
		std::vector<DotPoint> points;
	public:
		std::vector<short> flags;
		std::vector<DiceInfo::dtype> types;
		std::vector<int> kinds;
	public:

		DotPoints();

		void add(DotPoint dot,short flag,DiceInfo::dtype type,int kind);
		int size() const;

		DotPoint operator[](int i) const;

	};

	class LineSegments{
	private:
		
		std::vector<LineSegment> lines;
		int num;

	public:
		std::vector<short> flags;
		std::vector<DiceInfo::dtype> types;
		std::vector<int> kinds;
		std::vector<int> dotNums[2];
	public:

		LineSegments();

		void add(LineSegment lseg,short flag,DiceInfo::dtype type,int kind,int dotNum1,int dotNum2);
		int size() const;

		LineSegment operator[](int i) const;
	};

private:


	/***************
	 *   �ϐ���`
	 */

	// ���摜
	Image src;

	// �_�Q�f�[�^
	//std::vector<DotPoint> allPoints;
	//std::vector<short> ptFlags;
	//std::vector<DiceInfo::dtype> ptTypes;
	//std::vector<int> ptKinds;
	//int ptNum;
	DotPoints allPoints;

	// �����f�[�^
	//std::vector<LineSegment> allLine;
	//std::vector<short> lineFlags;
	//int lineNum;
	//int maxLineRadius;  // �����F���̍Œ����a
	LineSegments allLines;


	// �T�C�R���̖ڃf�[�^
	std::vector<Dot1Point> dot1Points;
	std::vector<Dot2Point> dot2Points;
	std::vector<Dot3Point> dot3Points;


public:


	/***************
	 *   �֐���`
	 */

	DiceDetection(void);
	~DiceDetection(void);

	// ������
	//void init(int num,std::vector<cv::Point2f> points,std::vector<int> sizes);
	//void init(LabelingCenter lc);
	void init(Image src);

	// �K�v�v�f�̎擾
	void getAllPoints();
	void getAllLines();
	//void getAllDot3Points();

	// �ڂ̔��菈��
	void getDot1Points();
	void getDot2Points();

	// �폜����
	void eraseDot1Points();

	// �C������
	void correctPointType();

	// �`��
	void drawAllPoints(Image& img,cv::Scalar scal = cv::Scalar::all(0));
	void drawTruePoints(Image& img,cv::Scalar scal = cv::Scalar::all(0));
	void drawFalsePoints(Image& img,cv::Scalar scal = cv::Scalar::all(0));
	void drawTypePoints(Image& img,DiceInfo::dtype type,cv::Scalar scal = cv::Scalar::all(0));
	void drawKindPoints(Image& img,int kind,cv::Scalar scal = cv::Scalar::all(0));


	void drawAllLine(Image& img,cv::Scalar dot_col = cv::Scalar::all(0)
						,cv::Scalar line_col = cv::Scalar::all(0)
						,int thickness = 1);
	void drawTrueLine(Image& img,cv::Scalar dot_col = cv::Scalar::all(0)
						,cv::Scalar line_col = cv::Scalar::all(0)
						,int thickness = 1);
	void drawFalseLine(Image& img,cv::Scalar dot_col = cv::Scalar::all(0)
						,cv::Scalar line_col = cv::Scalar::all(0)
						,int thickness = 1);
	void drawTypeLine(Image& img,DiceInfo::dtype type
						,cv::Scalar dot_col = cv::Scalar::all(0)
						,cv::Scalar line_col = cv::Scalar::all(0)
						,int thickness = 1);
	void drawKindLine(Image& img,int kind
						,cv::Scalar dot_col = cv::Scalar::all(0)
						,cv::Scalar line_col = cv::Scalar::all(0)
						,int thickness = 1);
	

	void drawDot1Points(Image& img,cv::Scalar scal = cv::Scalar::all(0));
	void drawTypeDot1Points(Image& img,DiceInfo::dtype type,cv::Scalar scal = cv::Scalar::all(0));
	

	void drawDot2Points(Image& img,cv::Scalar dot_col = cv::Scalar::all(0)
						,cv::Scalar line_col = cv::Scalar::all(0)
						,int thickness = 1);
	void drawTypeDot2Points(Image& img,DiceInfo::dtype type
						,cv::Scalar dot_col = cv::Scalar::all(0)
						,cv::Scalar line_col = cv::Scalar::all(0)
						,int thickness = 1);
	void drawDot2Center(Image& img,cv::Scalar scal = cv::Scalar::all(0));

};

/**
 
 DiceDetection ����
 ��Ǝ菇
 �P�D�S�_�擾:getAllPoints()
	1.1. ������̏��ԂŃT�C�Y�w��i2�i�ڂɒu���ꂽ���T�C�R���Ƒ�T�C�R���̔��ʍ���j
	1.2. 1�̖ڂ̏��T�C�R����large�ɐݒ�
	1.3. 1�̖ڂ̒���T�C�R����large�ɐݒ�
 �Q�D�P�̖ڂ̃T�C�R�����o:getDot1Points()
	2.1. �ԐF���o����1�̖ڍ��W�擾
	2.2. �S�_�ƍ��W��r�A�d�Ȃ����_��S�_�ɂ�����false�w��
	2.3. ���T�C�R����1�̖ڂ�large����small�֒���
	2.4. ���ӂƂ̍��W�̌���肩��咆��1�̖ڔ���
 �R�D�T�C�Y����C��:correctPointType()
	3.1. 2�i�ڂɒu�������T�C�R�����T�C�R���̃T�C�Y�ƌ딻��
	3.2. ���ӂɂ���T�C�Y�̓_�̐����ׂ邱�ƂŏC��
 �S�D�S�����擾:getAllLines()
 
 */

}