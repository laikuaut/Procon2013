#include "InPaiDivide.h"

#include<sstream>

namespace pro{

InPaiDivide::InPaiDivide(void)
{
	getIniSetting();
	getLine(1,1,1);
}

InPaiDivide::~InPaiDivide(void)
{
}

long InPaiDivide::getDirNum() const{
	return dir_num;
}

int InPaiDivide::getOneLineNum() const{
	return one_line_num;
}

int InPaiDivide::getLineNum() const{
	return line_num;
}

int InPaiDivide::getFileNum() const{
	return file_num;
}

long InPaiDivide::getNowDir() const{
	return now_dir;
}

int InPaiDivide::getNowFile() const{
	return now_file;
}

int InPaiDivide::getNowLine() const{
	return now_line;
}

const CharArray& InPaiDivide::getLine(){
	return c_str;
}

const CharArray& InPaiDivide::getLine(long dir_num,int file_num,int line_num){

	open(dir_num,file_num);

	getLine(line_num);

	return c_str;
}

void InPaiDivide::open(long dir_num,int file_num){	
	setDir(dir_num);
	setFile(file_num);
}

void InPaiDivide::close(){
	fs.close();
}

const CharArray& InPaiDivide::getLine(int line_num){

	setLine(line_num);

	return c_str;

}

void InPaiDivide::setDir(long dir_num){

	if(dir_num > this->dir_num || dir_num < 1)
		throw OutOfRangeException<long>(dir_num,"dir_num","InPaiDivide.cpp","InPaiDivide::setDir(long)",__LINE__);

	std::stringstream d_ss;
	d_ss << dir_num;
	path = Dir(base_path.pwd(d_ss.str()));
	if(!path.isDirectory())
		throw DirException(DirException::NOT_EXIST,path.pwd(),"InPaiDivide.cpp","InPaiDivide::setDir(long)",__LINE__);
	now_dir = dir_num;
}

void InPaiDivide::setFile(int file_num){

	if(fs.is_open())
		close();
	if(now_dir == dir_num){
		if(file_num > last_file_num || file_num < 1)
			throw OutOfRangeException<long>(file_num,"file_num","InPaiDivide.cpp","InPaiDivide::setFile(int)",__LINE__);
	}else{
		if(file_num > this->file_num || file_num < 1)
			throw OutOfRangeException<long>(file_num,"file_num","InPaiDivide.cpp","InPaiDivide::setFile(int)",__LINE__);
	}

	std::stringstream f_ss;
	f_ss << name << "_" << file_num << ".txt";
	fs.open(path.pwd(f_ss.str()));
	if(fs.fail())
		throw FileException(FileException::OPEN,path.pwd(name),"Pai.cpp","InPaiDivide::getLine(long,int,int)",__LINE__);
	
	now_file = file_num;
}

void InPaiDivide::setLine(int line_num){
	//char *c_str;
	int one_line;

	if( now_dir == this->dir_num && now_file == this->last_file_num){
		if(line_num > last_line_num || line_num < 1)
			throw OutOfRangeException<long>(file_num,"line_num","InPaiDivide.cpp","InPaiDivide::setLine(int)",__LINE__);
	}else{
		if(line_num > this->line_num || line_num < 1)
			throw OutOfRangeException<long>(file_num,"line_num","InPaiDivide.cpp","InPaiDivide::setLine(int)",__LINE__);
	}

	if( now_dir == this->dir_num &&
		now_file == this->last_file_num &&
		line_num == this->last_line_num){
		one_line = last_digits+1;
	}else{
		one_line = one_line_num+1;
	}

	fs.seekg((line_num-1)*(one_line_num+2),std::ios_base::beg);

	char* str = new char[one_line];

	fs.getline(str,one_line);

	c_str = str;

	now_line = line_num;
}

bool InPaiDivide::nextDir(){
	try{
		setDir(now_dir+1);
	}catch(const OutOfRangeException<long>&){
		return false;
	}
	return true;
}

bool InPaiDivide::nextFile(){
	try{
		setFile(now_file+1);
	}catch(const OutOfRangeException<long>&){
		if(nextDir()){
			setFile(1);
			return true;
		}
		return false;
	}
	return true;
}

const CharArray& InPaiDivide::nextLine(){
	try{
		return getLine(now_line+1);
	}catch(const OutOfRangeException<long>&){
		if(nextFile())
			return getLine(1);
	}
	c_str.clear(); // ç≈å„Ç‹Ç≈çsÇ≠Ç∆c_str.lengthÇ™0Ç∆Ç»ÇÈÅB
	return c_str;
}

}