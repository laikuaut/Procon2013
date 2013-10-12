#pragma once

#include"Procon2013\Core\Core.h"
#include"DotPoint.h"
#include"LineSegment.h"
#include"Dot3Point.h"
#include"DiceInfo.h"
#include"Dot4Point.h"
#include"Dot5Point.h"
#include"Dot6Point.h"
#include"Procon2013\ImageProcessing\\MouseEvent.h"

#include"Procon2013\ImageProcessing\LabelingCenter.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/optional.hpp>
using namespace boost::property_tree;

namespace pro{

// �T�C�R������N���X
class PRO_EXPORTS DiceDetection : public MouseEvent
{
private:

	/***************
	 *   �p�����[�^�f�t�H���g�萔��`
	 */

	// �T�C�R���̃T�C�Y���ʂɎg�p����萔�Q
	static const int default_dotSmallMinSize	= 30;
	static const int default_dotSmallMaxSize	= 99;
	static const int default_dotMiddleMinSize	= 100;
	static const int default_dotMiddleMaxSize	= 280;
	static const int default_dotLargeMinSize	= 281;
	static const int default_dotLargeMaxSize	= 600;
	static const int default_dotNoneMinSize		= 601;
	static const int default_dotNoneMaxSize		= 2000;
	static const int default_dot1MinSize		= 100;
	static const int default_dot1MaxSize		= 2000;
	// double
	static const int default_dotCircleFilterPer			= 1;
	static const int default_dotCircleFilterRadiusPer	= 2;

	// 1�̖ڂ̒��o
	// double
	static const int default_dot1CircleFilterPer		= 1;
	static const int default_dot1CircleFilterRadiusPer	= 3;
	// �咆�T�C�R����1�̖ڂ̔��ʂɎg�p
	//	-> �אڂ���T�C�R���Ƃ̌���苗��
	static const int default_dot1LMDetectRadius		= 73;
	static const int default_dot1LMCorrectRadius	= 90;

	// �咆�T�C�R���Ɍ딻�肵�����T�C�R���̓_�C���̂��߂̔��a
	static const int default_correctMiddleRadius	= 30*3;
	static const int default_correctLargeRadius		= 50*3;
	static const int default_correctMiddleMaxSize	= 300;
	static const int default_correctLargeMinSize	= 230;

	// �������o���a
	static const int default_lineSmallRadius	= 40;
	static const int default_lineMiddleRadius	= 60;
	static const int default_lineLargeRadius	= 80;

	// �Q�̖ڌ��o�̔��a
	static const int default_dot2SmallMinDistance	= 0;
	static const int default_dot2MiddleMinDistance	= 0;
	static const int default_dot2LargeMinDistance	= 0;
	static const int default_dot2SmallMaxDistance	= 23;
	static const int default_dot2MiddleMaxDistance	= 40;
	static const int default_dot2LargeMaxDistance	= 50;
	static const int default_dot2SmallDistance		= 35;
	static const int default_dot2MiddleDistance		= 60;
	static const int default_dot2LargeDistance		= 70;
	static const int default_dot2MinAngle			= 35;
	static const int default_dot2MaxAngle			= 55;

	// �S�̖ڌ��o
	static const int default_dot4SmallMinDistance	= 0;
	static const int default_dot4MiddleMinDistance	= 0;
	static const int default_dot4LargeMinDistance	= 0;
	static const int default_dot4SmallMaxDistance	= 20;
	static const int default_dot4MiddleMaxDistance	= 33;
	static const int default_dot4LargeMaxDistance	= 45;
	static const int default_dot4SmallDistance		= 37;
	static const int default_dot4MiddleDistance		= 60;
	static const int default_dot4LargeDistance		= 80;
	static const int default_dot4MinAngle			= 35;
	static const int default_dot4MaxAngle			= 55;
	static const int default_dot4CorrectMiddleDistance = 85;
	static const int default_dot4CorrectMiddleLoopCount = 5;

	// �S3�_
	static const int default_allDot3Angle				= 160;
	static const int default_allDot3SmallMinDistance	= 0;
	static const int default_allDot3MiddleMinDistance	= 0;
	static const int default_allDot3LargeMinDistance	= 0;
	static const int default_allDot3SmallMaxDistance	= 20;
	static const int default_allDot3MiddleMaxDistance	= 35;
	static const int default_allDot3LargeMaxDistance	= 50;

	// 6�̖�
	static const int default_dot6SmallDistance	= 20;
	static const int default_dot6MiddleDistance = 30;
	static const int default_dot6LargeDistance	= 50;
	static const int default_dot6SmallRadius	= 20;
	static const int default_dot6MiddleRadius	= 37;
	static const int default_dot6LargeRadius	= 60;

	// �F

private:

	/***************
	 *   �p�����[�^��`
	 */

	// �T�C�R���̃T�C�Y���ʂɎg�p����萔�Q
	int dotSmallMinSize;
	int dotSmallMaxSize;
	int dotMiddleMinSize;
	int dotMiddleMaxSize;
	int dotLargeMinSize;
	int dotLargeMaxSize;
	int dotNoneMinSize;
	int dotNoneMaxSize;
	int dot1MinSize;
	int dot1MaxSize;
	// double
	double dotCircleFilterPer;
	double dotCircleFilterRadiusPer;

	// 1�̖ڂ̒��o
	// double
	double dot1CircleFilterPer;
	double dot1CircleFilterRadiusPer;
	// �咆�T�C�R����1�̖ڂ̔��ʂɎg�p
	//	-> �אڂ���T�C�R���Ƃ̌���苗��
	int dot1LMDetectRadius;
	int dot1LMCorrectRadius;

	// �咆�T�C�R���Ɍ딻�肵�����T�C�R���̓_�C���̂��߂̔��a
	int correctMiddleRadius;
	int correctLargeRadius;
	int correctMiddleMaxSize;
	int correctLargeMinSize;

	// �������o���a
	int lineSmallRadius;
	int lineMiddleRadius;
	int lineLargeRadius;

	// �Q�̖ڌ��o�̔��a
	int dot2SmallMinDistance;
	int dot2MiddleMinDistance;
	int dot2LargeMinDistance;
	int dot2SmallMaxDistance;
	int dot2MiddleMaxDistance;
	int dot2LargeMaxDistance;
	int dot2SmallDistance;
	int dot2MiddleDistance;
	int dot2LargeDistance;
	int dot2MinAngle;
	int dot2MaxAngle;

	// �S�̖ڌ��o
	int dot4SmallMinDistance;
	int dot4MiddleMinDistance;
	int dot4LargeMinDistance;
	int dot4SmallMaxDistance;
	int dot4MiddleMaxDistance;
	int dot4LargeMaxDistance;
	int dot4SmallDistance;
	int dot4MiddleDistance;
	int dot4LargeDistance;
	int dot4MinAngle;
	int dot4MaxAngle;
	int dot4CorrectMiddleDistance;
	int dot4CorrectMiddleLoopCount;

	// �S3�_
	int allDot3Angle;
	int allDot3SmallMinDistance;
	int allDot3MiddleMinDistance;
	int allDot3LargeMinDistance;
	int allDot3SmallMaxDistance;
	int allDot3MiddleMaxDistance;
	int allDot3LargeMaxDistance;

	// 6�̖�
	int dot6SmallDistance;
	int dot6MiddleDistance;
	int dot6LargeDistance;
	int dot6SmallRadius;
	int dot6MiddleRadius;
	int dot6LargeRadius;

	// �F

protected:


	/***************
	 *   �N���X��`
	 */

	// �S�_�N���X
	class DotPoints{
	private:
		int num;
	public:
		std::vector<DotPoint> points;
		std::vector<short> flags;
		std::vector<DiceInfo::dtype> types;
		std::vector<int> kinds;
	public:

		DotPoints();

		void add(DotPoint dot,short flag,DiceInfo::dtype type,int kind);
		int size() const;
		void setKind(int kind,int number);

		void clear();

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
	class AllDot3Points{
	private:

		std::vector<Dot3Point> dot3s;
		int num;
	public:
		std::vector<short> flags;
		std::vector<DiceInfo::dtype> types;
		std::vector<int> kinds;
		std::vector<int> dotNums[3];
	
	public:

		AllDot3Points();

		void add(Dot3Point dot3,short flag,DiceInfo::dtype type,int kind,int dotNum1,int dotNum2,int dotNum3);
		int size() const;

		void clear();

		Dot3Point operator[](int i);

	};

	// ���S�_�Q�N���X
	class DotCenters{
	private:

		int num;

	public:
		
		vector<DotPoint> centers;
		
		vector<DiceInfo::dtype> types;
		vector<int> kinds;
		vector<int> numbers;

	public:

		DotCenters();

		void clear();

		void add(DotPoint center,DiceInfo::dtype type,int kind,int number);
		int size() const;

		DotPoint operator[](int i);

	};


	// �e�_�Q�N���X
	class Dot1Points{
	private:	
		
		int num;
		
		static const int smallSize = 300;
		static const int middleSize = 800;
		static const int largeSize = 900;

	public:
		
		vector<Dot1Point> dot1s;
		vector<int> pointNums;

	public:

		Dot1Points();

		void clear();
		void erase(int i);
		void add(Dot1Point dot1,int number);
		void add(DotPoint center,DiceInfo::dtype type);
		int size() const;

		Dot1Point operator[](int i);

	};

	class Dot2Points{
	private:
		int num;
		
		static const int smallSize = 90;
		static const int middleSize = 250;
		static const int largeSize = 380;
		static const int smallRadius = 12;
		static const int middleRadius = 17;
		static const int largeRadius = 23;

	public:
		vector<Dot2Point> dot2s;
		vector<int> pointNums[2];
	public:
		Dot2Points();

		void clear();
		void erase(int i);
		void add(Dot2Point dot2,int number1,int number2);
		void add(DotPoint center,DiceInfo::dtype type);
		int size() const;

		Dot2Point operator[](int i);
	};

	class Dot3Points{
	private:
		int num;
		
		static const int smallSize = 90;
		static const int middleSize = 250;
		static const int largeSize = 380;
		static const int smallRadius = 12;
		static const int middleRadius = 17;
		static const int largeRadius = 28;

	public:
		vector<Dot3Point> dot3s;
		vector<int> pointNums[3];
	public:
		Dot3Points();

		void clear();
		void erase(int i);
		void add(Dot3Point dot2,int number1
			,int number2
			,int number3);
		void add(DotPoint center,DiceInfo::dtype type);
		int size() const;

		Dot3Point operator[](int i);

	};

	class Dot4Points{
	private:
		int num;
		
		static const int smallSize = 90;
		static const int middleSize = 250;
		static const int largeSize = 380;
		static const int smallRadius = 12;
		static const int middleRadius = 17;
		static const int largeRadius = 25;

	public:
		vector<Dot4Point> dot4s;
		vector<int> pointNums[4];
	public:
		Dot4Points();

		void clear();
		void erase(int i);
		void add(Dot4Point dot4,int number1
			,int number2
			,int number3
			,int number4);
		void add(DotPoint center,DiceInfo::dtype type);
		int size() const;

		Dot4Point operator[](int i);

	};

	class Dot5Points{
	private:
		int num;
		
		static const int smallSize = 90;
		static const int middleSize = 250;
		static const int largeSize = 380;
		static const int smallRadius = 12;
		static const int middleRadius = 17;
		static const int largeRadius = 29;

	public:
		vector<Dot5Point> dot5s;
		vector<int> pointNums[5];
	public:
		Dot5Points();

		void clear();
		void erase(int i);
		void add(Dot5Point dot5,int number1
			,int number2
			,int number3
			,int number4
			,int number5);
		void add(DotPoint center,DiceInfo::dtype type);
		int size() const;

		Dot5Point operator[](int i);

	};

	class Dot6Points{
	private:
		int num;
		
		static const int smallSize = 90;
		static const int middleSize = 250;
		static const int largeSize = 380;
		static const int smallRadius = 12*2;
		static const int middleRadius = 20*2;
		static const int largeRadius = 33*2;

	public:
		vector<Dot6Point> dot6s;
		vector<int> pointNums[6];
	public:
		Dot6Points();

		void clear();
		void erase(int i);
		void add(Dot6Point dot6,int number1
			,int number2
			,int number3
			,int number4
			,int number5
			,int number6);
		void add(DotPoint center,DiceInfo::dtype type);
		int size() const;

		Dot6Point operator[](int i);

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
	AllDot3Points allDot3Points;

	// �T�C�R���̒��S���W
	DotCenters allDotCenters;

	// ���o�~�X�������������S���W
	DotCenters missDotCenters;

	// �T�C�R���̖ڃf�[�^
	Dot1Points dot1Points;
	//std::vector<Dot2Point> dot2Points;
	Dot2Points dot2Points;
	//std::vector<Dot3Point> dot3Points;
	Dot3Points dot3Points;
	//std::vector<Dot4Point> dot4Points;
	Dot4Points dot4Points;
	//std::vector<Dot5Point> dot5Points;
	Dot5Points dot5Points;
	//std::vector<Dot6Point> dot6Points;
	Dot6Points dot6Points;

	// �ݒ�t�@�C����
	string iniFileName;
	// �摜�f�B���N�g��
	Dir dir;
	// �摜�t�@�C����
	string name;

private:


	/***************
	 *   �֐���`
	 */

	// �K�v�v�f�̎擾
	void getAllPoints();
	void getAllLines();
	void getAllDot3Points();
	void getAllDotCenters();

	// �ڂ̔��菈��
	void getDot1Points();
	void getDot2Points();
	void getDot4Points();	// 124536�̏� 2���
	void _getDot4Points();	// 125364�̏� ����
	void getDot5Points();
	void getDot3Points();
	void getDot6Points();

	// �]��_����̌��o����
	void getOddPoints();

	// �폜����
	//void eraseDot1Points();
	
	// erase
	void eraseDot1Points(int i);
	void eraseTypeDot1Points(DiceInfo::dtype type);
	void eraseDot2Points(int i);
	void eraseTypeDot2Points(DiceInfo::dtype type);
	void eraseDot3Points(int i);
	void eraseTypeDot3Points(DiceInfo::dtype type);
	void eraseDot4Points(int i);
	void eraseTypeDot4Points(DiceInfo::dtype type);
	void eraseDot5Points(int i);
	void eraseTypeDot5Points(DiceInfo::dtype type);
	void eraseDot6Points(int i);
	void eraseTypeDot6Points(DiceInfo::dtype type);

	// clear
	void clearAll();
	void clearAllPoints();
	void clearAllLines();
	void clearAllDot3Points();
	void clearAllDotCenters();
	void clearDot1Points();
	void clearDot2Points();
	void clearDot3Points();
	void clearDot4Points();
	void clearDot5Points();
	void clearDot6Points();

	// set
	void setTypeDot1Points(DiceInfo::dtype type,int num);
	void setTypeDot2Points(DiceInfo::dtype type,int num);
	void setTypeDot3Points(DiceInfo::dtype type,int num);
	void setTypeDot4Points(DiceInfo::dtype type,int num);
	void setTypeDot5Points(DiceInfo::dtype type,int num);
	void setTypeDot6Points(DiceInfo::dtype type,int num);

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
	int getNumTrueAllPoints() const;
	int getNumFalseAllPoints() const;
	int getNumTypeAllPoints(DiceInfo::dtype type) const;
	int getNumKindAllPoints(int kind) const;
	int getNumAllLines() const;
	int getNumTrueAllLines() const;
	int getNumFalseAllLines() const;
	int getNumTypeAllLines(DiceInfo::dtype type) const;
	int getNumKindAllLines(int kind) const;
	int getNumAllDot3Points() const;
	int getNumTrueAllDot3Points() const;
	int getNumFalseAllDot3Points() const;
	int getNumTypeAllDot3Points(DiceInfo::dtype type) const;
	int getNumKindAllDot3Points(int kind) const;
	int getNumAllDotCenters() const;
	int getNumTypeAllDotCenters(DiceInfo::dtype type) const;
	int getNumKindAllDotCenters(int kind) const;
	int getNumDot1Points(DiceInfo::dtype type = DiceInfo::none) const;
	int getNumDot2Points(DiceInfo::dtype type = DiceInfo::none) const;
	int getNumDot3Points(DiceInfo::dtype type = DiceInfo::none) const;
	int getNumDot4Points(DiceInfo::dtype type = DiceInfo::none) const;
	int getNumDot5Points(DiceInfo::dtype type = DiceInfo::none) const;
	int getNumDot6Points(DiceInfo::dtype type = DiceInfo::none) const;

private:
	
	DiceInfo mode;
	int modeFlag; // 0:T 1:K 2:C 3:R
	//DiceInfo now_mouse;
	int centerNum;
	Image types,kinds;

	// �C�x���g�֘A
	void onMouse_impl(int event,int x,int y,int flag);
	int keyEvent(int key);

	void setMousePointCenter(int x,int y);
	void mouseCorrectType();
	void mouseCorrectKind();
	void mouseCreateKind();

	// ��]����
	Image rotato;
	double rotatoAngle;
	cv::Point2f rCenter;

	void rotationImage();
	int rotatoKeyEvent(int key);
	void mouseRotatoCenterPoint();
		
	// �ݒ�t�@�C���֘A
	void defaultIniFileCreate();
	void readIniFile();

	// �p�����[�^�֘A
	void setDefaultParam();

	// ���s�֘A����
	void drawRun();
	void drawMousePoint(Image& src,string winName);
	void outRun();
	void outEncode();

	// ���s�����֘A
	void run();
	
public:

	DiceDetection(void);
	~DiceDetection(void);

	// ������
	void init();
	void init(Dir dir,string name);

	// �`�ʑ��쏈��
	void drawing();
	void draw();

	// �O������̃L�[����
	void setMode(int key);

	// �O���փp�P�b�g����n��
	int getPacket() const;
	// �O���֌��݂̃��[�h��n��
	int getMode() const;
	// �O���֌��݂̃��[�h�̃T�C�R���̖ڂ�n��
	int getModeKind() const;
	// �O���֌��݂̃��[�h�̃T�C�R���̎�ނ�n��
	int getModeType() const;

	// �e�X�g�p
	void testRun();
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