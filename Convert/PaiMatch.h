#pragma once

#include"Procon2013/Core/Core.h"
#include<iostream>

#include"CharArray.h"
#include"CharArrayNumeric.h"
#include"InPaiDivide.h"

namespace pro{

class PRO_EXPORTS PaiMatch
{
private:

	int digits;			// マッチングする桁数
	int length;			// マッチングするときの文字列長さ
	int line_length;	// 文字列が跨ぐラインの長さ

	int char_num;		// 文字番号
	std::ifstream::pos_type pos;	// 開始位置

	long long unsigned count;			// 一致数カウント

	CharArray c_str;	// マッチ保存文字列
	CharArrayNumeric num_str; // 数値文字列

	InPaiDivide ipd;	// 円周率分割ファイルデータ取得クラス

	Dir path;
	std::fstream fs;
	std::fstream count_fs;

	bool load_flag;
	
	void setStr();
	void init();
	bool next();
	void open();
	void close();
	bool match();
	void matchOneLine();
	void output();
	void nowDisplay();
	void keyEvent();

	// 途中経過
	void save();
	void last_save();
	void load();

public:
	PaiMatch(int digits=1,CharArrayNumeric::NumKind kind=CharArrayNumeric::HEX);
	~PaiMatch(void);

	int getDigits() const;

	void matching();

};

}
