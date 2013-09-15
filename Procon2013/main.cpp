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

int main(int argc,char* argv[]){
	Image img1,img2,img3,img4,img5;
	img5.init(500,500);
	img1.load("mCap5.jpg");
	//show(img1);
	img2.grayeScale(img1);
	//show(img2);
	img3.binarization(img2);
	//show(img3);
	img4.adaptiveBinarization(img2);
	//show(img4);
	img1.save("img1.jpg");
	img2.save("img2.jpg");
	img3.save("img3.jpg");
	img4.save("img4.jpg");
	show(img5);
	img5.circle(cv::Point(100,100),20,cv::Scalar(255,255,255));
	img5.rectangle(cv::Point(200,200),100,100,cv::Scalar(255,255,255));
	img5.rectangle(cv::Point(300,300),cv::Point(350,350),cv::Scalar(255,255,255));
	img5.line(cv::Point(300,300),cv::Point(350,350),cv::Scalar(255,255,255));
	img5.line(cv::Point(350,300),cv::Point(300,350),cv::Scalar(255,255,255));
	img5.triangle(cv::Point(400,400),cv::Point(450,200),cv::Point(500,400),cv::Scalar(255,255,255));

	show(img5);
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
 * Image Testing
 */

//int main(int argc, char* argv[]){
//
//	Image img("Auto_Cap","aCap1.jpg");
//	img.Show();
//	img.Resize(500,500);
//	img.Show();
//
//	return 0;
//}

/************************
 * Image Testing
 */

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