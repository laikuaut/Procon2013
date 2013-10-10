#include "StringDecode.h"

namespace pro{

StringDecode::StringDecode(void)
{
}


StringDecode::~StringDecode(void)
{
}

void StringDecode::init(){

}

void StringDecode::slvDice(string name){
	int i, j, tmp;
	FILE *in;
	fopen_s(&in,name.c_str(),"r");
	FILE *out;
	fopen_s(&out,("out_"+name).c_str(),"w");


	fgets(dice, STRMAX*8+1, in);
	for(i=0;i<STRMAX*8;i++) binary[i] = 0;
	binary[0] = 1;
	for(i = 0, j = 0; dice[i] != '\0'; ++i){
		j = j + dice[i] - '0';
		binary[j] = 1;
	}
	binary[j] = -1;

	for(i = 0; binary[i*8] != -1; ++i)
		str[i] = binary[i*8+1] + binary[i*8+2] * 2 + binary[i*8+3] * 4 + binary[i*8+4] * 8 + binary[i*8+5] * 16 + binary[i*8+6]*32 + binary[i*8+7]*64;
	binary[i] = '\0';

	fprintf(out, "%s", str);

	fclose(in);
	fclose(out);
}

}