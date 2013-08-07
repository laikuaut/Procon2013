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
	int line_num;		// ライン番号
	int file_num;		// ファイル番号
	int dir_num;		// ディレクトリ番号

	long count;

	CharArray c_str;	// マッチ保存文字列
	CharArrayNumeric num_str; // 数値文字列

	InPaiDivide ipd;	// 円周率分割ファイルデータ取得クラス

	std::fstream fs;
	std::fstream count_fs;
	
	void setStr();

	void init();
	bool next();

	bool match();

	void matchOneLine();

	void output();

public:
	PaiMatch(void);
	~PaiMatch(void);

	void matching();

};

}
