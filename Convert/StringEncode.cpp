#include "StringEncode.h"

namespace pro{

StringEncode::StringEncode(void)
{
}


StringEncode::~StringEncode(void)
{
}

void StringEncode::loadDice(string name){

	FILE *in;
	fopen_s(&in,name.c_str(),"r");
	FILE *out;
	fopen_s(&out,("out_"+name).c_str(),"w");

	int i, j, tmp;
	fgets(str, STRMAX, in);
	for(i = 0; i < STRMAX && str[i] != '\0' && str[i] != '\n'; ++i){
		tmp = str[i];
		binary[i*8] = 1;
		for(j = 1; j < 8; ++j){
			binary[i*8 + j]  = tmp % 2;
			tmp             /= 2;
		}
	}
	binary[i*8]  = ENDBINARY;
	
	for(i = 0, j = 0; binary[j] != ENDBINARY; i++){
		tmp     = j;
		for(++j;binary[j] == 0; ++j);
		dice[i] = j - tmp;
	}
	dice[i] = 0;

	for(i = 1; dice[i-1] != 0; ++ i){
		fprintf(out, "%d", dice[i-1]);
	}

	fclose(in);
	fclose(out);

}

}