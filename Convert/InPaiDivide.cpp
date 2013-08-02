#include "InPaiDivide.h"

#include<sstream>

namespace pro{

InPaiDivide::InPaiDivide(void)
{
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


const char* InPaiDivide::getLine(long dir_num,int file_num,int line_num){
	std::ifstream in_file;
	
	std::stringstream d_ss;
	std::stringstream f_ss;
	d_ss << dir_num;
	f_ss << name << "_" << file_num << ".txt";

	path = Dir(base_path.pwd(d_ss.str()));

	in_file.open(path.pwd(f_ss.str()));
	if(in_file.fail())
		throw FileException(FileException::OPEN,path.pwd(name),"Pai.cpp","InPaiDivide::getLine(long,int,int)",__LINE__);

	char *c_str;
	int one_line;

	if( dir_num == this->dir_num &&
		file_num == this->last_file_num &&
		line_num == this->last_line_num){
		one_line = last_digits+1;
	}else{
		one_line = one_line_num+1;
	}

	c_str = new char[one_line];

	in_file.seekg((line_num-1)*(one_line+1),std::ios_base::beg);

	in_file.getline(c_str,one_line);

	in_file.close();

	return c_str;
}

}