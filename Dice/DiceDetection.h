#pragma once

#include"Procon2013\Core\Core.h"
#include"DotPoint.h"
#include"LineSegment.h"
#include"Dot3Point.h"
#include"DiceInfo.h"
#include"Dot4Point.h"
#include"Dot5Point.h"
#include"Dot6Point.h"

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
	// double
	static const int dotCircleFilterPer = 1;
	static const int dotCircleFilterRadiusPer = 2;

	// 1�̖ڂ̒��o
	// double
	static const int dot1CircleFilterPer = 1;
	static const int dot1CircleFilterRadiusPer = 3;

	// �咆�T�C�R����1�̖ڂ̔��ʂɎg�p
	//	-> �אڂ���T�C�R���Ƃ̌���苗��
	static const int dot1LMDetectRadius = 73;
	static const int dot1LMCorrectRadius = 90;

	// �咆�T�C�R���Ɍ딻�肵�����T�C�R���̓_�C���̂��߂̔��a
	static const int correctMiddleRadius = 30*3;
	static const int correctLargeRadius = 50*3;
	static const int correctMiddleMaxSize = 300;
	static const int correctLargeMinSize = 230;

	// �������o���a
	static const int lineSmallRadius = 40;
	static const int lineMiddleRadius = 60;
	static const int lineLargeRadius = 80;

	// �Q�̖ڌ��o�̔��a
	static const int dot2SmallMinDistance = 0;
	static const int dot2MiddleMinDistance = 0;
	static const int dot2LargeMinDistance = 0;
	static const int dot2SmallMaxDistance = 23;
	static const int dot2MiddleMaxDistance = 40;
	static const int dot2LargeMaxDistance = 50;
	static const int dot2SmallDistance = 35;
	static const int dot2MiddleDistance = 60;
	static const int dot2LargeDistance = 70;
	static const int dot2MinAngle = 35;
	static const int dot2MaxAngle = 55;

	// �S�̖ڌ��o
	static const int dot4SmallMinDistance = 0;
	static const int dot4MiddleMinDistance = 0;
	static const int dot4LargeMinDistance = 0;
	static const int dot4SmallMaxDistance = 20;
	static const int dot4MiddleMaxDistance = 33;
	static const int dot4LargeMaxDistance = 45;
	static const int dot4SmallDistance = 37;
	static const int dot4MiddleDistance = 60;
	static const int dot4LargeDistance = 80;
	//static const int dot4MinAngle = 35;
	//static const int dot4MaxAngle = 55;
	static const int dot4CorrectMiddleDistance = 85;
	static const int dot4CorrectMiddleLoopCount = 5;

	// �S3�_
	static const int allDot3Angle = 160;
	static const int allDot3SmallMinDistance = 0;
	static const int allDot3MiddleMinDistance = 0;
	static const int allDot3LargeMinDistance = 0;
	static const int allDot3SmallMaxDistance = 20;
	static const int allDot3MiddleMaxDistance = 35;
	static const int allDot3LargeMaxDistance = 50;

	// 6�̖�
	static const int dot6SmallDistance = 20;
	static const int dot6MiddleDistance = 30;
	static const int dot6LargeDistance = 50;
	static const int dot6SmallRasius = 20;
	static const int dot6MiddleRasius = 37;
	static const int dot6LargeRasius = 60;

protected:


	/***************
	 *   �N���X��`
	 */

	// �S�_�N���X
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

	// �S���N���X
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

		void clear();

		LineSegment operator[](int i) const;
	};

	// �S3�_�����N���X
	class Dot3Points{
	private:

		std::vector<Dot3Point> dot3s;
		int num;
	public:
		std::vector<short> flags;
		std::vector<DiceInfo::dtype> types;
		std::vector<int> kinds;
		std::vector<int> dotNums[3];
	
	public:

		Dot3Points();

		void add(Dot3Point dot3,short flag,DiceInfo::dtype type,int kind,int dotNum1,int dotNum2,int dotNum3);
		int size() const;

		Dot3Point operator[](int i);

	};

	class DotCenters{
	private:

		vector<DotPoint> centers;
		int num;

	public:
		vector<DiceInfo::dtype> types;
		vector<int> kinds;

	public:

		DotCenters();

		void clear();

		void add(DotPoint center,DiceInfo::dtype type,int kind);
		int size() const;

		DotPoint operator[](int i);

	};

private:


	/***************
	 *   �ϐ���`
	 */

	// ���摜
	Image src;

	// �_�Q�f�[�^
	DotPoints allPoints;

	// �����f�[�^
	LineSegments allLines;

	// 3�_�f�[�^
	Dot3Points allDot3Points;

	// �T�C�R���̒��S���W
	DotCenters allDotCenters;

	// ���o�~�X�������������S���W
	DotCenters missDotCenters;

	// �T�C�R���̖ڃf�[�^
	std::vector<Dot1Point> dot1Points;
	std::vector<Dot2Point> dot2Points;
	std::vector<Dot3Point> dot3Points;
	std::vector<Dot4Point> dot4Points;
	std::vector<Dot5Point> dot5Points;
	std::vector<Dot6Point> dot6Points;

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
	void getAllDot3Points();
	void getAllDotCenters();

	// �ڂ̔��菈��
	void getDot1Points();
	void getDot2Points();
	void getDot4Points();	// 124536�̏�
	void _getDot4Points();	// 125364�̏�
	void getDot5Points();
	void getDot3Points();
	void getDot6Points();

	// �폜����
	void eraseDot1Points();
	void clearAllLines();
	void clearAllDotCenters();

	// �C������
	void correctPointType();
	int correctMiddleDot4Points(); //�]��_����4�̖ڂ̒��o�~�X�����
	void correctOddMiddleToLarge();

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
	

	void drawDot4Points(Image& img
						,cv::Scalar dot_col = cv::Scalar::all(0)
						,cv::Scalar line_col = cv::Scalar::all(0)
						,int thickness = 1);
	void drawTypeDot4Points(Image& img,DiceInfo::dtype type
						,cv::Scalar dot_col = cv::Scalar::all(0)
						,cv::Scalar line_col = cv::Scalar::all(0)
						,int thickness = 1);
	void drawDot4Center(Image& img,cv::Scalar scal = cv::Scalar::all(0));


	void drawAllDot3Points(Image& img
			,cv::Scalar dot_col = cv::Scalar::all(0)
			,cv::Scalar line_col = cv::Scalar::all(0)
			,int thickness = 1);
	void drawAllDot3Center(Image& img,cv::Scalar scal = cv::Scalar::all(0));
	void drawTrueAllDot3Points(Image& img
			,cv::Scalar dot_col = cv::Scalar::all(0)
			,cv::Scalar line_col = cv::Scalar::all(0)
			,int thickness = 1);
	void drawFalseAllDot3Points(Image& img
			,cv::Scalar dot_col = cv::Scalar::all(0)
			,cv::Scalar line_col = cv::Scalar::all(0)
			,int thickness = 1);
	void drawTypeAllDot3Points(Image& img,DiceInfo::dtype type
			,cv::Scalar dot_col = cv::Scalar::all(0)
			,cv::Scalar line_col = cv::Scalar::all(0)
			,int thickness = 1);
	void drawKindAllDot3Points(Image& img,int kind
			,cv::Scalar dot_col = cv::Scalar::all(0)
			,cv::Scalar line_col = cv::Scalar::all(0)
			,int thickness = 1);


	void drawDot5Points(Image& img
			,cv::Scalar dot_col = cv::Scalar::all(0)
			,cv::Scalar line_col = cv::Scalar::all(0)
			,int thickness = 1);
	void drawTypeDot5Points(Image& img,DiceInfo::dtype type
			,cv::Scalar dot_col = cv::Scalar::all(0)
			,cv::Scalar line_col = cv::Scalar::all(0)
			,int thickness = 1);
	void drawDot5Center(Image& img,cv::Scalar scal = cv::Scalar::all(0));


	void drawDot3Points(Image& img
			,cv::Scalar dot_col = cv::Scalar::all(0)
			,cv::Scalar line_col = cv::Scalar::all(0)
			,int thickness = 1);
	void drawTypeDot3Points(Image& img,DiceInfo::dtype type
			,cv::Scalar dot_col = cv::Scalar::all(0)
			,cv::Scalar line_col = cv::Scalar::all(0)
			,int thickness = 1);
	void drawDot3Center(Image& img,cv::Scalar scal = cv::Scalar::all(0));


	void drawDot6Points(Image& img
			,cv::Scalar dot_col = cv::Scalar::all(0)
			,cv::Scalar line_col = cv::Scalar::all(0)
			,int thickness = 1);
	void drawTypeDot6Points(Image& img,DiceInfo::dtype type
			,cv::Scalar dot_col = cv::Scalar::all(0)
			,cv::Scalar line_col = cv::Scalar::all(0)
			,int thickness = 1);
	void drawDot6Center(Image& img,cv::Scalar scal = cv::Scalar::all(0));	

	
	void drawAllDotCenters(Image& img,cv::Scalar scal = cv::Scalar::all(0));
	void drawTypeAllDotCenters(Image& img,DiceInfo::dtype type,cv::Scalar scal = cv::Scalar::all(0));
	void drawKindAllDotCenters(Image& img,int kind,cv::Scalar scal = cv::Scalar::all(0));


	// ���擾
	int getNumAllPoints() const;
	int getNumTrueAllPoints();
	int getNumFalseAllPoints();
	int getNumTypeAllPoints(DiceInfo::dtype type);
	int getNumKindAllPoints(int kind);
	int getNumAllLines();
	int getNumTrueAllLines();
	int getNumFalseAllLines();
	int getNumTypeAllLines(DiceInfo::dtype type);
	int getNumKindAllLines(int kind);
	int getNumAllDot3Points();
	int getNumTrueAllDot3Points();
	int getNumFalseAllDot3Points();
	int getNumTypeAllDot3Points(DiceInfo::dtype type);
	int getNumKindAllDot3Points(int kind);
	int getNumAllDotCenters();
	int getNumTypeAllDotCenters(DiceInfo::dtype type);
	int getNumKindAllDotCenters(int kind);
	int getNumDot1Points(DiceInfo::dtype type = DiceInfo::none);
	int getNumDot2Points(DiceInfo::dtype type = DiceInfo::none);
	int getNumDot3Points(DiceInfo::dtype type = DiceInfo::none);
	int getNumDot4Points(DiceInfo::dtype type = DiceInfo::none);
	int getNumDot5Points(DiceInfo::dtype type = DiceInfo::none);
	int getNumDot6Points(DiceInfo::dtype type = DiceInfo::none);

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
	4.1. �T�C�R���̃T�C�Y���Ƃɐ�����`��
	4.2. �Ɨ������_���폜(none)
 �T�D2�̖ڂ̔F��
	5.1. �����̃T�C�Y����2�̖ڂ��܂܂Ȃ������𒊏o
	5.2. ��ɒ��o���������Ɏg�p����Ă��Ȃ��_��2�̖ڂ̓_���Ƃ���
	5.3. �p�x�Ƌ�������2�̖ڂ�����
 */

}