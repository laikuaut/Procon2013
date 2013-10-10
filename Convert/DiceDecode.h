#pragma once

#include"Procon2013\Core\Core.h"
#include"Procon2013\Dice\DiceDetection.h"

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

	void readIni();
	void addFile();

	void keyEvent();

	// Encode出力のパケット登録
	void packetRegist();
	void packetRegistDisplay();
	void packetDisplay();

	// デコードマージ
	void packetMarge();

	// モードや現在の番号表示
	void nowDisplay();

public:
	DiceDecode(void);
	~DiceDecode(void);

	void init();

	void drawing();
	void draw();

};

// パケットテキストをコンソールに表示する。


}