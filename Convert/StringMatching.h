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

	// 1��������
	void length1Matching();
	void length1SizeErase(int minSize);
	
	// �ꕶ���A�����o
	void continuous1Matching();
	// length:�����񒷂� minsize:������̃|�W�V������
	void continuous1LengthAndSizeErase(int length,int minSize);

	// 2��������
	void length2Matching(int minsize);

	// n��������
	void lengthMatching(int n,int minsize);

	// fileRead
	void fileReadStr(string name);
	void fileReadDice(string name);



	// ���]�������o
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