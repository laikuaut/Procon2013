#include "Dice.h"

#include<iostream>

using namespace std;

namespace pro{

Dice::Dice(void)
{
}


Dice::~Dice(void)
{
}

int Dice::diceKindMatching(string ans,string src){

	// マッチング処理
	int count=0;
	vector<int> ans_kinds,kinds;
	std::ifstream ans_ifs,ifs;
	int kind;

	ans_ifs.open(ans);
	ifs.open(src);
	
	ans_ifs >> kind;
	do{
		ans_kinds.push_back(kind);
		ifs >> kind;
		kinds.push_back(kind);
		if(ans_kinds[count]!=kinds[count]) break;
		count++;
		ans_ifs >> kind;
	}while(!ans_ifs.eof());

	ans_ifs.close();
	ifs.close();

	return count;


}

}