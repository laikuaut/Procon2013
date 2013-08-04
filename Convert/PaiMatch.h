#pragma once

#include"Procon2013/Core/Core.h"
#include<iostream>

#include"CharArray.h"
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

	CharArray c_str;	// マッチ文字列
	InPaiDivide ipd;	// 円周率分割ファイルデータ取得クラス


public:
	PaiMatch(void);
	~PaiMatch(void);
};

}
