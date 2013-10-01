#pragma once

#include"Procon2013\Core\Core.h"
#include"Dot1Point.h"
#include"Procon2013\ImageProcessing\LabelingCenter.h"

namespace pro{

// サイコロ判定クラス
class DiceDetection
{
private:

	// 点データ
	std::vector<cv::Point2f> points;
	std::vector<int> sizes;
	std::vector<short> flags;
	int num;

	// サイコロの目データ
	std::vector<Dot1Point> dot1points;

public:
	DiceDetection(void);
	~DiceDetection(void);

	// 初期化
	void init(int num,std::vector<cv::Point2f> points,std::vector<int> sizes);
	void init(LabelingCenter lc);

	// 目判定処理


	// 削除処理


	// 描写
	void drawAllPoints(Image& img,cv::Scalar scal = cv::Scalar::all(0));
	//void drawDot1Points(Image img,cv::Scalar scal = cv::Scalar::all(0));
	
	// 

};

}