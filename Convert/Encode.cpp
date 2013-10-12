#include "Encode.h"

#include<iostream>

using namespace std;

namespace pro{

Encode::Encode(void)
{
}


Encode::~Encode(void)
{
}

void Encode::init(string name){
	codeEncode.init(name);
}

void Encode::run(){
	codeEncode.output();
	diceCodeEncode.init("CodeEncode.txt");
	diceCodeEncode.outputRunlength();
	diceEncode.init("DiceEncode.txt");
	diceEncode.drawing();
}

}