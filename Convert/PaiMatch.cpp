#include "PaiMatch.h"


namespace pro{

PaiMatch::PaiMatch(int digits, CharArrayNumeric::NumKind kind){
	init();

	num_str.init(digits,kind);

	this->digits = digits;
	
}

PaiMatch::~PaiMatch(void){
	close();
}

void PaiMatch::init(){
	path = Dir("./Resource/PAI_MATCH/",false);
	path.create(Dir::OVER_WRITE);
}

void PaiMatch::close(){
	fs.close();
	count_fs.close();
}

int PaiMatch::getDigits() const{
	return digits;
}

}
