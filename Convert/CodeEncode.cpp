#include "CodeEncode.h"

namespace pro{

CodeEncode::CodeEncode(void)
{
}


CodeEncode::~CodeEncode(void)
{
}

void CodeEncode::init(string name){
	fileRead(name);
	setCode();
}

void CodeEncode::fileRead(string name){
	std::ifstream ifs;
	ifs.open(name);
	char *c_str = new char[4001];
	ifs.getline(c_str,4000);
	c_str[4000] = '\0';
	for(int i=0;c_str[i]!='\0';i++)
		str.push_back(c_str[i]);
	ifs.close();
}

void CodeEncode::setCode(){
	for(int i=0;i<str.size();i++){
		codes.push_back(codeTable(str[i]));
	}
}

int CodeEncode::codeTable(char c){
	switch(c){
		case '!':return 116;break;//case '!':return 1;break;
		case '\"':return 118;break;//case '\"':return 2;break;
		case '#':return 104;break;//case '#':return 3;break;
		case '$':return 103;break;//case '$':return 4;break;
		case '%':return 111;break;//case '%':return 5;break;
		case '&':return 113;break;//case '&':return 6;break;
		case '\'':return 99;break;//case '\'':return 7;break;
		case '(':return 8;break;
		case ')':return 9;break;
		case '*':return 10;break;
		case '+':return 11;break;
		case ',':return 12;break;
		case '-':return 13;break;
		case '.':return 14;break;
		case '/':return 15;break;
		case '0':return 117;break;//case '0':return 16;break;
		case '1':return 17;break;
		case '2':return 18;break;
		case '3':return 19;break;
		case '4':return 20;break;
		case '5':return 21;break;
		case '6':return 22;break;
		case '7':return 23;break;
		case '8':return 24;break;
		case '9':return 25;break;
		case ':':return 26;break;
		case ';':return 27;break;
		case '<':return 28;break;
		case '=':return 29;break;
		case '>':return 30;break;
		case '?':return 31;break;
		case '@':return 32;break;
		case 'A':return 123;break;//case 'A':return 33;break;
		case 'B':return 34;break;
		case 'C':return 35;break;
		case 'D':return 36;break;
		case 'E':return 37;break;
		case 'F':return 38;break;
		case 'G':return 39;break;
		case 'H':return 40;break;
		case 'I':return 41;break;
		case 'J':return 42;break;
		case 'K':return 43;break;
		case 'L':return 44;break;
		case 'M':return 45;break;
		case 'N':return 46;break;
		case 'O':return 47;break;
		case 'P':return 119;break;//case 'P':return 48;break;
		case 'Q':return 49;break;
		case 'R':return 50;break;
		case 'S':return 51;break;
		case 'T':return 52;break;
		case 'U':return 53;break;
		case 'V':return 54;break;
		case 'W':return 55;break;
		case 'X':return 56;break;
		case 'Y':return 57;break;
		case 'Z':return 58;break;
		case '_':return 59;break;
		case '`':return 60;break;
		case 'a':return 61;break;
		case 'b':return 62;break;
		case 'c':return 63;break;
		case 'd':return 120;break;//case 'd':return 64;break;
		case 'e':return 125;break;//case 'e':return 65;break;
		case 'f':return 122;break;//case 'f':return 66;break;
		case 'g':return 124;break;//case 'g':return 67;break;
		case 'h':return 68;break;
		case 'i':return 69;break;
		case 'j':return 70;break;
		case 'k':return 71;break;
		case 'l':return 72;break;
		case 'm':return 73;break;
		case 'n':return 74;break;
		case 'o':return 75;break;
		case 'p':return 76;break;
		case 'q':return 77;break;
		case 'r':return 78;break;
		case 's':return 79;break;
		case 't':return 121;break;//case 't':return 80;break;
		case 'u':return 81;break;
		case 'v':return 82;break;
		case 'w':return 83;break;
		case 'x':return 84;break;
		case 'y':return 85;break;
		case 'z':return 86;break;
		default:return '\0';
	}
}

void CodeEncode::output(){
	std::ofstream ofs;
	ofs.open("CodeEncode.txt");
	for(int i=0;i<codes.size();i++){
		ofs << codes[i] << " " << std::flush;
	}
	ofs.close();
}

}