#include "CharArrayNumeric.h"

namespace pro{

CharArrayNumeric::CharArrayNumeric(void) : CharArray()
{
	setNumKind(DEC);
	length = 1;
}

CharArrayNumeric::CharArrayNumeric(int length)
{
	setNumKind(DEC);
	allSame(numString[0],this->length=length);
}

CharArrayNumeric::CharArrayNumeric(NumKind kind) : CharArray(){
	setNumKind(kind);
	length = 1;
}

CharArrayNumeric::CharArrayNumeric(NumKind kind
								   ,int length){
	setNumKind(kind);
	allSame(numString[0],this->length=length);
}


CharArrayNumeric::~CharArrayNumeric(void)
{
}

void CharArrayNumeric::setNumKind(NumKind kind,const char* str,int num){
	this->kind = kind;
	switch (kind)
	{
	case DEC:
		numString = "0123456789";
		numLength = 10;
		break;
	case OCT:
		numString = "01234567";
		numLength = 8;
		break;
	case HEX:
		numString = "0123456789abcdef";
		numLength = 16;
		break;
	case ORIGINAL:
		numString = str;
		numLength = num;
		break;
	default:
		break;
	}
}

int CharArrayNumeric::getNumStringNum(char c){
	for(int i=0;i<numLength;i++){
		if(numString[i]==c)
			return i;
	}
	return -1;
}

int CharArrayNumeric::getNumLength() const{
	return numLength;
}

const char* CharArrayNumeric::getNumString() const{
	return numString;
}

bool CharArrayNumeric::add(){
	int num;
	for(int i=0;i<length;i++){
		num = getNumStringNum(c_str[i]);
		if(++num == numLength){
			if(length-1==i)
				return false;
			c_str[i] = numString[0];
		}else{
			c_str[i] = numString[num];
			break;
		}
	}
	return true;
}

bool CharArrayNumeric::sub(){
	int num;
	for(int i=0;i<length;i++){
		num = getNumStringNum(c_str[i]);
		if(--num == -1){
			if(length-1==i){
				allSame(numString[0]);
				return false;
			}
			c_str[i] = numString[numLength-1];
		}else{
			c_str[i] = numString[num];
			break;
		}
	}
	return true;
}

bool CharArrayNumeric::add(int num){
	for(int i=0;i<num;i++)
		if(!add()) return false;
	return true;
}

bool CharArrayNumeric::sub(int num){
	for(int i=0;i<num;i++)
		if(!sub()) return false;
	return true;
}

void CharArrayNumeric::setNum(const char* str){
	CharArray tmp(str);
	for(int i=0;i<tmp.getLength();i++){
		for(int j=0;j<numLength;j++){
			if(tmp[i] != numString[j])
				throw Exception("•¶Žš—ñ‚É•s³‚È’l‚ª‚ ‚è‚Ü‚·B","CharArrayNumeric.cpp","CharArrayNumeric::setNum(const char*)",__LINE__);
		}
	}
	create(str);
}

const char* CharArrayNumeric::operator++(int){
	CharArray tmp(this->c_str,this->length);
	add();
	return tmp.getCstr();
}

const CharArrayNumeric& CharArrayNumeric::operator++(){
	add();
	return (*this);
}

const CharArrayNumeric& CharArrayNumeric::operator+=(int num){
	add(num);
	return (*this);
}

const char* CharArrayNumeric::operator--(int){
	CharArray tmp(this->c_str,this->length);
	sub();
	return tmp.getCstr();
}

const CharArrayNumeric& CharArrayNumeric::operator--(){
	sub();
	return (*this);
}

const CharArrayNumeric& CharArrayNumeric::operator-=(int num){
	sub(num);
	return (*this);
}
}