#pragma once

#include"Procon2013\Core\Core.h"
#include"Procon2013\ImageProcessing\ImageProssing.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>

namespace pro{
	
class PRO_EXPORTS DiceDraw : public MouseEvent
{
private:
	
	typedef enum dice_type{
		small,middle,large
	}dtype;

	// サイコロサイズ
	const int DISE_S;
	const int DISE_M;
	const int DISE_L;

	// 台フレームサイズ
	const int FRAME_W;
	const int FRAME_H;


private:

	Image dst;
	Image base;

	int w,h;
	double rate;
	cv::Point mp;
	int angle;

	int kind; // 1～6
	dtype type;
	
	void init();

	void onMouse_impl(int event,int x,int y,int flag);
	
	void draw(Image& src);
	void keyEvent();
public:
	DiceDraw(int rate);
	~DiceDraw(void);
	
	void drawing();

};

}