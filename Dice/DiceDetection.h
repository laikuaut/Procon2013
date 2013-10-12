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

// サイコロ判定クラス
class PRO_EXPORTS DiceDetection : public MouseEvent
{
private:

	/***************
	 *   パラメータデフォルト定数定義
	 */

	// サイコロのサイズ判別に使用する定数群
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

	// 1の目の抽出
	// double
	static const int default_dot1CircleFilterPer		= 1;
	static const int default_dot1CircleFilterRadiusPer	= 3;
	// 大中サイコロの1の目の判別に使用
	//	-> 隣接するサイコロとの交わり距離
	static const int default_dot1LMDetectRadius		= 73;
	static const int default_dot1LMCorrectRadius	= 90;

	// 大中サイコロに誤判定した中サイコロの点修正のための半径
	static const int default_correctMiddleRadius	= 30*3;
	static const int default_correctLargeRadius		= 50*3;
	static const int default_correctMiddleMaxSize	= 300;
	static const int default_correctLargeMinSize	= 230;

	// 線分検出半径
	static const int default_lineSmallRadius	= 40;
	static const int default_lineMiddleRadius	= 60;
	static const int default_lineLargeRadius	= 80;

	// ２の目検出の半径
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

	// ４の目検出
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

	// 全3点
	static const int default_allDot3Angle				= 160;
	static const int default_allDot3SmallMinDistance	= 0;
	static const int default_allDot3MiddleMinDistance	= 0;
	static const int default_allDot3LargeMinDistance	= 0;
	static const int default_allDot3SmallMaxDistance	= 20;
	static const int default_allDot3MiddleMaxDistance	= 35;
	static const int default_allDot3LargeMaxDistance	= 50;

	// 6の目
	static const int default_dot6SmallDistance	= 20;
	static const int default_dot6MiddleDistance = 30;
	static const int default_dot6LargeDistance	= 50;
	static const int default_dot6SmallRadius	= 20;
	static const int default_dot6MiddleRadius	= 37;
	static const int default_dot6LargeRadius	= 60;

	// 色

private:

	/***************
	 *   パラメータ定義
	 */

	// サイコロのサイズ判別に使用する定数群
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

	// 1の目の抽出
	// double
	double dot1CircleFilterPer;
	double dot1CircleFilterRadiusPer;
	// 大中サイコロの1の目の判別に使用
	//	-> 隣接するサイコロとの交わり距離
	int dot1LMDetectRadius;
	int dot1LMCorrectRadius;

	// 大中サイコロに誤判定した中サイコロの点修正のための半径
	int correctMiddleRadius;
	int correctLargeRadius;
	int correctMiddleMaxSize;
	int correctLargeMinSize;

	// 線分検出半径
	int lineSmallRadius;
	int lineMiddleRadius;
	int lineLargeRadius;

	// ２の目検出の半径
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

	// ４の目検出
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

	// 全3点
	int allDot3Angle;
	int allDot3SmallMinDistance;
	int allDot3MiddleMinDistance;
	int allDot3LargeMinDistance;
	int allDot3SmallMaxDistance;
	int allDot3MiddleMaxDistance;
	int allDot3LargeMaxDistance;

	// 6の目
	int dot6SmallDistance;
	int dot6MiddleDistance;
	int dot6LargeDistance;
	int dot6SmallRadius;
	int dot6MiddleRadius;
	int dot6LargeRadius;

	// 色

protected:


	/***************
	 *   クラス定義
	 */

	// 全点クラス
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

	// 全線クラス
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

	// 全3点直線クラス
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

	// 中心点群クラス
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


	// 各点群クラス
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
	 *   変数定義
	 */

	// 元画像
	Image src;

	// 点群データ
	DotPoints allPoints;

	// 線分データ
	LineSegments allLines;

	// 3点データ
	AllDot3Points allDot3Points;

	// サイコロの中心座標
	DotCenters allDotCenters;

	// 検出ミスが発生した中心座標
	DotCenters missDotCenters;

	// サイコロの目データ
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

	// 設定ファイル名
	string iniFileName;
	// 画像ディレクトリ
	Dir dir;
	// 画像ファイル名
	string name;

private:


	/***************
	 *   関数定義
	 */

	// 必要要素の取得
	void getAllPoints();
	void getAllLines();
	void getAllDot3Points();
	void getAllDotCenters();

	// 目の判定処理
	void getDot1Points();
	void getDot2Points();
	void getDot4Points();	// 124536の順 2回目
	void _getDot4Points();	// 125364の順 一回目
	void getDot5Points();
	void getDot3Points();
	void getDot6Points();

	// 余り点からの検出処理
	void getOddPoints();

	// 削除処理
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

	// 修正処理
	void correctPointType();
	int correctMiddleDot4Points(); //余り点から4の目の抽出ミスを訂正
	void correctOddMiddleToLarge();


	// 描写
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


	// 個数取得
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

	// イベント関連
	void onMouse_impl(int event,int x,int y,int flag);
	int keyEvent(int key);

	void setMousePointCenter(int x,int y);
	void mouseCorrectType();
	void mouseCorrectKind();
	void mouseCreateKind();

	// 回転処理
	Image rotato;
	double rotatoAngle;
	cv::Point2f rCenter;

	void rotationImage();
	int rotatoKeyEvent(int key);
	void mouseRotatoCenterPoint();
		
	// 設定ファイル関連
	void defaultIniFileCreate();
	void readIniFile();

	// パラメータ関連
	void setDefaultParam();

	// 実行関連処理
	void drawRun();
	void drawMousePoint(Image& src,string winName);
	void outRun();
	void outEncode();

	// 実行処理関連
	void run();
	
public:

	DiceDetection(void);
	~DiceDetection(void);

	// 初期化
	void init();
	void init(Dir dir,string name);

	// 描写操作処理
	void drawing();
	void draw();

	// 外部からのキー操作
	void setMode(int key);

	// 外部へパケット数を渡す
	int getPacket() const;
	// 外部へ現在のモードを渡す
	int getMode() const;
	// 外部へ現在のモードのサイコロの目を渡す
	int getModeKind() const;
	// 外部へ現在のモードのサイコロの種類を渡す
	int getModeType() const;

	// テスト用
	void testRun();
};

/**
 
 DiceDetection メモ
 作業手順
 １．全点取得:getAllPoints()
	1.1. 小中大の順番でサイズ指定（2段目に置かれた中サイコロと大サイコロの判別困難）
	1.2. 1の目の小サイコロはlargeに設定
	1.3. 1の目の中大サイコロはlargeに設定
 ２．１の目のサイコロ検出:getDot1Points()
	2.1. 赤色抽出から1の目座標取得
	2.2. 全点と座標比較、重なった点を全点においてfalse指定
	2.3. 小サイコロの1の目をlargeからsmallへ直す
	2.4. 周辺との座標の交わりから大中の1の目判別
 ３．サイズ判定修正:correctPointType()
	3.1. 2段目に置いた中サイコロを大サイコロのサイズと誤判定
	3.2. 周辺にあるサイズの点の数を比べることで修正
 ４．全線分取得:getAllLines()
	4.1. サイコロのサイズごとに線分を描く
	4.2. 独立した点を削除(none)
 ５．2の目の認識
	5.1. 線分のサイズから2の目を含まない線分を抽出
	5.2. 先に抽出した線分に使用されていない点を2の目の点候補とする
	5.3. 角度と距離から2の目を決定
 */

}