#pragma once

#include"PaiMatch.h"

namespace pro{

class InPaiMatch : public PaiMatch
{
private:

	int dir_num;
	int file_num;
	int line_num;

	int flag_count;

	void init();		// 初期化関数

	void open();		// 開く
	void keyEvent(){}	// キーイベント関数

	void setDigits(int digits);

public:

	InPaiMatch(int digits=1, CharArrayNumeric::NumKind kind=CharArrayNumeric::HEX);
	~InPaiMatch(void);
	
	int getDirNum() const;
	int getFileNum() const;
	int getLineNum() const;
	int getCharNum() const;
	long long unsigned getCount() const;
	const char* getNumStr() const;
	
	bool setNum();
	bool setNum(const char* str);

	bool next();		// 次の要素にアクセス
	bool nextNum();		// 次の数値にアクセス

	void Reset();

	void nowDisplay();	// 現在状況の表示


};

}
