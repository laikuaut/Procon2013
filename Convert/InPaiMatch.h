#pragma once

#include"PaiMatch.h"

namespace pro{

class InPaiMatch : public PaiMatch
{
private:

	int dir_num;
	int file_num;
	int line_num;

	void init();		// 初期化関数

	void open();		// 開く
	void nowDisplay(){}	// 現在状況の表示
	void keyEvent(){}	// キーイベント関数

	void setCount();

public:
	
	int getDirNum() const;
	int getFileNum() const;
	int getLineNum() const;
	int getCharNum() const;
	int getCount() const;
	
	void setNum(const char* str);

	bool next();		// 次の数値にアクセス

	InPaiMatch(void);
	~InPaiMatch(void);

};

}
