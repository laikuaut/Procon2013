#pragma once

#include"Procon2013\Core\Core.h"

#include"DiceDraw.h"
#include<fstream>

namespace pro{

class DiceEncode : public DiceDraw
{
private:
	vector<DiceDraw> diceDraws;
	
	vector<int> kinds;
	int now;
	int packetNum;
	int watch_num;
	int pattern;

	void onMouse_impl(int event,int x,int y,int flag);
	void keyEvent();
	int nowPacketDiceNum();
	void nextPacket(int num=-1);


	void createPacket();
	void reCreatePacket(int pat);
	// L6*6 M9*4
	void createPacketPattern01(int &x,int &y);
	// L6*8
	void createPacketPattern02(int &x,int &y);
	// M9*10
	void createPacketPattern03(int &x,int &y);

	void backPacket();


public:
	DiceEncode(void);
	~DiceEncode(void);

	void init(string name);
	void drawing();	

};

}