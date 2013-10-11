#pragma once

#include"Procon2013\Core\Core.h"
#include"CharPositions.h"
#include"StringPositions.h"
#include"StringReverse.h"
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

	// 1•¶šˆ—
	void length1Matching();
	void length1SizeErase(int minSize);
	
	// ˆê•¶š˜A‘±ŒŸo
	void continuous1Matching();
	void continuous1LengthAndSizeErase(int length,int minSize);

	// 2•¶šˆ—
	void length2Matching(int minsize);

	// n•¶šˆ—
	void lengthMatching(int n,int minsize);

	// ”½“]•¶šŒŸo
	//void reverseLength2Matching(int minsize);
	//void reverseLengthMatching(int n,int minsize);

public:
	StringMatching(void);
	~StringMatching(void);

	void init(string name);

	void dips();

};

}