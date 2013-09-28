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
	cv::namedWindow("test");
	cv::imshow("test",img);
	cv::waitKey(0);
}

void set(cv::Mat& img){
	img = cv::Mat(cv::Size(200,200),CV_8UC3,cv::Scalar(255,0,0));
}

void info(cv::Mat& img){
	cout << img.channels() << endl;
	cout << img.elemSize() << endl;
}

//void _test(cv::Mat& src){
//	cv::Mat dst4 = cv::Mat(src.size(),CV_8SC1);
//	cv::Mat dst5 = cv::Mat(src.size(),CV_8SC1);
//	cv::Mat dst6 = cv::Mat(src.size(),CV_8SC1);
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
//	show(src);
//	show(dst4);
//	show(dst5);
//	show(dst6);
//	show(dst1);
//	show(dst2);
//	show(dst3);
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

int main(){
	DiceDraw dd(5);
	dd.drawing();

}

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
//
//int main(int argc, char* argv[]){
//
//	try{
//		Camera camera;
//		camera.autoCapture(2,60);
//		camera.manualCapture();
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
//	img1.load("img.jpg");
//	//img1.resize(img1,cv::Size(1920,1080));
//	bin.grayeScale(img1);
//	bin.binarization(bin);
//
//	// ラベリング重心計算
//	LabelingCenter labelCenter(bin);
//	labelCenter.setCenter(bin);
//	labelCenter.circleFilter();
//	
//	// 円表示
//	for(int i=0;i<labelCenter.num;i++){
//		if(labelCenter.flags[i]){
//			img1.circle(labelCenter(i),(int)sqrt(labelCenter.sizes[i]),cv::Scalar(255,0,0));
//			//cout << "OK:" << labelCenter.sizes[i] << endl;
//		}else{
//			if(labelCenter.sizes[i]<2000)
//				img1.circle(labelCenter(i),(int)sqrt(labelCenter.sizes[i]),cv::Scalar(0,255,0));
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
//
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
//
//int main(int argc,char* argv[]){
//	Image img,gray,bin,adap;
//	img.load("Picture 6.jpg");
//	img.resize(img,cv::Size(1920,1080));
//
//	mmshow(img);
//}
