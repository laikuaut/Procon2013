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

Dir::Dir(void)
{
	path = fs::system_complete(".");
	ErrorShow = false;
}

Dir::Dir(const fs::path& path){
	if(!isPath(path))
		throw DirException(DirException::PATH_ERROR,path.string(),"Dir.cpp","Dir::Dir(boost::filesystem::path&)");
	this->path = fs::system_complete(path);
}

Dir::~Dir(void)
{

}

bool Dir::isPath(const fs::path& path){
	fs::path pth = path.string();
	string str_path;
	if(pth.is_absolute()){
		str_path = pth.relative_path().string();
	}
	return !(boost::regex_search(str_path.begin(), str_path.end(), boost::regex(DIR_REGEX_STR)));
}

const std::string Dir::pwd() const{
	return path.string();
}

bool Dir::create(int flag){
	try{
		if(fs::exists(path)){
			if(flag == 0)
				throw DirException(DirException::EXIST,pwd(),"Dir.cpp","Dir::create()");
			else if(flag%2==1){
				string default_path = pwd();
				int num=1;
				stringstream ss;
				do{
					ss.str("");
					ss.clear(stringstream::goodbit);
					ss << default_path << "_" << num++;
					cd(ss.str());
				}while(!fs::create_directory(pwd()));
				return true;
			}else if((flag>>1)%2==1){
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
			}else if((flag>>2)%2==1){
				remove();
				return fs::create_directory(path);
			}
		}else{
			if((flag>>3)%2==0){
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

bool Dir::create(const fs::path& path, int flag){
	Dir dir(this->pwd());
	try{
		dir.cd(path,DirException(DirException::PATH_ERROR,path.string(),"Dir.cpp","Dir::create(string,int)"));
	}catch(const DirException& e){
		if(ErrorShow) e.showError();
		return false;
	}
	return dir.create(flag);
}

bool Dir::remove() const{
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

bool Dir::remove(const fs::path& path) const{
	Dir dir(this->pwd());
	try{
		dir.cd(path,DirException(DirException::PATH_ERROR,path.string(),"Dir.cpp","Dir::remove(string)"));
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

boost::uintmax_t Dir::remove_all() const{
	try{
		return fs::remove_all(path);
	}catch(const fs::filesystem_error& e){
		cout << e.what() << endl;
		cout << "予期せぬエラー：[Dir.cpp,Dir::remove_all()]" << endl;
		throw e;
	}
}

boost::uintmax_t Dir::remove_all(const fs::path& path) const{
	Dir dir(this->pwd());
	try{
		dir.cd(path,DirException(DirException::PATH_ERROR,path.string(),"Dir.cpp","Dir::remove_all(string)"));
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

void Dir::cd(const fs::path& path){
	fs::path pth(path.string());
	if(!isPath(path))
		throw DirException(DirException::PATH_ERROR,path.string(),"Dir.cpp","Dir::cd(string)");
	if(pth.is_absolute()){
		this->path = fs::system_complete(pth);
	}else if(pth.is_relative()){
		this->path = fs::system_complete(this->path/pth);
	}
}

void Dir::cd(const fs::path& path,const DirException& e){
	fs::path pth(path.string());
	try{
		if(!isPath(path))
			throw DirException(DirException::PATH_ERROR,path.string(),"Dir.cpp","Dir::cd(string,DirException)");
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

void Dir::setErrorShow(bool errorShow){
	ErrorShow = errorShow;
}

const char* Dir::test(){

	//fstream file;
	//file.open("test.txt",ios::in);

	//string ss;

	//getline(file,ss);

	//file.close();

	//assert(true);

	//fs::path pp(ss);

	//Dir dir(ss);
	//dir.create(Dir::OVER_WRITE_REMOVE_ALL);
	//dir.remove();

	return "";
}



}

