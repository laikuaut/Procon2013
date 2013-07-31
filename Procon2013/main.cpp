#include"Procon2013/Procon2013.h"

#include<iostream>
#include<typeinfo>

#include"Procon2013\ImageProcessing\Image.h"

using namespace pro;
using namespace std;

int main(int argc,char* argv[]){

	PaiFileDivide dd;
	//dd.fileSizeCalc();
	//dd.getIniSetting();
	try{
		//dd.divide();
		dd.getIniSetting();
		cout << dd.getLine(1,1,1) << endl;
		cout << dd.getLine(1,1,2) << endl;
		cout << dd.getLine(1,1,3) << endl;
	}catch(const FileException& e){
		e.showError();
	}
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

}