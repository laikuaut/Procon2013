#include "DiceCodeDecode.h"

namespace pro{

DiceCodeDecode::DiceCodeDecode(void)
{
}


DiceCodeDecode::~DiceCodeDecode(void)
{
}

void DiceCodeDecode::init(string name){
	fileRead(name);
	slvDice();
}

void DiceCodeDecode::fileRead(string name){
	std::ifstream ifs;
	ifs.open(name);
	int code;
	int count=0;
	while(1){
		ifs>>code;
		if(ifs.eof()) break;
		dice[count++]=code;
	}
	dice[count] = '\0';
	ifs.close();
}

void DiceCodeDecode::slvDice(){
	int i, j, tmp;
	//FILE *in;
	//fopen_s(&in,name.c_str(),"r");
	//FILE *out;
	//fopen_s(&out,("out_"+name).c_str(),"w");


	//fgets(dice, STRMAX*8+1, in);
	for(i=0;i<STRMAX*8;i++) binary[i] = 0;
	binary[0] = 1;
	for(i = 0, j = 0; dice[i] != '\0'; ++i){
		j = j + dice[i];
		binary[j] = 1;
	}

	for(i=j;i<STRMAX*8;i++)
		binary[i] = -1;

	for(i = 0; binary[i*8] != -1; ++i)
		codes.push_back(binary[i*8+1] + binary[i*8+2] * 2 + binary[i*8+3] * 4 + binary[i*8+4] * 8 + binary[i*8+5] * 16 + binary[i*8+6]*32 + binary[i*8+7]*64);
		//str[i] = binary[i*8+1] + binary[i*8+2] * 2 + binary[i*8+3] * 4 + binary[i*8+4] * 8 + binary[i*8+5] * 16 + binary[i*8+6]*32 + binary[i*8+7]*64;

	//fprintf(out, "%s", str);

	//fclose(in);
	//fclose(out);
}

void DiceCodeDecode::output(){
	std::ofstream ofs;
	ofs.open("CodeDecode.txt");
	for(int i=0;i<codes.size();i++){
		ofs<<codes[i]<<" "<<std::flush;
	}
	ofs.close();
}

}