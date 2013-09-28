#include "DiceDraw.h"

namespace pro{

DiceDraw::DiceDraw(int rate) : 
	DISE_S(6),DISE_M(10),DISE_L(15),FRAME_W(150),FRAME_H(100)
{
	w = rate * FRAME_W;
	h = rate * FRAME_H;
	base.init(w,h);
	base.oneColor(cv::Scalar::all(255));

	this->rate = rate;

	kind = 1;
	type = small;
	angle=0;
}

DiceDraw::~DiceDraw(void)
{

}

void DiceDraw::draw(Image& src = Image()){
	if(src.empty()) src = base;
	int ds,dm,dl;
	int radius;
	cv::Scalar red(0,0,255),black(0,0,0);
	ds = DISE_S*rate;
	dm = DISE_M*rate;
	dl = DISE_L*rate;

	double c=cos(15.*CV_PI/180.),s=sin(15.*CV_PI/180.);

	switch (type)
	{
	case small:
		src.rectangle(cv::Point(mp.x,mp.y),ds,ds,angle,black);

		radius = rate/5*2;
		switch (kind)
		{
		case 1:
			src.circle(cv::Point(mp.x,mp.y),rate,red);
			break;
		case 2:
			src.circle(mp + Calc::PointRotate(ds/4,ds/4,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(-ds/4,-ds/4,angle) , radius ,black);
			break;
		case 3:
			src.circle(cv::Point(mp.x,mp.y),radius,black);
			src.circle(mp + Calc::PointRotate(ds/4,ds/4,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(-ds/4,-ds/4,angle) , radius ,black);
			break;
		case 4:
			src.circle(mp + Calc::PointRotate(ds/4,ds/4,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(-ds/4,-ds/4,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(ds/4,-ds/4,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(-ds/4,ds/4,angle) , radius ,black);
			break;
		case 5:
			src.circle(cv::Point(mp.x,mp.y),radius,black);
			src.circle(mp + Calc::PointRotate(ds/4,ds/4,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(-ds/4,-ds/4,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(ds/4,-ds/4,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(-ds/4,ds/4,angle) , radius ,black);
			break;
		case 6:
			src.circle(mp + Calc::PointRotate(ds/5,ds/4,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(ds/5,0,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(ds/5,-ds/4,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(-ds/5,ds/4,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(-ds/5,0,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(-ds/5,-ds/4,angle) , radius ,black);
			break;
		default:
			break;
		}
		break;
	case middle:
		src.rectangle(cv::Point(mp.x,mp.y),dm,dm,angle,black);
		radius = rate/5*4;
		switch (kind)
		{
		case 1:
			src.circle(cv::Point(mp.x,mp.y),rate*2,red);
			break;
		case 2:
			src.circle(mp + Calc::PointRotate(dm/4,dm/4,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(-dm/4,-dm/4,angle) , radius ,black);
			break;
		case 3:
			src.circle(cv::Point(mp.x,mp.y),radius,black);
			src.circle(mp + Calc::PointRotate(dm/4,dm/4,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(-dm/4,-dm/4,angle) , radius ,black);
			break;
		case 4:
			src.circle(mp + Calc::PointRotate(dm/4,dm/4,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(-dm/4,-dm/4,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(dm/4,-dm/4,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(-dm/4,dm/4,angle) , radius ,black);
			break;
		case 5:
			src.circle(cv::Point(mp.x,mp.y),radius,black);
			src.circle(mp + Calc::PointRotate(dm/4,dm/4,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(-dm/4,-dm/4,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(dm/4,-dm/4,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(-dm/4,dm/4,angle) , radius ,black);
			break;
		case 6:
			src.circle(mp + Calc::PointRotate(dm/5,dm/3,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(dm/5,0,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(dm/5,-dm/3,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(-dm/5,dm/3,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(-dm/5,0,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(-dm/5,-dm/3,angle) , radius ,black);
			break;
		default:
			break;
		}
		break;

	case large:
		src.rectangle(cv::Point(mp.x,mp.y),dl,dl,angle,black);
		radius = rate;
		switch (kind)
		{
		case 1:
			src.circle(cv::Point(mp.x,mp.y),rate*2,red);
			break;
		case 2:
			src.circle(mp + Calc::PointRotate(dl/5,dl/5,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(-dl/5,-dl/5,angle) , radius ,black);
			break;
		case 3:
			src.circle(cv::Point(mp.x,mp.y),radius,black);
			src.circle(mp + Calc::PointRotate(dl/4,dl/4,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(-dl/4,-dl/4,angle) , radius ,black);
			break;
		case 4:
			src.circle(mp + Calc::PointRotate(dl/5,dl/5,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(-dl/5,-dl/5,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(dl/5,-dl/5,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(-dl/5,+dl/5,angle) , radius ,black);
			break;
		case 5:
			src.circle(cv::Point(mp.x,mp.y),radius,black);
			src.circle(mp + Calc::PointRotate(dl/4,dl/4,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(-dl/4,-dl/4,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(dl/4,-dl/4,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(-dl/4,+dl/4,angle) , radius ,black);
			break;
		case 6:
			src.circle(mp + Calc::PointRotate(dl/5,dl/4,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(dl/5,0,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(dl/5,-dl/4,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(-dl/5,dl/4,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(-dl/5,0,angle) , radius ,black);
			src.circle(mp + Calc::PointRotate(-dl/5,-dl/4,angle) , radius ,black);
			break;
		default:
			break;
		}
	
		break;
	default:
		break;
	}

}

void DiceDraw::drawing(){

	cv::namedWindow("drawing", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);

	while(1){
		// Windowの生存確認
		void* life = cvGetWindowHandle("drawing");
		if(life == NULL) break;

		base.imshow("drawing");

		dst.clone(base);
		draw(dst);
		dst.imshow("drawing");

		// キーボードイベント
		keyEvent();
		// マウスイベントに対するコールバック関数を登録
		cv::setMouseCallback("drawing", onMouse, this);
	}
}

void DiceDraw::keyEvent(){
	int key=cv::waitKey(30);
	switch (key)
	{
	case '1':
		kind = 1;
		break;
	case '2':
		kind = 2;
		break;
	case '3':
		kind = 3;
		break;
	case '4':
		kind = 4;
		break;
	case '5':
		kind = 5;
		break;
	case '6':
		kind = 6;
		break;
	case 's':
		type = small;
		break;
	case 'm':
		type = middle;
		break;
	case 'l':
		type = large;
		break;
	case 2424832: // ←
		angle += 15;
		if(angle==360) angle = 0;
		std::cout<<angle<<std::endl;
		break;
	case 2555904: // →
		angle -= 15;
		if(angle==-360) angle = 0;
		std::cout<<angle<<std::endl;
		break;
	case 'c':
		base.oneColor(cv::Scalar::all(255));
		break;
	case 'q':
		cv::destroyWindow("drawing");
		break;
	default:
		//std::cout<<key<<std::endl;
		break;
	}
}

void DiceDraw::onMouse_impl(int event, int x, int y, int flag){
	std::string desc;
	// マウスイベントを取得
	switch(event) {
	case cv::EVENT_MOUSEMOVE:
		desc += "MOUSE_MOVE";
		mp.x = x;
		mp.y = y;
		break;
	case cv::EVENT_LBUTTONDOWN:
		desc += "LBUTTON_DOWN";
		draw();
		break;
	//case cv::EVENT_RBUTTONDOWN:
	//	desc += "RBUTTON_DOWN";
	//	break;
	//case cv::EVENT_MBUTTONDOWN:
	//	desc += "MBUTTON_DOWN";
	//	break;
	//case cv::EVENT_LBUTTONUP:
	//	desc += "LBUTTON_UP";
	//	break;
	//case cv::EVENT_RBUTTONUP:
	//	desc += "RBUTTON_UP";
	//	break;
	//case cv::EVENT_MBUTTONUP:
	//	desc += "MBUTTON_UP";
	//	break;
	//case cv::EVENT_LBUTTONDBLCLK:
	//	desc += "LBUTTON_DBLCLK";
	//	break;
	//case cv::EVENT_RBUTTONDBLCLK:
	//	desc += "RBUTTON_DBLCLK";
	//	break;
	//case cv::EVENT_MBUTTONDBLCLK:
	//	desc += "MBUTTON_DBLCLK";
	//	break;
	}

	// マウスボタン，及び修飾キーを取得
	//if(flag & cv::EVENT_FLAG_LBUTTON)
	//	desc += " + LBUTTON";
	//if(flag & cv::EVENT_FLAG_RBUTTON)
	//	desc += " + RBUTTON";
	//if(flag & cv::EVENT_FLAG_MBUTTON)
	//	desc += " + MBUTTON";
	//if(flag & cv::EVENT_FLAG_CTRLKEY)
	//	desc += " + CTRL";
	//if(flag & cv::EVENT_FLAG_SHIFTKEY)
	//	desc += " + SHIFT";
	//if(flag & cv::EVENT_FLAG_ALTKEY)
	//	desc += " + ALT";

	//std::cout << desc << " (" << x << ", " << y << ")" << std::endl;
}

}