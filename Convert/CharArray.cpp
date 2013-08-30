#include "CharArray.h"

#include<sstream>

namespace pro{

CharArray::CharArray(void){
	clear();
}

CharArray::CharArray(int length)
{
	zero(length);
}

CharArray::CharArray(const char* c_str){

	create(c_str);

}

CharArray::CharArray(const char* c_str,int length){

	create(c_str,length);

}

CharArray::~CharArray(void)
{
	delete c_str;
}

void CharArray::create(const CharArray& obj){
	create(obj.c_str,obj.length);
}

void CharArray::create(const char* c_str){
	std::stringstream ss;
	ss << c_str;
	length = ss.str().length();

	create(c_str,length);
}

void CharArray::create(const char* c_str,int length){
	clear();
	this->length = length;
	this->c_str = new char[length+1];

	for(int i=0;i<length;i++){
		this->c_str[i] = c_str[i];
	}
	this->c_str[length] = '\0';
	//delete c_str;
}

void CharArray::clear(){
	delete[] c_str;
	c_str = nullptr;
	length = 0;
}

void CharArray::copy(CharArray& obj) const{
	obj.create(c_str,length);
}

void CharArray::copy(char* c_str) const{
	for(int i=0;i<length+1;i++){
		c_str[i] = this->c_str[i];
	}
}

void CharArray::copy(char* c_str,int& length) const{
	length = this->length;
	copy(c_str);
}

void CharArray::zero(){
	allSame(0);
}

void CharArray::zero(int length){
	allSame(0,length);
}

void CharArray::allSame(char c){
	for(int i=0;i<length;i++)
		c_str[i] = c;
	c_str[length] = '\0';
}

void CharArray::reverse(){
	const char* tmp = getCstr();
	for(int i=0;i<length;i++){
		this->c_str[i] = tmp[length-i-1];
	}
	this->c_str[length] = '\0';
}

void CharArray::allSame(char c,int length){
	c_str = new char[length+1];
	this->length = length;
	allSame(c);
}

void CharArray::push_back(const CharArray& obj){
	push_back(obj.c_str,obj.length);
}

void CharArray::push_back(const char* c_str){
	std::stringstream ss;
	ss<<this->c_str;
	ss<<c_str;
	length = ss.str().length();
	create(ss.str().c_str(),length);
}

void CharArray::push_back(const char* c_str,int length){
	length += this->length;
	char* tmp = new char[length+1];
	for(int i=0;i<this->length;i++){
		tmp[i] = this->c_str[i];
	}
	for(int i=this->length;i<length;i++){
		tmp[i] = c_str[i-this->length];
	}
	tmp[length] = '\0';
	create(tmp,length);
	delete tmp;
}

void CharArray::push_flont(const CharArray& obj){
	push_flont(obj.c_str,obj.length);
}

void CharArray::push_flont(const char* c_str){
	std::stringstream ss;
	ss<<c_str;
	ss<<this->c_str;
	length = ss.str().length();
	create(ss.str().c_str(),length);
}

void CharArray::push_flont(const char* c_str,int length){
	const int L = length + this->length;
	char* tmp = new char[L+1];
	for(int i=0;i<length;i++){
		tmp[i] = c_str[i];
	}
	for(int i=length;i<L;i++){
		tmp[i] = this->c_str[i-length];
	}
	tmp[L] = '\0';
	create(tmp,L);
	delete tmp;
}

void CharArray::pop_flont(int length){
	if(this->length <= length){
		clear();
		return;
	}
	char* tmp = new char[this->length - length + 1];
	for(int i=length;i<this->length;i++){
		tmp[i-length] = this->c_str[i];
	}
	tmp[this->length - length] = '\0';
	create(tmp,this->length-length);
	delete tmp;
}

void CharArray::pop_back(int length){
	if(this->length <= length){
		clear();
		return;
	}
	char* tmp = new char[this->length - length + 1];
	for(int i=0;i<this->length-length;i++){
		tmp[i] = this->c_str[i];
	}
	tmp[this->length - length] = '\0';
	create(tmp,this->length-length);
	delete tmp;
}

bool CharArray::Equal(const CharArray& obj) const{
	if(length!=obj.length)
		return false;
	for(int i=0;i<length;i++){
		if(c_str[i] != obj.c_str[i]) return false;
	}
	return true;
}

bool CharArray::Equal(const char* c_str) const{
	CharArray obj(c_str);
	return Equal(obj);
}

char CharArray::getChar(int n){
	int N;
	if(n<0){
		N=length+n;
	}else{
		N=n;
	}
	if(N<0 || N>length)
		throw OutOfRangeException<int>(n,"n","CharArray.cpp","CharArray::getChar(int)",__LINE__);
	return c_str[N];
}

int CharArray::getLength() const{
	return this->length;
}

const char* CharArray::getCstr() const{
	char* c_str = new char[length];
	copy(c_str);
	return c_str;
}

char CharArray::operator[](int n){
	try{
		return getChar(n);
	}catch(OutOfRangeException<int> e){
		throw OutOfRangeException<int>(n,"n","CharArray.cpp","CharArray::operator[](int)",__LINE__);
	}
}

char CharArray::operator()(int n){
	try{
		return getChar(n);
	}catch(OutOfRangeException<int> e){
		throw OutOfRangeException<int>(n,"n","CharArray.cpp","CharArray::operator()(int)",__LINE__);
	}
}

const char* CharArray::operator()(int s_num,int e_num){
	if(e_num < s_num)
		// ExceptionAgument‚ðì¬‚·‚é‚±‚Æ
		throw Exception("ˆø”‚ª³‚µ‚­‚È‚¢","CharArray.cpp","CharArray::operator()(int,int)",__LINE__);
	else if(s_num<0||s_num>length)
		throw OutOfRangeException<int>(s_num,"s_num","CharArray.cpp","CharArray::operator()(int,int)",__LINE__);
	else if(e_num<0||e_num>length)
		throw OutOfRangeException<int>(e_num,"e_num","CharArray.cpp","CharArray::operator()(int,int)",__LINE__);

	char* c_str = new char[e_num - s_num+1];
	for(int i=s_num;i<e_num;i++)
		c_str[i-s_num] = this->c_str[i];
	c_str[e_num-s_num] = '\0';
	return c_str;
}

CharArray::operator const char* () const{	
	return this->c_str;
}

CharArray::operator char* (){
	return this->c_str;
}

const CharArray& CharArray::operator=(const char* c_str){
	create(c_str);
	return(*this);
}

//const CharArray& CharArray::operator=(CharArray& obj){
//	create(obj);
//	return(*this);
//}

const CharArray& CharArray::operator+=(const char* c_str){
	push_back(c_str);
	return(*this);
}

//const CharArray& CharArray::operator+=(CharArray& obj){
//	push_back(obj);
//	return(*this);
//}

const char* CharArray::operator+(const char* c_str){
	CharArray tmp(this->c_str,this->length);
	tmp.push_back(c_str);
	return(tmp.getCstr());
}

//const char* CharArray::operator+(const CharArray& obj){
//	CharArray tmp;
//	tmp.create(this->c_str);
//	tmp.push_back(obj);
//	return(tmp.getCstr());
//}

bool CharArray::operator==(const CharArray& obj) const{
	return Equal(obj);
}

bool CharArray::operator==(const char* c_str) const{
	return Equal(c_str);
}

bool CharArray::operator!=(const CharArray& obj) const{
	return !Equal(obj);
}

bool CharArray::operator!=(const char* c_str) const{
	return !Equal(c_str);
}

}