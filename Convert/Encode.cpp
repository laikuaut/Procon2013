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

	// first step
		// CodeEncode
		//codeEncode.output();
		codeEncode.outputRunlength();

	// second step
		// SenaryEncode
		senaryEncode.init("CodeEncode.txt");
		senaryEncode.output();

		// QuinaryEncode	
		//quinaryEncode.init("CodeEncode.txt");
		//quinaryEncode.output();

		// DiceCodeEncode
		//diceCodeEncode.init("CodeEncode.txt");
		//diceCodeEncode.outputRunlength();

	diceEncode.init("DiceEncode.txt");
	diceEncode.drawing();
}

}