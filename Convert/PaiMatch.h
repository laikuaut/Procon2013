#pragma once

#include"Procon2013/Core/Core.h"
#include<iostream>

#include"CharArray.h"
#include"CharArrayNumeric.h"
#include"InPaiDivide.h"

namespace pro{

class PRO_EXPORTS PaiMatch
{
protected:

	int digits;						// マッチングする桁数

	int char_num;					// 文字番号
	std::ifstream::pos_type pos;	// 開始位置

	long long unsigned count;		// 一致数カウント

	CharArrayNumeric num_str;		// 数値文字列

	Dir path;						// ディレクトリパス
	std::fstream fs;				// 座標ファイルストリーム
	std::fstream count_fs;			// カウントファイルストリーム

	// 初期化関数
	virtual void init();	

	// 開く
	virtual void open() = 0;
	// 閉じる
	void close();					

	// 現在状況の表示
	virtual void nowDisplay() = 0;	
	// キーイベント関数
	virtual void keyEvent() = 0;	

public:
	PaiMatch(int digits=1,CharArrayNumeric::NumKind kind=CharArrayNumeric::HEX);
	~PaiMatch(void);

	// 桁数取得
	int getDigits() const;
	
};

}
