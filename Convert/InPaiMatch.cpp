#include "InPaiMatch.h"

#include<sstream>

namespace pro{

InPaiMatch::InPaiMatch(void)
{
}


InPaiMatch::~InPaiMatch(void)
{
}

void InPaiMatch::init(){
	pos = 0;
	dir_num = 0;
	file_num = 0;
	line_num = 0;
	char_num = 0;
	count = 0;
}

bool InPaiMatch::next(){

}

void InPaiMatch::open(){
	std::stringstream ss;
	ss << digits << ".txt";
	std::stringstream ss_count;
	ss_count << digits << "_count.txt";
	fs.open(path.pwd(ss.str()),std::ios::out);
	count_fs.open(path.pwd(ss_count.str()),std::ios::out);
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

int InPaiMatch::getCount() const{
	return count;
}

void InPaiMatch::setNum(const char* str){
	num_str.setNum(str);
}

}
