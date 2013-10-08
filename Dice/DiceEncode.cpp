#include "DiceEncode.h"

namespace pro{

DiceEncode::DiceEncode(void)
{
}


DiceEncode::~DiceEncode(void)
{
}

void DiceEncode::init(string name){
	std::ifstream ifs;
	ifs.open(name);
	int kind;
	
	// DiceDraw.init
	DiceDraw::init(5,true);	

	while(!ifs.eof()){
		ifs >> kind;
		kinds.push_back(kind);
	}

	now = 0;
	packetNum=1;
	watch_num=0;
	pattern=1;
	
	createPacket();

}

void DiceEncode::createPacket(){
	int x=DiceInfo::DICE_L/2,y=DiceInfo::DICE_L/2;
	
	switch (pattern)
	{
	case 1:
		createPacketPattern01(x,y);
		break;
	case 2:
		createPacketPattern02(x,y);
		break;
	case 3:
		createPacketPattern03(x,y);
		break;
	default:
		break;
	}

	// 小サイコロ描写
	x=DiceInfo::DICE_S/2;
	for(int i=0;i<packetNum;i++){
		if(i!=0&&i%DiceInfo::MAX_SH_NUM==0){
			y+=DiceInfo::DICE_S;
			x=DiceInfo::DICE_S/2;
		}
		addDice(cv::Point(x,y),0,DiceInfo::small,1);
		x+=DiceInfo::DICE_S;
	}

	packetNum++;

}


void DiceEncode::createPacketPattern01(int &x,int &y){
	// 大サイコロ描写
	for(int i=0;i<6;i++){
		x=DiceInfo::DICE_L/2+3;
		for(int j=0;j<6;j++){
			if(kinds.size() == now) break;
			addDice(cv::Point(x,y),0,DiceInfo::large,kinds[now++]);
			x += DiceInfo::DICE_L; 
			if(j==2) x+=3;
		}
		y += DiceInfo::DICE_L; 
	}

	// 中サイコロ描写
	for(int i=0;i<4;i++){
		x= DiceInfo::DICE_M/2+2;
		for(int j=0;j<9;j++){
			if(kinds.size() == now) break;
			addDice(cv::Point(x,y),0,DiceInfo::middle,kinds[now++]);
			x += DiceInfo::DICE_M; 
			if(j==2 || j==5) x+=2;
		}
		y += DiceInfo::DICE_M; 
	}
}

void DiceEncode::createPacketPattern02(int &x,int &y){
	// 大サイコロ描写
	for(int i=0;i<8;i++){
		x=DiceInfo::DICE_L/2+3;
		for(int j=0;j<6;j++){
			if(kinds.size() == now) break;
			addDice(cv::Point(x,y),0,DiceInfo::large,kinds[now++]);
			x += DiceInfo::DICE_L; 
			if(j==2) x+=3;
		}
		y += DiceInfo::DICE_L; 
	}
}

void DiceEncode::createPacketPattern03(int &x,int &y){

	// 中サイコロ描写
	for(int i=0;i<10;i++){
		x= DiceInfo::DICE_M/2+2;
		for(int j=0;j<9;j++){
			if(kinds.size() == now) break;
			addDice(cv::Point(x,y),0,DiceInfo::middle,kinds[now++]);
			x += DiceInfo::DICE_M; 
			if(j==2 || j==5) x+=2;
		}
		y += DiceInfo::DICE_M+1; 
	}
}

void DiceEncode::reCreatePacket(int pat){
	allClear();
	now-=nowPacketDiceNum();
	pattern=pat;
	packetNum--;
	createPacket();
}

void DiceEncode::backPacket(){
	int num=diceDraws[diceDraws.size()-1].size()-diceDraws.size();
	now-=num;
	diceDraws.pop_back();
	if(watch_num!=0&&watch_num==diceDraws.size())
		watch_num=diceDraws.size()-1;
	packetNum--;
	reCreatePacket(pattern);
}


int DiceEncode::nowPacketDiceNum(){
	switch (pattern)
	{
	case 1:
		return 72;
	case 2:
		return 6*8;
	case 3:
		return 9*10;
	default:
		break;
	}
}

void DiceEncode::nextPacket(int num){
	int size=dices.size();
	if(num!=-1){
		for(int i=num+1;i<size-packetNum+1;i++){
			label = num+1;
			draw(Image(),true);
		}
		now-=((size-packetNum+1)-num-1);
	}
	diceDraws.push_back(*this);
	allClear();
	createPacket();
	watch_num++;
	if(watch_num!=0&&watch_num==diceDraws.size())
		watch_num=diceDraws.size()-1;
}

void DiceEncode::onMouse_impl(int event, int x, int y, int flag){
	//std::string desc;
	// マウスイベントを取得
	switch(event) {
	case cv::EVENT_MOUSEMOVE:
		setPoint(x,y);
		//std::cout<<label<<std::endl;
		break;
	case cv::EVENT_LBUTTONDOWN:
		nextPacket(label);
		break;
	case cv::EVENT_RBUTTONDOWN:
		if(diceDraws.size())
			backPacket();
		break;
	}
}

void DiceEncode::keyEvent(){
	int key=cv::waitKey(30);
	switch (key)
	{
	case '1':
		reCreatePacket(1);
		break;
	case '2':
		reCreatePacket(2);
		break;
	case '3':
		reCreatePacket(3);
		break;
	case '4':
		break;
	case '5':
		break;
	case '6':
		break;
	case 's':
		break;
	case 'm':
		break;
	case 'l':
		break;
	case 2424832: // [←]
		watch_num--;
		if(watch_num<0) watch_num=0;
		break;
	case 2555904: // [→]
		watch_num++;
		if(watch_num==diceDraws.size())
			watch_num=diceDraws.size()-1;
		break;
	case 13:
		nextPacket();
		break;
	case 'c':
		allClear();
		break;
	case 'q':
		cv::destroyWindow("drawing");
		break;
	default:
		//std::cout<<key<<std::endl;
		break;
	}
}

void DiceEncode::drawing(){

	cv::namedWindow("drawing", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
	//cv::namedWindow("packets",0);

	while(1){
		// Windowの生存確認
		void* life = cvGetWindowHandle("drawing");
		if(life == NULL) break;

		base.imshow("drawing");

		dst.clone(base);
		draw(dst);
		dst.imshow("drawing");

		if(diceDraws.size()>0)
			diceDraws[watch_num].show("packets");
		else
			cv::destroyWindow("packets");

		// キーボードイベント
		keyEvent();
		// マウスイベントに対するコールバック関数を登録
		cv::setMouseCallback("drawing", onMouse, this);
	}
}


}