#include "Senary.h"

namespace pro{

Senary::Senary(void)
{
}

Senary::~Senary(void)
{
}

void Senary::init(int dec){
	int e=0;
	int co_num = dec;

	// Œ…”‚ÌŒˆ’è
	while(co_num/=6){
		e++;
	}

	while(e){
		this->num.push_back(dec/pow(6,e));
		int pw = pow(6,e);
		dec = dec%pw;
		e--;
	}

	this->num.push_back(dec);

}

void Senary::inits(vector<short> senary){
	num = senary;
}


void Senary::display(){
	for(int i=0;i<num.size();i++){
		std::cout<<num[i]<<std::flush;
	}
	std::cout<<std::endl;
}

int Senary::getDec(){
	int dec=0;
	for(int i=0;i<num.size();i++){
		dec += pow(6,num.size()-1-i)*num[i];
	}
	return dec;
}

int Senary::size() const{
	return num.size();
}

short Senary::operator[](int i){
	return num[i];
}

}