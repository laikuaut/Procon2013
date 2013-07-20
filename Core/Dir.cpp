#include "Dir.h"

#include<iostream>
#include<cstring>
#include<fstream>
#include<sstream>
#include<cstdio>
#include<boost/regex.hpp>

using namespace std;
namespace fs = boost::filesystem;

namespace pro{

Dir::Dir(bool errorShow)
{
	path = fs::system_complete(".");
	ErrorShow = errorShow;
}

Dir::Dir(string path,bool errorShow){
	if(!isPath(path))
		throw DirException(DirException::PATH_ERROR,path,"Dir.cpp","Dir::Dir(string)");
	this->path = fs::system_complete(path);
	ErrorShow = errorShow;
}

Dir::~Dir(void)
{

}

bool Dir::isPath(string path){
	fs::path pth = path;
	if(pth.is_absolute()){
		path = pth.relative_path().string();
	}
	return !(boost::regex_search(path.begin(), path.end(), boost::regex(DIR_REGEX_STR)));
}

bool Dir::isPath(fs::path path){
	string str = path.string();
	if(path.is_absolute()){
		path = path.relative_path().string();
	}
	return !(boost::regex_search(str.begin(), str.end(), boost::regex(DIR_REGEX_STR)));
}

const std::string Dir::pwd() const{
	return path.string();
}

bool Dir::create(int option){
	try{
		if(fs::exists(path)){
			if(option == 0)
				throw DirException(DirException::EXIST,pwd(),"Dir.cpp","Dir::create()");
			else if(option%2==1){
				string default_path = pwd();
				int num=1;
				stringstream ss;
				do{
					ss.str("");
					ss.clear(stringstream::goodbit);
					ss << default_path << "_" << num++;
					cd(ss.str());
				}while(!fs::create_directory(pwd()));
			}else if((option>>1)%2==1){
				remove_all();
				// -----------------------------------
				// アクセス拒否対策　コード検討・・・
				while(fs::exists(path,boost::system::error_code()));
				for(int i=0;i<5;i++){
					if(fs::create_directory(path,boost::system::error_code()))
						return true;
				}
				// -----------------------------------
				return fs::create_directory(path);
			}else if((option>>2)%2==1){
				remove();
				return fs::create_directory(path);
			}
		}else{
			if((option>>3)%2==0){
				if(fs::create_directory(path))
					return true;
				throw DirException(DirException::NOT_PATH,pwd(),"Dir.cpp","Dir::create()");
			}
			else
				return fs::create_directories(path);
		}
	}catch(const DirException& e){
		if(ErrorShow) e.showError();
		return false;
	}catch(const fs::filesystem_error& e){
		cout << e.what() << endl;
		cout << "予期せぬエラー：[Dir.cpp,Dir::create()]" << endl;
		throw e;
	}
	return false;
}

bool Dir::create(string path, int option){
	Dir dir(this->pwd(),this->ErrorShow);
	try{
		dir.cd(path,DirException(DirException::PATH_ERROR,path,"Dir.cpp","Dir::create(string,int)"));
	}catch(const DirException& e){
		if(ErrorShow) e.showError();
		return false;
	}
	return dir.create(option);
}

bool Dir::remove(){
	try{
		if(!fs::exists(path))
			throw DirException(DirException::NOT_EXIST,path.string(),"Dir.cpp","Dir::remove()");
		else if(!fs::is_empty(path))
			throw DirException(DirException::NOT_EMPTY,path.string(),"Dir.cpp","Dir::remove()");
		return fs::remove(path);
	}catch(const DirException& e){
		if(ErrorShow) e.showError();
		return false;
	}catch(const fs::filesystem_error& e){
		cout << e.what() << endl;
		cout << "予期せぬエラー：[Dir.cpp,Dir::remove()]" << endl;
		throw e;
	}
}

bool Dir::remove(string path){
	Dir dir(this->pwd(),this->ErrorShow);
	try{
		dir.cd(path,DirException(DirException::PATH_ERROR,path,"Dir.cpp","Dir::remove(string)"));
		return dir.remove();
	}catch(const DirException& e){
		if(ErrorShow) e.showError();
		return false;
	}catch(const fs::filesystem_error& e){
		cout << e.what() << endl;
		cout << "予期せぬエラー：[Dir.cpp,Dir::remove(string)]" << endl;
		throw e;
	}
}

boost::uintmax_t Dir::remove_all(){
	try{
		return fs::remove_all(path);
	}catch(const fs::filesystem_error& e){
		cout << e.what() << endl;
		cout << "予期せぬエラー：[Dir.cpp,Dir::remove_all()]" << endl;
		throw e;
	}
}

boost::uintmax_t Dir::remove_all(string path){
	Dir dir(this->pwd(),this->ErrorShow);
	try{
		dir.cd(path,DirException(DirException::PATH_ERROR,path,"Dir.cpp","Dir::remove_all(string)"));
		return dir.remove_all();
	}catch(const DirException& e){
		if(ErrorShow) e.showError();
		return 0;
	}catch(const fs::filesystem_error& e){
		cout << e.what() << endl;
		cout << "予期せぬエラー：[Dir.cpp,Dir::remove_all(string)]" << endl;
		throw e;
	}
}

void Dir::cd(string path){
	fs::path pth(path);
	if(!isPath(path))
		throw DirException(DirException::PATH_ERROR,path,"Dir.cpp","Dir::cd(string)");
	if(pth.is_absolute()){
		this->path = fs::system_complete(pth);
	}else if(pth.is_relative()){
		this->path = fs::system_complete(this->path/pth);
	}
}

void Dir::cd(string path,DirException e){
	fs::path pth(path);
	try{
		if(!isPath(path))
			throw DirException(DirException::PATH_ERROR,path,"Dir.cpp","Dir::cd(string,DirException)");
	}catch(const DirException& ex){
		if(ErrorShow) ex.showError();
		throw e;
	}
	if(pth.is_absolute()){
		this->path = fs::system_complete(pth);
	}else if(pth.is_relative()){
		this->path = fs::system_complete(this->path/pth);
	}
}

const char* Dir::test(){

	fstream file;
	file.open("test.txt",ios::in);

	string ss;

	getline(file,ss);

	file.close();

	fs::path pp(ss);

	Dir dir(ss);
	dir.create(Dir::OVER_WRITE_REMOVE_ALL);
	//dir.remove();

	return "";
}

}