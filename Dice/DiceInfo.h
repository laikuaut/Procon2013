#pragma once

#include"Procon2013\Core\Core.h"

namespace pro{

// �������`�̃T�C�R�����N���X
class PRO_EXPORTS DiceInfo
{
public:

	/**
	 *  �^�A�萔�錾
	 */
	typedef enum dice_type{
		small,middle,large,none
	}dtype;

	// �T�C�R���T�C�Y
	static const int DICE_S = 6;
	static const int DICE_M = 10;
	static const int DICE_L = 15;

	// ��t���[���T�C�Y
	static const int FRAME_W = 150;
	static const int FRAME_H = 100;
	
	// �t���[�����Ɏ��܂�P�̍ő�l
	static const int MAX_LW_NUM = 9;
	static const int MAX_LH_NUM = 6;
	static const int MAX_MW_NUM = 14;
	static const int MAX_MH_NUM = 10;
	static const int MAX_SW_NUM = 25; 
	static const int MAX_SH_NUM = 17; 

public:

	// �p�x
	int angle;
	// ���S
	cv::Point center;
	// �咆��
	DiceInfo::dtype type;
	// 1�`6
	int kind;

public:
	DiceInfo(void);
	~DiceInfo(void);

	void init(cv::Point center,int angle,DiceInfo::dtype type,int kind);

	static int getDiceSize(DiceInfo::dtype type);

	// �t���[�����ɂ����鐔�̍ő�l�����ꂼ��Z�o
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