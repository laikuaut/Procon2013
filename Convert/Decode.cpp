#include "Decode.h"

namespace pro{

Decode::Decode(void)
{
}


Decode::~Decode(void)
{
}

void Decode::init(){
	diceDecode.init();
}

void Decode::run(){
	diceDecode.drawing();
	//diceCodeDecode.init("DiceDecode.txt");
	//diceCodeDecode.output();
	//codeDecode.init("CodeDecode.txt");
	//codeDecode.output();
}

}