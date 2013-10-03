#pragma once

#include"Procon2013\Core\Core.h"
#include"DotPoint.h"
#include"LineSegment.h"
#include"Dot3Point.h"
#include"DiceInfo.h"

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
	static const int dot2LargeMaxDistance = 58;
	static const int dot2SmallDistance = 35;
	static const int dot2MiddleDistance = 55;
	static const int dot2LargeDistance = 70;

protected:


	/***************
	 *   クラス定義
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
	 *   変数定義
	 */

	// 元画像
	Image src;

	// 点群データ
	//std::vector<DotPoint> allPoints;
	//std::vector<short> ptFlags;
	//std::vector<DiceInfo::dtype> ptTypes;
	//std::vector<int> ptKinds;
	//int ptNum;
	DotPoints allPoints;

	// 線分データ
	//std::vector<LineSegment> allLine;
	//std::vector<short> lineFlags;
	//int lineNum;
	//int maxLineRadius;  // 線分認識の最長半径
	LineSegments allLines;


	// サイコロの目データ
	std::vector<Dot1Point> dot1Points;
	std::vector<Dot2Point> dot2Points;
	std::vector<Dot3Point> dot3Points;


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
	//void getAllDot3Points();

	// 目の判定処理
	void getDot1Points();
	void getDot2Points();

	// 削除処理
	void eraseDot1Points();

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
 
 */

}