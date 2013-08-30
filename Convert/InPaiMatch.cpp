#include "InPaiMatch.h"

#include<sstream>

namespace pro{

InPaiMatch::InPaiMatch(int digits, CharArrayNumeric::NumKind kind)
{
	init();

	num_str.init(digits,kind);

	this->digits = digits;
}


InPaiMatch::~InPaiMatch(void)
{
	close();
}

void InPaiMatch::init(){
	path = Dir("./Resource/PAI_MATCH/",false);
	pos = 0;
	dir_num = 0;
	file_num = 0;
	line_num = 0;
	char_num = 0;
	count = 0;
	flag_count=0;
	num_str.first_num();
	setNum();
}

void InPaiMatch::open(){
	if(fs.is_open())
		close();
	std::stringstream ss;
	ss << digits << ".txt";
	std::stringstream ss_count;
	ss_count << digits << "_count.txt";
	fs.open(path.pwd(ss.str()),std::ios::in);
	if(fs.fail()){ 
		//std::cout << "fs not" << std::endl;
		throw FileException(FileException::NOT_EXIST,path.pwd(ss.str()),"InPaiMatch.cpp","InPaiMatch::open()",__LINE__);
	}
	count_fs.open(path.pwd(ss_count.str()),std::ios::in);
	if(count_fs.fail()){
		//std::cout << "count_fs not" << std::endl;
		throw FileException(FileException::NOT_EXIST,path.pwd(ss_count.str()),"InPaiMatch.cpp","InPaiMatch::open()",__LINE__);
	}
}

void InPaiMatch::nowDisplay(){
	std::cout << "Digits:"	<< getDigits()	<< std::endl;
	std::cout << "NumStr:"	<< getNumStr()	<< std::endl;
	std::cout << "Count:"	<< getCount()	<< std::endl;
	std::cout << "DirNum:"	<< getDirNum()	<< std::endl;
	std::cout << "FileNum:" << getFileNum()	<< std::endl;
	std::cout << "LineNum:" << getLineNum()	<< std::endl;
	std::cout << "CharNum:" << getCharNum()	<< std::endl;
	std::cout << std::endl;
}

void InPaiMatch::setDigits(int digits){
	this->digits = digits;
}

int InPaiMatch::getDirNum() const{
	return dir_num;
}

int InPaiMatch::getFileNum() const{
	return file_num;
}

int InPaiMatch::getLineNum() const{
	return line_num;
}

int InPaiMatch::getCharNum() const{
	return char_num;
}

long long unsigned InPaiMatch::getCount() const{
	return count;
}

const char* InPaiMatch::getNumStr() const{
	return num_str;
}

bool InPaiMatch::setNum(){
	return setNum(num_str);
}

bool InPaiMatch::setNum(const char* str){

	std::stringstream ss;
	ss << str;
	num_str.setLength(ss.str().length());
	setDigits(num_str.getLength());

	try{
		open();
	}catch(const FileException&){
		return false;
	}
	
	do{
		if(!nextNum())
			return false;
	}while(!num_str.Equal(str));

	return true;
}

bool InPaiMatch::next(){
	if(count == flag_count) return false;
	fs >> dir_num;
	fs >> file_num;
	fs >> line_num;
	fs >> char_num;
	flag_count++;
	return true;
}

bool InPaiMatch::nextNum(){

	string str;
	int pos;
	count_fs >> str;
	num_str.setNum(str.c_str());
	count_fs >> count;
	count_fs >> pos;
	this->pos = pos;
	if(count_fs.eof()) 
		return false;
	
	fs.seekg(pos,std::ios::beg);
	string s;
	fs >> s;
	if(!num_str.Equal(s.c_str()))
		return false;
	flag_count=0;

	return true;
}

void InPaiMatch::Reset(){
	const char *str = num_str.getCstr();
	init();
	setNum(str);
}

}
