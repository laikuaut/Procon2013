#include"Procon2013/Procon2013.h"

#include<iostream>
#include<typeinfo>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/optional.hpp>

using namespace pro;
using namespace std;

using namespace boost::property_tree;

// Testing main

void show(cv::Mat& img){
	cv::namedWindow("test",0);
	cv::imshow("test",img);
	cv::waitKey(0);
}

void show(cv::Mat& img,std::string str){
	//cv::waitKey(1000);
	cv::namedWindow(str,0);
	cv::imshow(str,img);
}

void set(cv::Mat& img){
	img = cv::Mat(cv::Size(200,200),CV_8UC3,cv::Scalar(255,0,0));
}

void info(cv::Mat& img){
	cout << img.channels() << endl;
	cout << img.elemSize() << endl;
}

//void _test(cv::Mat& src){
//	cv::Mat dst4 = cv::Mat(src.size(),0);
//	cv::Mat dst5 = cv::Mat(src.size(),0);
//	cv::Mat dst6 = cv::Mat(src.size(),0);
//	cv::Mat dst1 = cv::Mat(src.size(),src.type(),cv::Scalar(255,255,255));
//	cv::Mat dst2 = cv::Mat(src.size(),src.type(),cv::Scalar(255,255,255));
//	cv::Mat dst3 = cv::Mat(src.size(),src.type(),cv::Scalar(255,255,255));
//	for(int y = 0; y < src.rows; ++y){
//		for(int x = 0; x < src.cols; ++x){
//			// 画像のチャネル数分だけループ。白黒の場合は1回、カラーの場合は3回　　　　　
//			//for(int c = 0; c < src.channels(); ++c){
//			dst4.data[ y * dst4.step + x * dst4.channels() + 0 ] = src.data[ y * src.step + x * src.channels() + 0];
//			dst5.data[ y * dst5.step + x * dst5.channels() + 0 ] = src.data[ y * src.step + x * src.channels() + 1];
//			dst6.data[ y * dst6.step + x * dst6.channels() + 0 ] = src.data[ y * src.step + x * src.channels() + 2];
//			dst1.data[ y * src.step + x * src.channels() + 0] = src.data[ y * src.step + x * src.channels() + 0];
//			dst2.data[ y * src.step + x * src.channels() + 1] = src.data[ y * src.step + x * src.channels() + 1];
//			dst3.data[ y * src.step + x * src.channels() + 2] = src.data[ y * src.step + x * src.channels() + 2];
//			//}
//		}
//	}
//	//show(src);
//	show(dst4);
//	show(dst5);
//	show(dst6);
//	//show(dst1);
//	//show(dst2);
//	//show(dst3);
//	//cv::cvtColor(dst4, dst4, CV_BGR2GRAY);
//	//cv::cvtColor(dst5, dst5, CV_BGR2GRAY);
//	//cv::cvtColor(dst6, dst6, CV_BGR2GRAY);
//	cv::threshold(dst4, dst4, 0, 255, cv::THRESH_BINARY_INV|cv::THRESH_OTSU);
//	cv::threshold(dst5, dst5, 0, 255, cv::THRESH_BINARY_INV|cv::THRESH_OTSU);
//	cv::threshold(dst6, dst6, 0, 255, cv::THRESH_BINARY_INV|cv::THRESH_OTSU);
//	show(dst4);
//	show(dst5);
//	show(dst6);
//
//
//}

//void hist(cv::Mat& src){
//  //cv::Mat src_img = cv::imread("../../image/lenna.png", 0);
//  //if(src_img.empty()) return -1; 
//  
//  // ヒストグラムを描画する画像割り当て
//  const int ch_width = 260, ch_height=200;
//  cv::Mat hist_img(cv::Size(ch_width, ch_height), CV_8UC3, cv::Scalar::all(255));
//
//  cv::Mat hist;
//  const int hdims[] = {256}; // 次元毎のヒストグラムサイズ
//  const float hranges[] = {0,250};
//  const float* ranges[] = {hranges}; // 次元毎のビンの下限上限
//  double max_val = .0;
//
//  // シングルチャンネルのヒストグラム計算
//  // 画像（複数可），画像枚数，計算するチャンネル，マスク，ヒストグラム（出力），
//  // ヒストグラムの次元，ヒストグラムビンの下限上限
//  cv::calcHist(&src, 1, 0, cv::Mat(), hist, 1, hdims, ranges);
//  
//  // 最大値の計算
//  cv::minMaxLoc(hist, 0, &max_val);
//
//  // ヒストグラムのスケーリングと描画
//  cv::Scalar color = cv::Scalar::all(100);
//  // スケーリング
//  hist = hist * (max_val? ch_height/max_val:0.);
//  for(int j=0; j<hdims[0]; ++j) {
//    int bin_w = cv::saturate_cast<int>((double)ch_width/hdims[0]);
//    cv::rectangle(hist_img, 
//		  cv::Point(j*bin_w, hist_img.rows),
//		  cv::Point((j+1)*bin_w, hist_img.rows-cv::saturate_cast<int>(hist.at<float>(j))),
//		  color, -1);
//  }
//
//  cv::namedWindow("Image", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
//  cv::namedWindow("Histogram", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
//  cv::imshow("Image", src);
//  cv::imshow("Histogram", hist_img);
//  cv::waitKey(0);
//}


//
//int main(int argc,char* argv[]){
//	Image img1,img2,img3,img4,img5;
//	img5.init(500,500);
//	img1.load("img.jpg");
//	//show(img1);
//	img2.grayeScale(img1);
//	//show(img2);
//	img3.binarization(img2);
//	//show(img3);
//	img4.adaptiveBinarization(img2);
//	//show(img4);
//	img1.save("img1.jpg");
//	img2.save("img2.jpg");
//	img3.save("img3.jpg");
//	img4.save("img4.jpg");
//	//show(img5);
//	img5.circle(cv::Point(100,100),20,cv::Scalar(255,255,255));
//	img5.rectangle(cv::Point(200,200),100,100,cv::Scalar(255,255,255));
//	img5.rectangle(cv::Point(300,300),cv::Point(350,350),cv::Scalar(255,255,255));
//	img5.line(cv::Point(300,300),cv::Point(350,350),cv::Scalar(255,255,255));
//	img5.line(cv::Point(350,300),cv::Point(300,350),cv::Scalar(255,255,255));
//	img5.triangle(cv::Point(400,400),cv::Point(450,200),cv::Point(500,400),cv::Scalar(255,255,255));
//	//show(img5);
//	show(img3);
//	label(img4);
//}




//int main(int argc,char* argv[]){


	//try{
	//	OutPaiDivide opd("./Resource/Pi - Hex - Chudnovsky.txt");
	//	opd.divide();
	//}catch(const FileException& e){
	//	e.showError();
	//}catch(const DirException& e){
	//	e.showError();
	//}
/*
	InPaiDivide ipd;*/
	////ipd.getIniSetting();

	//cout << ipd.getLine() << endl;
	//cout << ipd.nextLine() << endl;


	//PaiMatch pm(2);
	//while(pm.getDigits()<=4000)
	//	pm.matching();


	
	//ptree pt;
	//
 //   pt.put("Data.value1", 1);
 //   pt.put("Data.value2", 2);
 //   pt.put("Data.str", "Hello");
 //   pt.put("Data2.str", "Hello");
 //   pt.put("Data2.str2", "Hello");

	//write_ini("data_out.ini" , pt);
	

	/*
	ptree pt;
    read_ini("data_out.ini", pt);

    if (boost::optional<int> value = pt.get_optional<int>("Data.value2")) {
        std::cout << "value2 : " << value.get() << std::endl;
    }
    else {
        std::cout << "value is nothing" << std::endl;
    }

	if (boost::optional<int> value = pt.get_optional<int>("Data.value1")) {
        std::cout << "value1 : " << value.get() << std::endl;
    }
    else {
        std::cout << "value is nothing" << std::endl;
    }

    if (boost::optional<std::string> str = pt.get_optional<std::string>("Data.str")) {
        std::cout << "str : " << str.get() << std::endl;
    }
    else {
        std::cout << "str is nothing" << std::endl;
    }
	*/

	//CharArrayNumeric can(CharArrayNumeric::HEX,1);
	//do{
	//	cout << can << endl;
	//}while(can.add());


	//PaiFileDivide dd;
	////dd.fileSizeCalc();
	////dd.getIniSetting();
	//try{
	//	//dd.divide();
	//	dd.getIniSetting();
	//	cout << dd.getLine(1,1,1) << endl;
	//	cout << dd.getLine(1,1,2) << endl;
	//	cout << dd.getLine(1,1,3) << endl;
	//}catch(const FileException& e){
	//	e.showError();
	//}
	//try{
	//	Camera camera;
	//	camera.autoCapture(2,60);
	//	camera.manualCapture();
	//}catch(const OutOfRangeException<long>& e){
	//	e.showError();
	//}catch(const OutOfRangeException<int>& e){
	//	e.showError();
	//}catch(const DirException& e){
	//	e.showError();
	//}catch(const boost::filesystem::filesystem_error& e){
	//	cout << e.what() <<endl;
	//}catch(const CameraException& e){
	//	e.showError();
	//}

	//pro::Image::test();

//}



/************************
 * PaiDivide
 */

//int main(int argc,char* argv[]){
//	try{
//		OutPaiDivide opd(argv[1]);
//		opd.divide();
//	}catch(const FileException& e){
//		e.showError();
//	}catch(const DirException& e){
//		e.showError();
//	}
//
//}

/************************
 * OutPaiMatch
 */

//int main(int argc,char* argv[]){
//	OutPaiMatch opm(1);
//	while(opm.getDigits()<=4000){
//		try{
//			opm.matching();
//		}catch(const OutOfRangeException<long>& e){
//			e.showError();
//			return 0;
//		}
//	}
//}

/************************
 * InPaiMatch Testing
 */
//
//int main(int argc,char* argv[]){
//
//	InPaiMatch ipm;
//	string key;
//
//	while(1){
//		cin >> key;
//		if(key=="q"){
//			break;
//		}else if(key=="n") {
//			if(!ipm.nextNum())
//				continue;
//		}else if(key=="e"){
//		
//		}else {
//			if(!ipm.setNum(key.c_str()))
//				continue;
//		}
//
//		ipm.next();
//		ipm.nowDisplay();
//
//	}
//			 
//}


/************************
 * Cam Testing
 */

//int main(int argc, char* argv[]){
//
//	int interval;
//	int time;
//
//	cout << "試合時間 > " << flush;
//	cin >> time;
//	cout << "間隔 > " << flush;
//	cin >> interval;
//
//	try{
//		Camera camera;
//		camera.autoCapture(interval,time);
//		//camera.manualCapture();
//	}catch(const OutOfRangeException<long>& e){
//		e.showError();
//	}catch(const OutOfRangeException<int>& e){
//		e.showError();
//	}catch(const DirException& e){
//		e.showError();
//	}catch(const boost::filesystem::filesystem_error& e){
//		cout << e.what() <<endl;
//	}catch(const CameraException& e){
//		e.showError();
//	}
//
//	return 0;
//}

/************************
 * Label Testing
 */
//// 適当な色を出す用
//cv::RNG rnd(1192);
//cv::Scalar randomColor()
//{
//    return cv::Scalar(rnd.next() & 0xFF, rnd.next() & 0xFF, rnd.next() & 0xFF);
//}
//// ラベリング　ランダム色
//void label(Image src){
//	Labeling labels(src);
//	labels.labeling(src);
//	vector<cv::Scalar> colors;
//	colors.resize(labels.num);
//	memset(&colors[0],0,sizeof(cv::Scalar)*labels.num);
//	for(int i=0;i<labels.num;i++){
//		colors[i] = randomColor();
//	}
//	cv::Mat dst(cv::Size(labels.w,labels.h),CV_8UC3);
//	for(int y = 0; y < labels.h; ++y){
//		for(int x = 0; x < labels.w; ++x){
//			dst.data[y*dst.step + x*dst.channels() + 0] = colors[labels(x,y)][0];
//			dst.data[y*dst.step + x*dst.channels() + 1] = colors[labels(x,y)][1];
//			dst.data[y*dst.step + x*dst.channels() + 2] = colors[labels(x,y)][2];
//		}
//	}
//	show(dst);
//}
//// ラベリングメイン
//void main(){
//	Image img;
//	img.load("img.jpg");
//	img.grayeScale(img);
//	img.binarization(img);
//	label(img);
//}

/************************
 * LabelingCenter Testing
 */
//int main(int argc,char* argv[]){
//	Image img1,bin;
//
//	// 画像処理
//	img1.load("Dice/Picture 15.jpg");
//	img1.resize(img1,cv::Size(1920,1080));
//	bin.grayeScale(img1);
//	bin.binarization(bin);
//
//	// ラベリング重心計算
//	LabelingCenter labelCenter;
//	labelCenter.init(bin);
//	labelCenter.setCenter(bin);
//	labelCenter.circleFilter();
//	labelCenter.sizeFilter(30,2000);
//	
//	// 円表示
//	for(int i=0;i<labelCenter.num;i++){
//		if(labelCenter.flags[i]){
//			img1.circle(labelCenter(i),(int)sqrt(labelCenter.sizes[i]/CV_PI),cv::Scalar(255,0,0));
//			//cout << "OK:" << labelCenter.sizes[i] << endl;
//		}else{
//			if(labelCenter.sizes[i]<2000)
//				img1.circle(labelCenter(i),(int)sqrt(labelCenter.sizes[i]/CV_PI),cv::Scalar(0,255,0));
//			//cout << "NG:" << labelCenter.sizes[i] << endl;
//		}
//	}
//	show(img1);
//	
//	// 座標出力
//	labelCenter.outputCenter();
//}

/************************
 * MouseEvent Testing
 */
//class MainMouseEvent : public MouseEvent{
//public:
//
//	void onMouse_impl(int event,int x,int y,int flag);
//
//};
//
//void MainMouseEvent::onMouse_impl(int event,int x,int y,int flag){
//	  std::string desc;
////  cv::Mat img;
//
//  //mouse_point = cv::Point(x,y);
//
//  // マウスイベントを取得
//  switch(event) {
//  case cv::EVENT_MOUSEMOVE:
//    desc += "MOUSE_MOVE";
//    break;
//  case cv::EVENT_LBUTTONDOWN:
//    desc += "LBUTTON_DOWN";
////	draw();
//    break;
//  case cv::EVENT_RBUTTONDOWN:
//    desc += "RBUTTON_DOWN";
//    break;
//  case cv::EVENT_MBUTTONDOWN:
//    desc += "MBUTTON_DOWN";
//    break;
//  case cv::EVENT_LBUTTONUP:
//    desc += "LBUTTON_UP";
//    break;
//  case cv::EVENT_RBUTTONUP:
//    desc += "RBUTTON_UP";
//    break;
//  case cv::EVENT_MBUTTONUP:
//    desc += "MBUTTON_UP";
//    break;
//  case cv::EVENT_LBUTTONDBLCLK:
//    desc += "LBUTTON_DBLCLK";
//    break;
//  case cv::EVENT_RBUTTONDBLCLK:
//    desc += "RBUTTON_DBLCLK";
//    break;
//  case cv::EVENT_MBUTTONDBLCLK:
//    desc += "MBUTTON_DBLCLK";
//    break;
//  }
//
//  // マウスボタン，及び修飾キーを取得
//  if(flag & cv::EVENT_FLAG_LBUTTON)
//    desc += " + LBUTTON";
//  if(flag & cv::EVENT_FLAG_RBUTTON)
//    desc += " + RBUTTON";
//  if(flag & cv::EVENT_FLAG_MBUTTON)
//    desc += " + MBUTTON";
//  if(flag & cv::EVENT_FLAG_CTRLKEY)
//    desc += " + CTRL";
//  if(flag & cv::EVENT_FLAG_SHIFTKEY)
//    desc += " + SHIFT";
//  if(flag & cv::EVENT_FLAG_ALTKEY)
//    desc += " + ALT";
//
//  std::cout << desc << " (" << x << ", " << y << ")" << std::endl;
//}
//void mmshow(cv::Mat& mat){
//	MainMouseEvent mme;
//
//	cv::namedWindow("drawing");
//
//	while(cv::waitKey(30)){
//		// Windowの生存確認
//		void* life = cvGetWindowHandle("drawing");
//		if(life == NULL) break;
//
//		cv::imshow("drawing",mat);
//
//		cv::setMouseCallback("drawing", MainMouseEvent::onMouse, &mme);
//	}
//}
//int main(int argc,char* argv[]){
//	Image img,gray,bin,adap;
//	img.load("Picture 6.jpg");
//	img.resize(img,cv::Size(1920,1080));
//
//	mmshow(img);
//}

/************************
 * DiceDraw Testing
 */
//int main(){
//	DiceDraw dd(5);
//	//for(int i=0;i<9;i++){
//	//	for(int j=0;j<6;j++){
//	//		dd.addDice(cv::Point(DiceInfo::DICE_L/2+1 + (1+DiceInfo::DICE_L)*i,DiceInfo::DICE_L/2+1 + (1+DiceInfo::DICE_L)*j),i*90,DiceInfo::large,j+1);
//	//	}
//	//}
//
//	dd.drawing();
//	dd.output();
//}

/************************
 * Image Binaly Testing
 */
//int main(){
//	Image img,gray,bin,adap;
//	img.load("Picture 7.jpg");
//	img.resize(img,cv::Size(1920,1080));
//	show(img);
//	gray.grayeScale(img);
//	show(gray);
//	bin.binarization(gray);
//	show(bin);
//	adap.adaptiveBinarization(gray);
//	show(adap);
//}

/************************
 * LineSegment Testing
 */
//int main(){
//	Dot1Point dot1[2];
//	Dot2Point dot2;
//	Image img;
//	img.init(600,600);
//	img.oneColor(cv::Scalar::all(255));
//
//	dot1[0].init(300,300,100);
//	dot1[1].init(100,500,100);
//
//	dot2.init(dot1);
//
//	dot2.draw(img);
//
//	show(img);
//}

/************************
 * DiceDetection Testing01
 */
//int main(){
//	// 宣言
//	DiceDetection dd;
//	Image img,draw,draw1,bin;
//	LabelingCenter lc;
//	Timer timer;
//
//	// デバック時間省略のためのファイル読み込み
//	ifstream ifs;
//	char* c_str = new char[10];
//	ifs.open("img.txt");
//	ifs.getline(c_str,100);
//
//	
//	// 色
//	cv::Scalar white,red,green,blue,black;
//		white = cv::Scalar::all(255);
//		black = cv::Scalar::all(0);
//		red = cv::Scalar(0,0,255);
//		green = cv::Scalar(0,255,0);
//		blue = cv::Scalar(255,0,0);
//
//	
//	timer.start();
//
//	// 画像作成
//	img.load(c_str);
//	img.resize(img,cv::Size(1920,1080));
//	
//	draw.clone(img);
//	//draw1.clone(img);
//
//	timer.lap();
//	cout << "画像生成:" << (double)timer.getNow()/1000 << endl;
//
//	// サイコロの目を検出
//	dd.init(img);
//	dd.getAllPoints();
//
//	// 初期検出
//	dd.drawTypePoints(draw,DiceInfo::none,blue);
//	dd.drawTypePoints(draw,DiceInfo::small,red);
//	dd.drawTypePoints(draw,DiceInfo::middle,green);
//	dd.drawTypePoints(draw,DiceInfo::large,white);
//	show(draw,"first");
//	draw.clone(img);
//
//	timer.lap();
//	cout << "全点検出:" << (double)timer.getNow()/1000 << endl;
//
//	// 1の目の取得
//	dd.getDot1Points();
//
//	// 1の目の判別状態
//	dd.drawTypePoints(draw,DiceInfo::none,blue);
//	dd.drawTypePoints(draw,DiceInfo::small,red);
//	dd.drawTypePoints(draw,DiceInfo::middle,green);
//	dd.drawTypePoints(draw,DiceInfo::large,white);
//	show(draw,"dot1");
//	draw.clone(img);
//
//	cout << "all:" << dd.getNumDot1Points() << endl;
//	cout << "small:" << dd.getNumDot1Points(DiceInfo::small) << endl;
//	cout << "middle:" << dd.getNumDot1Points(DiceInfo::middle) << endl;
//	cout << "large:" << dd.getNumDot1Points(DiceInfo::large) << endl;
//
//
//	timer.lap();
//	cout << "１の目:" << (double)timer.getNow()/1000 << endl;
//
//
//	dd.correctPointType();
//
//	// 修正状態の確認
//	dd.drawTypePoints(draw,DiceInfo::none,blue);
//	dd.drawTypePoints(draw,DiceInfo::small,red);
//	dd.drawTypePoints(draw,DiceInfo::middle,green);
//	dd.drawTypePoints(draw,DiceInfo::large,white);
//	show(draw,"correct");
//	draw.clone(img);
//
//	cout << "all:" << dd.getNumAllPoints() << endl;
//	cout << "none:" << dd.getNumTypeAllPoints(DiceInfo::none) << endl;
//	cout << "small:" << dd.getNumTypeAllPoints(DiceInfo::small) << endl;
//	cout << "middnle:" << dd.getNumTypeAllPoints(DiceInfo::middle) << endl;
//	cout << "large:" << dd.getNumTypeAllPoints(DiceInfo::large) << endl;
//
//	timer.lap();
//	cout << "サイズ修正:" << (double)timer.getNow()/1000 << endl;
//
//	// 線分取得
//	dd.getAllLines();
//
//	cout <<"num:" << dd.getNumAllLines() << endl;
//
//	dd.drawAllLine(draw,blue,red);
//	//dd.drawFalsePoints(draw,green);
//	//dd.drawTypePoints(draw,DiceInfo::none,green);
//	show(draw,"allLine");
//	draw.clone(img);
//
//	timer.lap();
//	cout << "線分抽出:" << (double)timer.getNow()/1000 << endl;
//
//	// 2の目の取得
//	dd.getDot2Points();
//	
//	// 2の目の確認
//	dd.drawTrueLine(draw,green,blue);
//	//dd.drawFalseLine(draw,red,red);
//	dd.drawDot2Points(draw,red,green);
//	dd.drawDot2Center(draw,blue);
//	show(draw,"Dot2");
//	draw.clone(img);
//
//	cout << "all:" << dd.getNumDot2Points() << endl;
//	cout << "small:" << dd.getNumDot2Points(DiceInfo::small) << endl;
//	cout << "middle:" << dd.getNumDot2Points(DiceInfo::middle) << endl;
//	cout << "large:" << dd.getNumDot2Points(DiceInfo::large) << endl;
//
//	timer.lap();
//	cout << "２の目:" << (double)timer.getNow()/1000 << endl;
//	
//	//// 4の目の取得
//	//dd.getDot4Points();
//
//	////dd.drawTrueLine(draw,blue,green);
//	////dd.drawDot1Points(draw,white);
//	////dd.drawKindPoints(draw,2,white);
//	//dd.drawKindPoints(draw,4,white);
//	////dd.drawDot4Points(draw,red,blue);
//	//dd.drawDot4Center(draw,blue);
//	//show(draw,"Dot4");
//	//draw.clone(img);
//
//	//cout << dd.getNumDot4Points() << endl;
//
//	//cout << "all:" << dd.getNumDot4Points() << endl;
//	//cout << "small:" << dd.getNumDot4Points(DiceInfo::small) << endl;
//	//cout << "middle:" << dd.getNumDot4Points(DiceInfo::middle) << endl;
//	//cout << "large:" << dd.getNumDot4Points(DiceInfo::large) << endl;
//
//	//timer.lap();
//	//cout << "４の目:" << (double)timer.getNow()/1000 << endl;
//
//	//３点全
//	dd.getAllDot3Points();
//
//	// 3点全描写
//	dd.drawAllDot3Points(draw,red,blue);
//	dd.drawAllDot3Center(draw,blue);
//	show(draw,"allDot3");
//	draw.clone(img);
//
//	cout << "num:" << dd.getNumAllDot3Points() << endl;
//
//	timer.lap();
//	cout << "3点全:" << (double)timer.getNow()/1000 << endl;
//
//
//	// 5の目の取得
//	dd.getDot5Points();
//	//dd.drawFalseAllDot3Points(draw,green,blue);
//
//	dd.drawDot5Points(draw,red,blue);
//	dd.drawTrueAllDot3Points(draw,green,blue);
//	show(draw,"dot5");
//	draw.clone(img);
//
//	cout << "all:" << dd.getNumDot5Points() << endl;
//	cout << "small:" << dd.getNumDot5Points(DiceInfo::small) << endl;
//	cout << "middle:" << dd.getNumDot5Points(DiceInfo::middle) << endl;
//	cout << "large:" << dd.getNumDot5Points(DiceInfo::large) << endl;
//
//	timer.lap();
//	cout << "5の目:" << (double)timer.getNow()/1000 << endl;
//
//
//	// 3の目の取得
//	dd.getDot3Points();
//
//	dd.drawDot3Points(draw,red,blue);
//	show(draw,"dot3");
//	draw.clone(img);
//
//	cout << "all:" << dd.getNumDot3Points() << endl;
//	cout << "small:" << dd.getNumDot3Points(DiceInfo::small) << endl;
//	cout << "middle:" << dd.getNumDot3Points(DiceInfo::middle) << endl;
//	cout << "large:" << dd.getNumDot3Points(DiceInfo::large) << endl;
//
//	timer.lap();
//	cout << "3の目:" << (double)timer.getNow()/1000 << endl;
//
//
//	// 6の目の取得
//	dd.getDot6Points();
//
//	dd.drawDot6Points(draw,red,blue);
//	dd.drawDot6Center(draw,blue);
//	show(draw,"dot6");
//	draw.clone(img);
//
//	cout << "all:" << dd.getNumDot6Points() << endl;
//	cout << "small:" << dd.getNumDot6Points(DiceInfo::small) << endl;
//	cout << "middle:" << dd.getNumDot6Points(DiceInfo::middle) << endl;
//	cout << "large:" << dd.getNumDot6Points(DiceInfo::large) << endl;
//
//	timer.lap();
//	cout << "6の目:" << (double)timer.getNow()/1000 << endl;
//
//	// 4の目の取得
//	dd._getDot4Points();
//
//	//dd.drawTrueLine(draw,blue,green);
//	//dd.drawDot1Points(draw,white);
//	//dd.drawKindPoints(draw,2,white);
//	dd.drawKindPoints(draw,4,white);
//	//dd.drawDot4Points(draw,red,blue);
//	dd.drawDot4Center(draw,blue);
//	show(draw,"Dot4");
//	draw.clone(img);
//
//	cout << dd.getNumDot4Points() << endl;
//
//	cout << "all:" << dd.getNumDot4Points() << endl;
//	cout << "small:" << dd.getNumDot4Points(DiceInfo::small) << endl;
//	cout << "middle:" << dd.getNumDot4Points(DiceInfo::middle) << endl;
//	cout << "large:" << dd.getNumDot4Points(DiceInfo::large) << endl;
//
//	timer.lap();
//	cout << "４の目:" << (double)timer.getNow()/1000 << endl;
//
//
//	// 最終処理
//	dd.correctOddMiddleToLarge();
//	dd.clearAllLines();
//	dd.getAllLines();
//	dd.getDot2Points();
//	dd.getAllDot3Points();
//	dd.getDot5Points();
//	dd.getDot3Points();
//	dd.getDot6Points();
//	dd.getDot4Points();
//
//	timer.lap();
//	cout << "最終処理:" << (double)timer.getNow()/1000 << endl;
//	
//	dd.getAllDotCenters();
//
//	dd.drawAllDotCenters(draw,blue);
//	show(draw,"Centers");
//	draw.clone(img);
//
//	timer.lap();
//	cout << "中心点:" << (double)timer.getNow()/1000 << endl;
//
//
//	// 検出した点の種類ごと
//	dd.drawDot1Points(draw,white);
//	dd.drawDot2Points(draw,red,red);
//	dd.drawDot2Center(draw,blue);
//	dd.drawDot3Points(draw,green,red);
//	dd.drawDot3Center(draw,blue);
//	dd.drawDot4Points(draw,cv::Scalar(255,255,0),red);
//	dd.drawDot4Center(draw,blue);
//	dd.drawDot5Points(draw,cv::Scalar(255,0,255),red);
//	dd.drawDot5Center(draw,blue);
//	dd.drawDot6Points(draw,cv::Scalar(0,255,255),red);
//	dd.drawDot6Center(draw,blue);
//	show(draw,"AllDots");
//	draw.clone(img);
//
//	// 検出した点のサイズごと
//	dd.drawTypePoints(draw,DiceInfo::none,cv::Scalar(255,0,0));
//	dd.drawTypePoints(draw,DiceInfo::small,red);
//	dd.drawTypePoints(draw,DiceInfo::middle,green);
//	dd.drawTypePoints(draw,DiceInfo::large,white);
//	show(draw,"Types");
//	draw.clone(img);
//
//
//	dd.drawTruePoints(draw,blue);
//	show(draw,"TruePoints");
//	draw.clone(img);
//
//	//dd.drawKindPoints(draw,1,blue);
//	//dd.drawKindPoints(draw,2,red);
//
//	// 表示
//	cv::waitKey(0);
//
//	//timer.getLapTime();
//
//}

/************************
 * DiceDetection Testing02
 */
int main(){
	// 宣言
	DiceDetection dd;
	Image img,draw,draw1,bin;
	
	dd.init();
	dd.run();
}

/************************
 * hsvColorExtraction Testing
 * 赤色検出による1の目の探索
 */
//int main(){
//	Image img,dst,hue1,hue2;
//	img.load("Dice/Picture 10.jpg");
//	img.resize(img,cv::Size(1920,1080));
//
//	dst.clone(img);
//
//	//for(int i=0;i<6;i++){
//	//	stringstream ss;
//	//	ss << "hsv" << i << ".jpg";
//	//	dst.hsvColorExtraction(img,60*i,60*i+60,100,100);
//	//	dst.save(ss.str());
//	//}
//
//	hue1.hsvColorExtraction(img,0,60,100,100);
//	show(hue1);
//	hue2.hsvColorExtraction(img,120,180,100,100);
//	show(hue2);
//	dst.bitwiseOr(hue1,hue2);
//	show(dst);
//
//	LabelingCenter lc;
//	lc.init(dst);
//	lc.setCenter(dst);
//	lc.circleFilter(1,3);
//	lc.sizeFilter(200,2000);
//	lc.draw(img,1,cv::Scalar(255,0,0));
//	lc.draw(img,0,cv::Scalar(255,255,0));
//
//	//show(dst);
//	show(img);
//
//}

/************************
 * DiceDraw Random Testing
 */
//int main(){
//	DiceRandomDraw drd;
//	drd.init(5);
//	drd.run();
//}

