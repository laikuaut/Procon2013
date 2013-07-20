#include "Dir.h"

#include<iostream>
#include<cstring>
#include<fstream>

#include<boost/filesystem.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <cstdio>
#include <boost/format.hpp>

using namespace std;
namespace fs = boost::filesystem;

namespace pro{

Dir::Dir(void)
{
	path = fs::system_complete(".");
	this->regex = "[:*?\"<>|]";
}

Dir::Dir(string path){
	this->path = fs::system_complete(path);
	this->regex = "[:*?\"<>|]";
}

Dir::~Dir(void)
{

}

bool Dir::isPath() const{
	string str = path.string();
	if(path.is_absolute()){
		str = path.relative_path().string();
	}
	return !(boost::regex_search(str.begin(), str.end(), this->regex));
}

const std::string Dir::pwd() const{
	return path.string();
}

bool Dir::create(){
	return fs::create_directories(path);
}

bool Dir::create(string path){
	Dir dir(this->pwd());
	dir.cd(path);
	return dir.create();
}

bool Dir::remove(){
	return fs::remove(path);
}

bool Dir::remove(string path){
	Dir dir(this->pwd());
	dir.cd(path);
	return dir.remove();
}

bool Dir::remove_all(){
	return fs::remove_all(path);
}

bool Dir::remove_all(string path){
	Dir dir(this->pwd());
	dir.cd(path);
	return dir.remove_all();
}

void Dir::cd(string path){
	fs::path pth(path);
	pth.is_complete();
	if(pth.is_absolute()){
		this->path = fs::system_complete(pth);
	}else if(pth.is_relative()){
		this->path = fs::system_complete(this->path/pth);
	}else{
		throw Exception("path error");
	}
}

const char* Dir::test(){
	//boost::filesystem::path dir = boost::filesystem::system_complete("./"); 
	//boost::filesystem::path file("..\\..\\test\\test\\test");
	//boost::filesystem::path path = dir / file;

	//try{
	//	fs::create_directories(fs::path(":dir"),);
	//}catch(...){
	//	cout << "eee" << endl;
	//}

	fstream file;
	file.open("test.txt",ios::in);

	string ss;

	getline(file,ss);

	file.close();

	if(boost::regex_search(ss.begin(), ss.end(), boost::regex("\n")))
		cout << "null" << endl;

	fs::path pp(ss);

	Dir dir(ss);
	dir.cd("test2");
	dir.create("..");
	//dir.remove();
	dir.remove("..");

	//cout << dir.pwd() << endl;

	//cout << boost::filesystem::system_complete(file).relative_path().string() << endl;

	//cout << dir.string() << endl;
	//cout << boost::filesystem::system_complete(file).string() << endl;
	//cout << path.string() << endl;

	//cout << dir.parent_path().string() << endl;

	return "";
}

}