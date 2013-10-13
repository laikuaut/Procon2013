#pragma once

#include"Procon2013\Core\Core.h"
#include"Procon2013\Dice\DiceDetection.h"
#include"DiceCodeDecode.h"
#include"CodeDecode.h"
#include"SenaryDecode.h"
//#include<Windows.h>

namespace pro{

class DiceDecode
{
private:

	vector<DiceDetection> diceDetections;
	vector<string> names;
	Dir dir;
	int now;
	int num;
	vector<int> outPacketNums;

	DiceCodeDecode diceCodeDecode;
	CodeDecode codeDecode;
	SenaryDecode senaryDecode;

	// タイマー機能
	int interval;

private:

	void readIni();
	void addFile();

	int keyEvent();

	// Encode出力のパケット登録
	void packetRegist();
	void packetRegistDisplay();
	void packetDisplay();

	// デコードマージ
	void packetMarge();

	// モードや現在の番号表示
	void nowDisplay();


	// 文字列出力
	void output();

	void send();

public:
	DiceDecode(void);
	~DiceDecode(void);

	void init();

	void drawing();
	void draw();

};

// パケットテキストをコンソールに表示する。


}