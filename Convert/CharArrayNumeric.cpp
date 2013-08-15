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

void CharArrayNumeric::init(int length,NumKind kind,const char* str,int num){
	setLength(length);
	setNumKind(kind,str,num);
}

void CharArrayNumeric::setLength(int length){
	first_num(length);
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
	case STRING:
		numLength = 86;
		char* str = new char[numLength];
		for(int i=33;i<123;i++){
			if(i<91 || i>94)
				str[i] = i;
		}
		numString = str;
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

CharArrayNumeric::NumKind CharArrayNumeric::getNumKind() const{
	return kind;
}

const char* CharArrayNumeric::getNumString() const{
	return numString;
}

bool CharArrayNumeric::add(){
	int num;
	for(int i=length-1;i>=0;i--){
		num = getNumStringNum(c_str[i]);
		if(++num == numLength){
			if(0==i)
				return false;
			c_str[i] = numString[0];
		}else{
			c_str[i] = numString[num];
			break;
		}
	}
	return true;
}

char CharArrayNumeric::getChar(int n){
	return CharArray::getChar(n);
}

int CharArrayNumeric::getLength() const{
	return CharArray::getLength();
}

const char* CharArrayNumeric::getCstr() const{
	return CharArray::getCstr();
}

bool CharArrayNumeric::sub(){
	int num;
	for(int i=length-1;i>=0;i--){
		num = getNumStringNum(c_str[i]);
		if(--num == -1){
			if(0==i){
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
	bool flag=false;
	for(int i=0;i<tmp.getLength();i++){
		for(int j=0;j<numLength;j++){
			if(tmp[i] == numString[j])
				flag = true;
		}
		if(!flag)
			throw Exception("文字列に不正な値があります。","CharArrayNumeric.cpp","CharArrayNumeric::setNum(const char*)",__LINE__);
	}
	create(str);
}

void CharArrayNumeric::setNum(const char* str,int length){
	CharArray tmp(str,length);
	bool flag=false;
	for(int i=0;i<tmp.getLength();i++){
		for(int j=0;j<numLength;j++){
			if(tmp[i] == numString[j])
				flag = true;
		}
		if(!flag)
			throw Exception("文字列に不正な値があります。","CharArrayNumeric.cpp","CharArrayNumeric::setNum(const char*)",__LINE__);
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
	
bool CharArrayNumeric::Equal(const CharArray& obj) const{
	return CharArray::Equal(obj);
}

bool CharArrayNumeric::Equal(const char* c_str) const{
	return CharArray::Equal(c_str);
}

bool CharArrayNumeric::operator==(const CharArray& obj) const{
	return Equal(obj);
}

bool CharArrayNumeric::operator==(const char* c_str) const{
	return Equal(c_str);
}

void CharArrayNumeric::first_num(){
	allSame(numString[0]);
}

void CharArrayNumeric::first_num(int length){
	allSame(numString[0],length);
}

void CharArrayNumeric::last_num(){
	allSame(numString[numLength-1]);
}

void CharArrayNumeric::last_num(int length){
	allSame(numString[numLength-1],length);
}

CharArrayNumeric::operator const char* () const{
	return c_str;
}

CharArrayNumeric::operator char* (){
	return c_str;
}





}