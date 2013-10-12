#include "Quinary.h"

namespace pro{

Quinary::Quinary(void)
{
}


Quinary::~Quinary(void)
{
}

void Quinary::init(int dec){
	int e=0;
	int co_num = dec;

	// Œ…”‚ÌŒˆ’è
	while(co_num/=5){
		e++;
	}

	while(e){
		this->num.push_back(dec/pow(5,e));
		int pw = pow(5,e);
		dec = dec%pw;
		e--;
	}

	this->num.push_back(dec);

}

void Quinary::initq(vector<short> quinary){
	num = quinary;
}


void Quinary::display(){
	for(int i=0;i<num.size();i++){
		std::cout<<num[i]<<std::flush;
	}
	std::cout<<std::endl;
}

int Quinary::getDec(){
	int dec=0;
	for(int i=0;i<num.size();i++){
		dec += pow(5,num.size()-1-i)*num[i];
	}
	return dec;
}

int Quinary::size() const{
	return num.size();
}

short Quinary::operator[](int i){
	return num[i];
}

}