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

	// 元画像
	Image src;

	// 点群データ
	std::vector<DotPoint> allPoints;
	std::vector<short> ptFlags;
	std::vector<DiceInfo::dtype> ptTypes;
	int ptNum;
	
	// 線分データ
	std::vector<LineSegment> allLine;
	std::vector<short> lineFlags;
	int lineNum;
	int maxLineRadius;  // 線分認識の最長半径

	// サイコロの目データ
	std::vector<Dot1Point> dot1Points;
	std::vector<Dot2Point> dot2Points;
	std::vector<Dot3Point> dot3Points;


public:
	DiceDetection(void);
	~DiceDetection(void);

	// 初期化
	//void init(int num,std::vector<cv::Point2f> points,std::vector<int> sizes);
	//void init(LabelingCenter lc);
	void init(Image src);

	// 必要要素の取得
	void getAllPoints();
	void getAllLines(int maxRadius = 10);
	//void getAllDot3Points();

	// 目の判定処理
	void getDot1Points();

	// 削除処理
	void eraseDot1Points();

	// 描写
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