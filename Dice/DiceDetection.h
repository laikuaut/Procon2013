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

// サイコロ判定クラス
class DiceDetection
{
private:

	/***************
	 *   定数定義
	 */

	// サイコロのサイズ判別に使用する定数群
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

	// 大中サイコロの1の目の判別に使用
	//	-> 隣接するサイコロとの交わり距離
	static const int dot1LMDetectRadius = 70;
	static const int dot1LMCorrectRadius = 80;

	// 大中サイコロに誤判定した中サイコロの点修正のための半径
	static const int correctMiddleRadius = 30*2;
	static const int correctLargeRadius = 50*2;
	static const int correctMiddleMaxSize = 500;
	static const int correctLargeMinSize = 250;

	// 線分検出半径
	static const int lineSmallRadius = 40;
	static const int lineMiddleRadius = 55;
	static const int lineLargeRadius = 70;

	// ２の目検出の半径
	static const int dot2SmallMinDistance = 0;
	static const int dot2MiddleMinDistance = 0;
	static const int dot2LargeMinDistance = 0;
	static const int dot2SmallMaxDistance = 23;
	static const int dot2MiddleMaxDistance = 40;
	static const int dot2LargeMaxDistance = 55;
	static const int dot2SmallDistance = 35;
	static const int dot2MiddleDistance = 55;
	static const int dot2LargeDistance = 70;

	// ４の目検出
	static const int dot4SmallMinDistance = 0;
	static const int dot4MiddleMinDistance = 0;
	static const int dot4LargeMinDistance = 0;
	static const int dot4SmallMaxDistance = 20;
	static const int dot4MiddleMaxDistance = 30;
	static const int dot4LargeMaxDistance = 45;
	static const int dot4SmallDistance = 37;
	static const int dot4MiddleDistance = 55;
	static const int dot4LargeDistance = 80;

	// 全3点
	static const int allDot3Angle = 160;
	static const int allDot3SmallMinDistance = 0;
	static const int allDot3MiddleMinDistance = 0;
	static const int allDot3LargeMinDistance = 0;
	static const int allDot3SmallMaxDistance = 20;
	static const int allDot3MiddleMaxDistance = 30;
	static const int allDot3LargeMaxDistance = 60;

	// 6の目
	static const int dot6SmallRasius = 20;
	static const int dot6MiddleRasius = 40;
	static const int dot6LargeRasius = 60;

protected:


	/***************
	 *   クラス定義
	 */

	// 全点クラス
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
	Dot3Points allDot3Points;

	// サイコロの目データ
	std::vector<Dot1Point> dot1Points;
	std::vector<Dot2Point> dot2Points;
	std::vector<Dot3Point> dot3Points;
	std::vector<Dot4Point> dot4Points;
	std::vector<Dot5Point> dot5Points;
	std::vector<Dot6Point> dot6Points;

public:


	/***************
	 *   関数定義
	 */

	DiceDetection(void);
	~DiceDetection(void);

	// 初期化
	//void init(int num,std::vector<cv::Point2f> points,std::vector<int> sizes);
	//void init(LabelingCenter lc);
	void init(Image src);

	// 必要要素の取得
	void getAllPoints();
	void getAllLines();
	void getAllDot3Points();

	// 目の判定処理
	void getDot1Points();
	void getDot2Points();
	void getDot4Points();
	void getDot5Points();
	void getDot3Points();
	void getDot6Points();

	// 削除処理
	void eraseDot1Points();
	void clearAllLines();

	// 修正処理
	void correctPointType();

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