#include "StringCalc.h"

namespace pro{

StringCalc::StringCalc(void)
{
}

StringCalc::~StringCalc(void)
{
}

void StringCalc::randomInit(){
	srand(time(NULL));
}

void StringCalc::randomStringOutput(int length,string filename){

	// 文字列生成
	char *c_str = new char[length+1];
	for(int i=0;i<length;i++){
		c_str[i] = rand()%RANDSTRNUM;
		if(c_str[i]<91-33)
			c_str[i]+=33;
		else
			c_str[i]+=37;
		std::cout << (int)c_str[i] << " " << std::flush;
	}
	c_str[length] = '\0';

	// 文字列掃き出し
	std::ofstream ofs;
	ofs.open(filename);
	ofs << c_str;
	ofs.close();

	delete[] c_str;
}


int StringCalc::fileStringMatching(string ansfile,string file,bool disp){

	// マッチング処理
	int count=0;
	char *ans_str,*str;
	std::ifstream ans_ifs,ifs;
	
	ans_str = new char[MAXSTRLENGTH+1];
	str = new char[MAXSTRLENGTH+1];

	ans_ifs.open(ansfile);
	ifs.open(file);

	ans_ifs.getline(ans_str,MAXSTRLENGTH);
	ifs.getline(str,MAXSTRLENGTH);

	while(ans_str[count]==str[count]){
		if(ans_str[count]=='\0') break;
		count++;
	}

	// 表示処理
	if(disp){
		std::cout<<"正解文字列("<< Dir::getFileName(ansfile) <<")"<<std::endl;
		std::cout<<ans_str<<std::endl;
		std::cout<<std::endl;

		std::cout<<"出力文字列("<< Dir::getFileName(file) <<")"<<std::endl;
		std::cout<<str<<std::endl;
		std::cout<<std::endl;

		std::cout<<"一致文字数 > "<<count<<std::endl;
		for(int i=0;i<count;i++){
			std::cout<<ans_str[i]<<std::flush;
		}
		std::cout<<std::endl;
	}

	ans_ifs.close();
	ifs.close();

	return count;

}


}