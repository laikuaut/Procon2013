#include "DiceRandomDraw.h"

namespace pro{

DiceRandomDraw::DiceRandomDraw(void)
{
}


DiceRandomDraw::~DiceRandomDraw(void)
{
}

void DiceRandomDraw::init(int rate){
	dicedraw.init(rate);
	srand((unsigned int)time(NULL));
	pattern=rand()%patNum+'0';
}

void DiceRandomDraw::pattern1(){
	for(int i=0;i<DiceInfo::MAX_LW_NUM;i++){
		for(int j=0;j<DiceInfo::MAX_LH_NUM;j++){
			dicedraw.addDice(cv::Point(DiceInfo::DISE_L/2+1 + (1+DiceInfo::DISE_L)*i
				,DiceInfo::DISE_L/2+1 + (1+DiceInfo::DISE_L)*j)
				,rand()%2*90,DiceInfo::large,rand()%6+1);
		}
	}
}

void DiceRandomDraw::pattern2(){
	int Lnum = rand()%4+5;
	//int Lnum = rand()%8+1;
	int Mnum = DiceInfo::getMToLWNum(Lnum);
	int LLeft = rand()%2;
	for(int i=0;i<Lnum+Mnum;i++){
		if(LLeft==0){
			if(i<Lnum){
				for(int j=0;j<DiceInfo::MAX_LH_NUM;j++){
					dicedraw.addDice(cv::Point(DiceInfo::DISE_L/2+1 + (1+DiceInfo::DISE_L)*i
						,DiceInfo::DISE_L/2 + (1+DiceInfo::DISE_L)*j)
						,rand()%2*90,DiceInfo::large,rand()%6+1);
				}
			}else{
				for(int j=0;j<DiceInfo::MAX_MH_NUM;j++){
					dicedraw.addDice(cv::Point((DiceInfo::DISE_L+1)*Lnum + DiceInfo::DISE_M/2+1 + (DiceInfo::DISE_M)*(i-Lnum)
						,DiceInfo::DISE_M/2 + (DiceInfo::DISE_M)*j)
						,rand()%2*90,DiceInfo::middle,rand()%6+1);
				}
			}
		}else{
			if(i<Mnum){
				for(int j=0;j<DiceInfo::MAX_MH_NUM;j++){
					dicedraw.addDice(cv::Point(DiceInfo::DISE_M/2+1 + (DiceInfo::DISE_M)*i
						,DiceInfo::DISE_M/2 + (DiceInfo::DISE_M)*j)
						,rand()%2*90,DiceInfo::middle,rand()%6+1);
				}
			}else{
				for(int j=0;j<DiceInfo::MAX_LH_NUM;j++){
					dicedraw.addDice(cv::Point((DiceInfo::DISE_M)*Mnum + DiceInfo::DISE_L/2+2 + (1+DiceInfo::DISE_L)*(i-Mnum)
						,DiceInfo::DISE_L/2+1 + (1+DiceInfo::DISE_L)*j)
						,rand()%2*90,DiceInfo::large,rand()%6+1);
				}
			}
		}
	}
}

void DiceRandomDraw::pattern3(){
	int Lnum = rand()%2+4;
	//int Lnum = rand()%5+1;
	int Mnum = DiceInfo::getMToLHNum(Lnum);
	int LLeft = rand()%2;
	for(int j=0;j<Lnum+Mnum;j++){
		if(LLeft==0){
			if(j<Lnum){
				for(int i=0;i<DiceInfo::MAX_LW_NUM;i++){
					dicedraw.addDice(cv::Point(DiceInfo::DISE_L/2 + (1+DiceInfo::DISE_L)*i
						,DiceInfo::DISE_L/2+1 + (1+DiceInfo::DISE_L)*j)
						,rand()%2*90,DiceInfo::large,rand()%6+1);
				}
			}else{
				for(int i=0;i<DiceInfo::MAX_MW_NUM;i++){
					dicedraw.addDice(cv::Point(DiceInfo::DISE_M/2 + (DiceInfo::DISE_M)*i
						,(DiceInfo::DISE_L+1)*Lnum + DiceInfo::DISE_M/2+1 + (DiceInfo::DISE_M)*(j-Lnum))
						,rand()%2*90,DiceInfo::middle,rand()%6+1);
				}
			}
		}else{
			if(j<Mnum){
				for(int i=0;i<DiceInfo::MAX_MW_NUM;i++){
					dicedraw.addDice(cv::Point(DiceInfo::DISE_M/2 + (DiceInfo::DISE_M)*i
						,DiceInfo::DISE_M/2+1 + (DiceInfo::DISE_M)*j)
						,rand()%2*90,DiceInfo::middle,rand()%6+1);
				}
			}else{
				for(int i=0;i<DiceInfo::MAX_LW_NUM;i++){
					dicedraw.addDice(cv::Point(DiceInfo::DISE_L/2+1 + (1+DiceInfo::DISE_L)*i
						,(DiceInfo::DISE_M)*Mnum + DiceInfo::DISE_L/2+2 + (1+DiceInfo::DISE_L)*(j-Mnum))
						,rand()%2*90,DiceInfo::large,rand()%6+1);
				}
			}
		}
	}
}

void DiceRandomDraw::pattern4(){
	int Lnumw = rand()%4+5;
	int Lnumh = rand()%2+4;
//	int Lnumw = rand()%8+1;
//	int Lnumh = rand()%5+1;
	int Mnumw = DiceInfo::getMToLWNum(Lnumw);
	int Mnumh = DiceInfo::getMToLHNum(Lnumh);
	int LPos = rand()%4;
	switch (LPos)
	{
	case 0: // 大サイコロ左上
		for(int i=0;i<Lnumw;i++){
			for(int j=0;j<Lnumh;j++){
				dicedraw.addDice(cv::Point(DiceInfo::DISE_L/2+1 + (1+DiceInfo::DISE_L)*i
					,DiceInfo::DISE_L/2+1 + (1+DiceInfo::DISE_L)*j)
					,rand()%2*90,DiceInfo::large,rand()%6+1);
			}
		}
		for(int i=0;i<DiceInfo::MAX_MW_NUM-Mnumw;i++){
			for(int j=Mnumh-1;j>=0;j--){
				dicedraw.addDice(cv::Point(DiceInfo::DISE_M/2 + (DiceInfo::DISE_M)*i
						,DiceInfo::FRAME_H - DiceInfo::DISE_M/2 - (DiceInfo::DISE_M)*(j))
						,rand()%2*90,DiceInfo::middle,rand()%6+1);
			}
		}
		for(int i=0;i<Mnumw;i++){
			for(int j=0;j<DiceInfo::MAX_MH_NUM;j++){
				dicedraw.addDice(cv::Point((DiceInfo::DISE_L+1)*Lnumw + DiceInfo::DISE_M/2+1 + (DiceInfo::DISE_M)*(i)
						,DiceInfo::DISE_M/2 + (DiceInfo::DISE_M)*j)
						,rand()%2*90,DiceInfo::middle,rand()%6+1);
			}
		}
		break;
	case 1: // 大サイコロ左下
		for(int i=0;i<Lnumw;i++){
			for(int j=0;j<Lnumh;j++){
				dicedraw.addDice(cv::Point(DiceInfo::DISE_L/2+1 + (1+DiceInfo::DISE_L)*i
					,DiceInfo::FRAME_H - DiceInfo::DISE_L/2-1 - (1+DiceInfo::DISE_L)*j)
					,rand()%2*90,DiceInfo::large,rand()%6+1);
			}
		}
		for(int i=0;i<DiceInfo::MAX_MW_NUM-Mnumw;i++){
			for(int j=Mnumh-1;j>=0;j--){
				dicedraw.addDice(cv::Point(DiceInfo::DISE_M/2 + (DiceInfo::DISE_M)*i
						,DiceInfo::DISE_M/2 + (DiceInfo::DISE_M)*(j))
						,rand()%2*90,DiceInfo::middle,rand()%6+1);
			}
		}
		for(int i=0;i<Mnumw;i++){
			for(int j=0;j<DiceInfo::MAX_MH_NUM;j++){
				dicedraw.addDice(cv::Point((DiceInfo::DISE_L+1)*Lnumw + DiceInfo::DISE_M/2+1 + (DiceInfo::DISE_M)*(i)
						,DiceInfo::DISE_M/2 + (DiceInfo::DISE_M)*j)
						,rand()%2*90,DiceInfo::middle,rand()%6+1);
			}
		}
		break;
	case 2: // 大サイコロ右上
		for(int i=0;i<Lnumw;i++){
			for(int j=0;j<Lnumh;j++){
				dicedraw.addDice(cv::Point(DiceInfo::FRAME_W - DiceInfo::DISE_L/2-1 - (1+DiceInfo::DISE_L)*i
					,DiceInfo::DISE_L/2-1 + (1+DiceInfo::DISE_L)*j)
					,rand()%2*90,DiceInfo::large,rand()%6+1);
			}
		}
		for(int i=0;i<DiceInfo::MAX_MW_NUM-Mnumw;i++){
			for(int j=Mnumh-1;j>=0;j--){
				dicedraw.addDice(cv::Point(DiceInfo::FRAME_W - DiceInfo::DISE_M/2 - (DiceInfo::DISE_M)*i
						,DiceInfo::FRAME_H - DiceInfo::DISE_M/2 - (DiceInfo::DISE_M)*(j))
						,rand()%2*90,DiceInfo::middle,rand()%6+1);
			}
		}
		for(int i=0;i<Mnumw;i++){
			for(int j=0;j<DiceInfo::MAX_MH_NUM;j++){
				dicedraw.addDice(cv::Point(DiceInfo::DISE_M/2+1 + (DiceInfo::DISE_M)*(i)
						,DiceInfo::DISE_M/2 + (DiceInfo::DISE_M)*j)
						,rand()%2*90,DiceInfo::middle,rand()%6+1);
			}
		}
		break;
	case 3: // 大サイコロ右下
		for(int i=0;i<Lnumw;i++){
			for(int j=0;j<Lnumh;j++){
				dicedraw.addDice(cv::Point(DiceInfo::FRAME_W - DiceInfo::DISE_L/2-1 - (1+DiceInfo::DISE_L)*i
					,DiceInfo::FRAME_H - DiceInfo::DISE_L/2-1 - (1+DiceInfo::DISE_L)*j)
					,rand()%2*90,DiceInfo::large,rand()%6+1);
			}
		}
		for(int i=0;i<DiceInfo::MAX_MW_NUM-Mnumw;i++){
			for(int j=Mnumh-1;j>=0;j--){
				dicedraw.addDice(cv::Point(DiceInfo::FRAME_W - DiceInfo::DISE_M/2 - (DiceInfo::DISE_M)*i
						,DiceInfo::DISE_M/2 + (DiceInfo::DISE_M)*(j))
						,rand()%2*90,DiceInfo::middle,rand()%6+1);
			}
		}
		for(int i=0;i<Mnumw;i++){
			for(int j=0;j<DiceInfo::MAX_MH_NUM;j++){
				dicedraw.addDice(cv::Point(DiceInfo::DISE_M/2+1 + (DiceInfo::DISE_M)*(i)
						,DiceInfo::DISE_M/2 + (DiceInfo::DISE_M)*j)
						,rand()%2*90,DiceInfo::middle,rand()%6+1);
			}
		}
		break;
	default:
		break;
	}
}

void DiceRandomDraw::pattern5(){

}

void DiceRandomDraw::pattern6(){

}

void DiceRandomDraw::pattern7(){

}

void DiceRandomDraw::pattern8(){

}

void DiceRandomDraw::pattern9(){

}

void DiceRandomDraw::pattern0(){
	pattern=rand()%patNum+'0';
	setPattern();
}

void DiceRandomDraw::setPattern(){
	switch (pattern)
	{
	case '0':
		pattern0();
		break;
	case '1':
		pattern1();
		break;
	case '2':
		pattern2();
		break;
	case '3':
		pattern3();
		break;
	case '4':
		pattern4();
		break;
	case '5':
		pattern5();
		break;
	case '6':
		pattern6();
		break;
	case '7':
		pattern7();
		break;
	case '8':
		pattern8();
		break;
	case '9':
		pattern9();
		break;
	default:
		break;
	}
}

void DiceRandomDraw::run(){
	std::cout << "メニュー>> q:終了 SPACE:停止/再開 r:選択(開始)" << std::endl;
	std::cout << "モード  >> 0:random 1:L 2～4:L&M" << std::endl;

	timer.start();
	setPattern();

	bool end = false;

	while(!end){
		long now = timer.getNow()/Timer::PER_SEC;
		std::cout << "\r" << now/60 << ":" << now%60 << "\t\t\t\t" << std::flush;
		int key=cv::waitKey(30);
		switch (key)
		{
		case 'q':
			end=true;
			break;
		case 'r':
			timer.reset();
			dicedraw.allClear();
			dicedraw.show();
			std::cout << "\r\r" << "パターン選択(0～" << patNum-1 << ")" << "\t\t\t\t"  << std::flush;
			pattern = cv::waitKey(0);
			timer.start();
			setPattern();
			break;
		case ' ':
			// 停止処理
			if(timer.getState()==Timer::START){
				timer.stop();
			// 再開処理
			}else if(timer.getState()==Timer::STOP){
				timer.restart();
			}
			break;
		default:
			if('0'<=key && key < '0'+patNum){
				pattern = key;
				dicedraw.allClear();
				timer.start();
				setPattern();
			}
			dicedraw.show();
			break;
		}
	}
}

}