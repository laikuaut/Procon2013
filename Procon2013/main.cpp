#include"Procon2013/Procon2013.h"

#include<iostream>
#include<typeinfo>

using namespace pro;
using namespace std;

int main(int argc,char* argv[]){

	//Camera camera;
	//try{
	//	camera.autoCapture(2,60);
	//}catch(const OutOfRangeException<long>& e){
	//	e.showError();
	//}

	cout << Dir::test() << endl;

	string ss="test|";
	boost::filesystem::path path(ss);

	cout << Dir::isPath(ss) << endl;
	cout << Dir::isPath(path) << endl;

	Dir dir;
	cout << ss << endl;
	try{
		dir.cd(ss);
	}catch(const DirException& e){
		e.showError();
	}
	cout << typeid(ss).name() << endl;
	cout << typeid(dir).name() << endl;


	//dir.create("test");

	//Dir dir;


	//boost::filesystem::path ppp = dir.getPath();
	//cout << ppp.string() << endl;

	//
	//cout << _chdir("test") << endl;
	//cout << _mkdir("../test/test") << endl;
	//cout << _rmdir("test") << endl;

	//cout << _getcwd(NULL,512) << endl;
	//cout << _fullpath(_getcwd(NULL,512),"../../../",512) << endl;

	//try{
	//	test(true);
	//}catch(const char* e){
	//	cout << e << ":main()" << endl;
	//}

	//Dir dir;

	//{ 
	////http://www2s.biglobe.ne.jp/~ragnarok/program/win32/class_of_cpp_in_dll.htm
	//cout << pro::ss() << endl;
	//}

	//std::string str = dir.pwd();

	//std::cout << str << std::endl;


}