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

void DiceCodeDecode::initRunlength(string name){
	fileRead(name);
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

void DiceCodeDecode::slvDice(vector<int> dices){
	int i, j, tmp;
	for(int i=0;i<dices.size();i++){
		dice[i] = dices[i];
	}

	dice[dices.size()] = '\0';

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

}

vector<int> DiceCodeDecode::runlength(){
	int count;
	int _dice;
	vector<int> dices;
	for(int i=0;dice[i]!='\0';i++){
		if(dice[i]==6){
			// •ÏŠ·
			vector<short> count;
			Quinary q;
			
			_dice = dice[i-1];
//			count.push_back(dice[i]-1);
			while(dice[++i]!=6){
				count.push_back(dice[i]-1);
			}
			q.initq(count);
			for(int j=0;j<q.getDec()-1;j++){
				dices.push_back(_dice);
			}
		}else{
			// ‚»‚Ì‚Ü‚Ü
			dices.push_back(dice[i]);
		}
	}
	return dices;
}

void DiceCodeDecode::output(){
	std::ofstream ofs;
	ofs.open("CodeDecode.txt");
	for(int i=0;i<codes.size();i++){
		ofs<<codes[i]<<" "<<std::flush;
	}
	ofs.close();
}

void DiceCodeDecode::outputRunlength(){
	vector<int> dices = runlength();

	// -- test --
	std::ofstream ofs;
	ofs.open("DiceTest.txt");
	for(int i=0;i<dices.size();i++){
		ofs << dices[i] << " " << std::flush;
	}
	ofs.close();

	slvDice(dices);
	output();
}

}