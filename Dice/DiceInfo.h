#pragma once

#include"Procon2013\Core\Core.h"

namespace pro{

// 整った形のサイコロ情報クラス
class PRO_EXPORTS DiceInfo
{
public:

	/**
	 *  型、定数宣言
	 */
	typedef enum dice_type{
		small,middle,large,none
	}dtype;

	// サイコロサイズ
	static const int DICE_S = 6;
	static const int DICE_M = 10;
	static const int DICE_L = 15;

	// 台フレームサイズ
	static const int FRAME_W = 150;
	static const int FRAME_H = 100;
	
	// フレーム内に収まる単体最大値
	static const int MAX_LW_NUM = 9;
	static const int MAX_LH_NUM = 6;
	static const int MAX_MW_NUM = 14;
	static const int MAX_MH_NUM = 10;
	static const int MAX_SW_NUM = 25; 
	static const int MAX_SH_NUM = 17; 

public:

	// 角度
	int angle;
	// 中心
	cv::Point center;
	// 大中小
	DiceInfo::dtype type;
	// 1～6
	int kind;

public:
	DiceInfo(void);
	~DiceInfo(void);

	void init(cv::Point center,int angle,DiceInfo::dtype type,int kind);

	static int getDiceSize(DiceInfo::dtype type);

	// フレーム内における数の最大値をそれぞれ算出
	static int getMToLWNum(int Lnum);
	//static int getLToMWNum(int Mnum);
	static int getSToMWNum(int Mnum);
	//static int getMToSWNum(int Snum);
	static int getMToLHNum(int Lnum);
	//static int getLToMHNum(int Mnum);
	static int getSToMHNum(int Mnum);
	//static int getMToSHNum(int Snum);


	bool equal(DiceInfo);

	bool operator()(DiceInfo di,DiceInfo n_di) const; 

};

}