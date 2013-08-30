#include"Procon2013/Procon2013.h"

#include<iostream>
#include<typeinfo>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/optional.hpp>

using namespace pro;
using namespace std;

using namespace boost::property_tree;


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

int main(int argc,char* argv[]){
	OutPaiMatch opm(1);
	while(opm.getDigits()<=4000){
		try{
			opm.matching();
		}catch(const OutOfRangeException<long>& e){
			e.showError();
			return 0;
		}
	}
}

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
