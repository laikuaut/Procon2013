#include "CodeDecode.h"

namespace pro{

CodeDecode::CodeDecode(void)
{
}

CodeDecode::~CodeDecode(void)
{
}

void CodeDecode::init(string name){
	fileRead(name);
	setStr();
}

void CodeDecode::initRunlength(string name){
	fileRead(name);
}

void CodeDecode::fileRead(string name){
	std::ifstream ifs;
	ifs.open(name);
	codes.clear();
	int code;
	while(1){
		ifs>>code;
		if(ifs.eof()) break;
		codes.push_back(code);
	}
	ifs.close();
}

void CodeDecode::setStr(){
	for(int i=0;i<codes.size();i++){
		str.push_back(strTable(codes[i]));
	}
}

void CodeDecode::setStr(vector<int> codes){
	for(int i=0;i<codes.size();i++){
		str.push_back(strTable(codes[i]));
	}
}

char CodeDecode::strTable(int code){
	switch(code){
		case 116:return '!';break;//case 1:return '!';break;
		case 118:return '\"';break;//case 2:return '\"';break;
		case 104:return '#';break;//case 3:return '#';break;
		case 103:return '$';break;//case 4:return '$';break;
		case 111:return '%';break;//case 5:return '%';break;
		case 113:return '&';break;//case 6:return '&';break;
		case 99:return '\'';break;//case 7:return '\'';break;
		case 8:return '(';break;
		case 9:return ')';break;
		case 10:return '*';break;
		case 11:return '+';break;
		case 12:return ',';break;
		case 13:return '-';break;
		case 14:return '.';break;
		case 15:return '/';break;
		case 117:return '0';break;//case 16:return '0';break;
		case 17:return '1';break;
		case 18:return '2';break;
		case 19:return '3';break;
		case 20:return '4';break;
		case 21:return '5';break;
		case 22:return '6';break;
		case 23:return '7';break;
		case 24:return '8';break;
		case 25:return '9';break;
		case 26:return ':';break;
		case 27:return ';';break;
		case 28:return '<';break;
		case 29:return '=';break;
		case 30:return '>';break;
		case 31:return '?';break;
		case 110:return '@';break;
		case 123:return 'A';break;//case 33:return 'A';break;
		case 34:return 'B';break;
		case 35:return 'C';break;
		case 36:return 'D';break;
		case 37:return 'E';break;
		case 38:return 'F';break;
		case 39:return 'G';break;
		case 40:return 'H';break;
		case 41:return 'I';break;
		case 42:return 'J';break;
		case 43:return 'K';break;
		case 44:return 'L';break;
		case 45:return 'M';break;
		case 46:return 'N';break;
		case 47:return 'O';break;
		case 119:return 'P';break;//case 48:return 'P';break;
		case 49:return 'Q';break;
		case 50:return 'R';break;
		case 51:return 'S';break;
		case 52:return 'T';break;
		case 53:return 'U';break;
		case 54:return 'V';break;
		case 55:return 'W';break;
		case 56:return 'X';break;
		case 57:return 'Y';break;
		case 58:return 'Z';break;
		case 59:return '_';break;
		case 60:return '`';break;
		case 61:return 'a';break;
		case 62:return 'b';break;
		case 63:return 'c';break;
		case 120:return 'd';break;//case 64:return 'd';break;
		case 125:return 'e';break;//case 65:return 'e';break;
		case 122:return 'f';break;//case 66:return 'f';break;
		case 124:return 'g';break;//case 67:return 'g';break;
		case 68:return 'h';break;
		case 69:return 'i';break;
		case 70:return 'j';break;
		case 71:return 'k';break;
		case 72:return 'l';break;
		case 73:return 'm';break;
		case 74:return 'n';break;
		case 75:return 'o';break;
		case 76:return 'p';break;
		case 77:return 'q';break;
		case 78:return 'r';break;
		case 79:return 's';break;
		case 121:return 't';break;//case 80:return 't';break;
		case 81:return 'u';break;
		case 82:return 'v';break;
		case 83:return 'w';break;
		case 84:return 'x';break;
		case 85:return 'y';break;
		case 86:return 'z';break;
		default:return '\0';
	}
}

vector<int> CodeDecode::runlength(){
	int count;
	int code;
	vector<int> _codes;
	bool flag;
	for(int i=0;i<codes.size();i++){
		if(codes[i]==0){
			flag = true;
			// •ÏŠ·
		//	vector<short> count;
			
			code = codes[i-1];
//			count.push_back(dice[i]-1);
			//while(codes[++i]!=0){
			//	if(i>=codes.size()) break;
			if(i+1<codes.size()){;
			count = codes[++i];
			//}
			//if(codes[i]=='\0') break;
			//q.initq(count);
			for(int j=0;j<count-1;j++){
				_codes.push_back(code);
			}
			}
		}else{
			flag = false;
			// ‚»‚Ì‚Ü‚Ü
			_codes.push_back(codes[i]);
		}
	}
	if(flag){
		for(int j=0;j<count-1;j++){
			_codes.push_back(code);
		}
	}
	return _codes;
}

void CodeDecode::output(){
	std::ofstream ofs;
	ofs.open("str.txt");
	for(int i=0;i<str.size();i++){
		ofs << str[i] << std::flush;
	}
	ofs.close();
	str.clear();
}

void CodeDecode::outputRunlength(){
	vector<int> _codes = runlength();
	setStr(_codes);
	output();
}


}