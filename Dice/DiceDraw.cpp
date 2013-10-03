#include "DiceDraw.h"

namespace pro{

DiceDraw::DiceDraw(int rate)// : 
	//DICE_S(6),DICE_M(10),DICE_L(15),FRAME_W(150),FRAME_H(100)
{
	init(rate);
}

DiceDraw::~DiceDraw(void)
{

}


void DiceDraw::init(int rate){
	w = rate * DiceInfo::FRAME_W;
	h = rate * DiceInfo::FRAME_H;
	base.init(w,h);
	base.oneColor(cv::Scalar::all(255));

	this->rate = rate;

	dice.kind = 1;
	dice.type = DiceInfo::small;
	dice.angle=0;

	dice_num=0;

	draw_flag = true;
	label = -1;

}

void DiceDraw::draw(Image& src, bool clear){
	if(src.empty()) src = base;
	int ds,dm,dl;
	int radius;
	int rate;
	rate = this->rate;
	cv::Scalar red(0,0,255),black(0,0,0);
	ds = DiceInfo::DICE_S*rate;
	dm = DiceInfo::DICE_M*rate;
	dl = DiceInfo::DICE_L*rate;

	DiceInfo n_dice;
	n_dice = dice;

	// サイコロ削除処理
	if(clear){
		if(label == -1) return;
		red = cv::Scalar::all(255);
		black = cv::Scalar::all(255);
		n_dice = dices[label];
		vector<DiceInfo>::iterator it = dices.begin();
		for(it = dices.begin(); it != dices.end(); ++it){
			if(it->equal(n_dice)){
				dices.erase(it);
				break;
			}
		}
		dice_num--;
		label = -1;
		rate*=1.5;
	}

	// 描写処理
	switch (n_dice.type)
	{

	case DiceInfo::small: // 小サイコロの描写処理
		src.rectangle(n_dice.center,ds,ds,n_dice.angle,black,1);

		radius = rate/5*2;
		switch (n_dice.kind)
		{
		case 1:
			src.circle(n_dice.center,rate,red);
			break;
		case 2:
			src.circle(n_dice.center + Calc::PointRotate(ds/4,ds/4,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(-ds/4,-ds/4,n_dice.angle) , radius ,black);
			break;
		case 3:
			src.circle(n_dice.center,radius,black);
			src.circle(n_dice.center + Calc::PointRotate(ds/4,ds/4,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(-ds/4,-ds/4,n_dice.angle) , radius ,black);
			break;
		case 4:
			src.circle(n_dice.center + Calc::PointRotate(ds/4,ds/4,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(-ds/4,-ds/4,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(ds/4,-ds/4,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(-ds/4,ds/4,n_dice.angle) , radius ,black);
			break;
		case 5:
			src.circle(n_dice.center,radius,black);
			src.circle(n_dice.center + Calc::PointRotate(ds/4,ds/4,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(-ds/4,-ds/4,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(ds/4,-ds/4,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(-ds/4,ds/4,n_dice.angle) , radius ,black);
			break;
		case 6:
			src.circle(n_dice.center + Calc::PointRotate(ds/5,ds/4,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(ds/5,0,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(ds/5,-ds/4,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(-ds/5,ds/4,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(-ds/5,0,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(-ds/5,-ds/4,n_dice.angle) , radius ,black);
			break;
		default:
			break;
		}
		break;

	case DiceInfo::middle: // 中サイコロの描写処理
		src.rectangle(n_dice.center,dm,dm,n_dice.angle,black,2);
		radius = rate/5*4;
		switch (n_dice.kind)
		{
		case 1:
			src.circle(n_dice.center,rate*2,red);
			break;
		case 2:
			src.circle(n_dice.center + Calc::PointRotate(dm/4,dm/4,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(-dm/4,-dm/4,n_dice.angle) , radius ,black);
			break;
		case 3:
			src.circle(n_dice.center,radius,black);
			src.circle(n_dice.center + Calc::PointRotate(dm/4,dm/4,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(-dm/4,-dm/4,n_dice.angle) , radius ,black);
			break;
		case 4:
			src.circle(n_dice.center + Calc::PointRotate(dm/4,dm/4,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(-dm/4,-dm/4,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(dm/4,-dm/4,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(-dm/4,dm/4,n_dice.angle) , radius ,black);
			break;
		case 5:
			src.circle(n_dice.center,radius,black);
			src.circle(n_dice.center + Calc::PointRotate(dm/4,dm/4,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(-dm/4,-dm/4,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(dm/4,-dm/4,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(-dm/4,dm/4,n_dice.angle) , radius ,black);
			break;
		case 6:
			src.circle(n_dice.center + Calc::PointRotate(dm/5,dm/3,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(dm/5,0,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(dm/5,-dm/3,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(-dm/5,dm/3,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(-dm/5,0,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(-dm/5,-dm/3,n_dice.angle) , radius ,black);
			break;
		default:
			break;
		}
		break;

	case DiceInfo::large: // 大サイコロの描写処理
		src.rectangle(n_dice.center,dl,dl,n_dice.angle,black,2);
		radius = rate;
		switch (n_dice.kind)
		{
		case 1:
			src.circle(n_dice.center,rate*2,red);
			break;
		case 2:
			src.circle(n_dice.center + Calc::PointRotate(dl/5,dl/5,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(-dl/5,-dl/5,n_dice.angle) , radius ,black);
			break;
		case 3:
			src.circle(n_dice.center,radius,black);
			src.circle(n_dice.center + Calc::PointRotate(dl/4,dl/4,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(-dl/4,-dl/4,n_dice.angle) , radius ,black);
			break;
		case 4:
			src.circle(n_dice.center + Calc::PointRotate(dl/5,dl/5,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(-dl/5,-dl/5,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(dl/5,-dl/5,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(-dl/5,+dl/5,n_dice.angle) , radius ,black);
			break;
		case 5:
			src.circle(n_dice.center,radius,black);
			src.circle(n_dice.center + Calc::PointRotate(dl/4,dl/4,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(-dl/4,-dl/4,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(dl/4,-dl/4,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(-dl/4,+dl/4,n_dice.angle) , radius ,black);
			break;
		case 6:
			src.circle(n_dice.center + Calc::PointRotate(dl/5,dl/4,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(dl/5,0,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(dl/5,-dl/4,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(-dl/5,dl/4,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(-dl/5,0,n_dice.angle) , radius ,black);
			src.circle(n_dice.center + Calc::PointRotate(-dl/5,-dl/4,n_dice.angle) , radius ,black);
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

void DiceDraw::allClear(){
	dices.clear();
	dice_num=0;
	label = -1;
	base.oneColor(cv::Scalar::all(255));
}

void DiceDraw::show(){
	cv::namedWindow("DiceDraw", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
	base.imshow("DiceDraw");
}

void DiceDraw::keyEvent(){
	int key=cv::waitKey(30);
	switch (key)
	{
	case '1':
		dice.kind = 1;
		break;
	case '2':
		dice.kind = 2;
		break;
	case '3':
		dice.kind = 3;
		break;
	case '4':
		dice.kind = 4;
		break;
	case '5':
		dice.kind = 5;
		break;
	case '6':
		dice.kind = 6;
		break;
	case 's':
		dice.type = DiceInfo::small;
		break;
	case 'm':
		dice.type = DiceInfo::middle;
		break;
	case 'l':
		dice.type = DiceInfo::large;
		break;
	case 2424832: // [←]
		dice.angle += 15;
		if(dice.angle==360) dice.angle = 0;
		break;
	case 2555904: // [→]
		dice.angle -= 15;
		if(dice.angle==-15) dice.angle = 345;
		break;
	case 'c':
		allClear();
		//base.oneColor(cv::Scalar::all(255));
		break;
	case 'q':
		cv::destroyWindow("drawing");
		break;
	default:
		//std::cout<<key<<std::endl;
		break;
	}
}

void DiceDraw::setPoint(int x,int y){
	int radius;
	
	draw_flag = true;
	label = -1;
	for(int i=0;i<dice_num;i++){
		radius = DiceInfo::getDiceSize(dice.type);
		if(radius < DiceInfo::getDiceSize(dices[i].type))
			radius = DiceInfo::getDiceSize(dices[i].type);
		radius *= rate/2;
		//if( pow(dices[i].center.x - x,2) +  pow(dices[i].center.y - y,2) < pow(radius,2) ){
		if(Calc::getDistance2(dices[i].center,cv::Point2f(x,y)) < pow(radius,2) ){
			x = dices[i].center.x;
			y = dices[i].center.y;
			draw_flag = false;
			label = i;
			break;
		}
	}

	dice.center.x = x;
	dice.center.y = y;
}

void DiceDraw::addDice(int x,int y){
	setPoint(x,y);
	if(draw_flag){
		draw();
		dices.push_back(dice);
		dice_num++;
	}
}
	
void DiceDraw::addDice(cv::Point pt,int angle,DiceInfo::dtype type,int kind){
	DiceInfo dinfo;
	dinfo.init(pt,angle,type,kind);
	addDice(dinfo);
}

void DiceDraw::addDice(DiceInfo dinfo){
	dice.angle = dinfo.angle;
	dice.type = dinfo.type;
	dice.kind = dinfo.kind;
	addDice(dinfo.center.x*rate,dinfo.center.y*rate);
}


void DiceDraw::onMouse_impl(int event, int x, int y, int flag){
	//std::string desc;
	// マウスイベントを取得
	switch(event) {
	case cv::EVENT_MOUSEMOVE:
		setPoint(x,y);
		break;
	case cv::EVENT_LBUTTONDOWN:
		// SHIFTを押したときの処理(上書き)
		if(flag & cv::EVENT_FLAG_SHIFTKEY){
			draw(Image(),true);
			addDice(x,y);
		// 通常処理
		}else{
			addDice(x,y);
		}
		break;
	case cv::EVENT_RBUTTONDOWN:
		// 削除処理
		draw(Image(),true);
		break;
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

void DiceDraw::output(){
	std::ofstream ofs;
	ofs.open("DiceInfos.txt");
	ofs<<dice_num<<std::endl;
	// 角度 X座標 Y座標 大中小 1～6
	for(int i=0;i<dice_num;i++){
		ofs<<dices[i].angle << " ";
		ofs<<dices[i].center.x << " ";
		ofs<<dices[i].center.y << " ";
		ofs<<dices[i].type << " ";
		ofs<<dices[i].kind << " ";
		ofs<<std::endl;
	}
}

}