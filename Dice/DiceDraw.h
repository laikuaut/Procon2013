#pragma once

#include"Procon2013\Core\Core.h"
#include"Procon2013\ImageProcessing\ImageProssing.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include"DiceInfo.h"

namespace pro{
	
class PRO_EXPORTS DiceDraw : public MouseEvent
{
private:

	Image dst;
	Image base;

	int w,h;
	double rate;

	DiceInfo dice;
	
	vector<DiceInfo> dices;
	int dice_num;

	bool draw_flag;
	int label;

private:

	void onMouse_impl(int event,int x,int y,int flag);
	
	void draw(Image& src = Image(), bool clear = false);
	void keyEvent();

	void setPoint(int x,int y);
	void addDice(int x,int y);

public:
	DiceDraw(int rate=5);
	~DiceDraw(void);

	void init(int rate);
	
	void drawing();
	void allClear();
	void show();

	void addDice(cv::Point pt,int angle,DiceInfo::dtype type,int kind);
	void addDice(DiceInfo dinfo);

	void output();

};

/**
--ALL
L9*L6
M14*M10
S25*S17

--LMS
L8M2	* L5M2
L7M3S1	* L4M3S1
L6M5	* L3M5
L5M6S1	* L2M7
L4M8	* L1M8S1
L3M10	* 
L2M11S1	* 
L1M13	* 

--MSH
M9S2
M8S3
M7S5
M6S7
M5S8..9
M4S10
M3S12
M2S13
M1S15

MSW
M14S1
M13S3
M12S5
M11S6
M10S8
M9 S10
M8 S11
M7 S13
M6 S15
M5 S16
M4 S18
M3 S20
M2 S21
M1 S23

*/

}