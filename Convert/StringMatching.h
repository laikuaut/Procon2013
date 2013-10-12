#pragma once

#include"Procon2013\Core\Core.h"
#include"CharPositions.h"
#include"StringPositions.h"
#include"Procon2013\Core\Timer.h"

namespace pro{

class StringMatching
{
private:

	vector<char> str;
	vector<CharPositions> charPositions;
	vector<vector<StringPositions>> strPositions;
	vector<StringPositions> continuousStrs;

	//	vector<vector<StringReverse>> strReverses;

	int getCharPositionsNumAtValue(char value);

	// 1文字処理
	void length1Matching();
	void length1SizeErase(int minSize);
	
	// 一文字連続検出
	void continuous1Matching();
	// length:文字列長さ minsize:文字列のポジション数
	void continuous1LengthAndSizeErase(int length,int minSize);

	// 2文字処理
	void length2Matching(int minsize);

	// n文字処理
	void lengthMatching(int n,int minsize);

	// fileRead
	void fileReadStr(string name);
	void fileReadDice(string name);



	// 反転文字検出
	//void reverseLength2Matching(int minsize);
	//void reverseLengthMatching(int n,int minsize);

public:
	StringMatching(void);
	~StringMatching(void);

	void init(string name,bool dice=false);
	void setchar(int dice);
	
	void matching(int n);

	void dipsStr(int n);
	void dipsDice(int n);

	vector<char> getStr() const;
	vector<CharPositions> getCharPositions() const;
	vector<vector<StringPositions>> getStrPositions() const;
	vector<StringPositions> getContinuousStrs() const;
};

}