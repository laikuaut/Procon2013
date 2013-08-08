#include "PaiMatch.h"

#include<Windows.h>
#include<sstream>
#include<opencv2/highgui/highgui.hpp>
#include<cstdio>

namespace pro{

PaiMatch::PaiMatch(int digits, CharArrayNumeric::NumKind kind){
	num_str.init(digits,kind);

	load();

	this->digits = num_str.getLength();
	
}

PaiMatch::~PaiMatch(void){
	close();
}

void PaiMatch::open(){
	path = Dir("./Resource/PAI_MATCH/");
	path.create();

	std::stringstream ss;
	ss << digits << ".txt";
	std::stringstream ss_count;
	ss_count << digits << "_count.txt";
	if(load_flag){
		fs.open(path.pwd(ss.str()),std::ios::app);
		fs.seekg(std::ios_base::end);
		count_fs.open(path.pwd(ss_count.str()),std::ios::app);
		count_fs.seekg(std::ios_base::end);
	}
	else{
		fs.open(path.pwd(ss.str()),std::ios::out);
		count_fs.open(path.pwd(ss_count.str()),std::ios::out);
	}
}

void PaiMatch::close(){
	fs.close();
	count_fs.close();
}

void PaiMatch::init(){
	//ipd.getIniSetting();
	this->line_length=2;
	this->length = ipd.getOneLineNum()*2;
	while(this->digits*2 > this->length){
		this->length *= 2;
		this->line_length *= 2;
	}

	c_str.push_back(ipd.getLine());
	for(int i=1;i<this->line_length;i++){
		c_str.push_back(ipd.nextLine());
	}

	//fs<<num_str<<std::endl;

}

bool PaiMatch::next(){
	
	if(count>0)
		count_fs << num_str << " " << count << " " << pos << std::endl;

	count = 0;

	ipd.getLine(1,1,1);

	init();

	return num_str.add();
}

void PaiMatch::setStr(){
	c_str.pop_flont(ipd.getOneLineNum());
	c_str.push_back(ipd.nextLine());
	if(ipd.getLine().getLength() == 0)
		line_length--;
	//std::cout << c_str;
	//std::cout << std::endl;
}

bool PaiMatch::match(){
	try{
		return num_str==c_str(char_num-1,char_num-1+digits);
	}catch(const Exception&){
		//e.showError();
		return false;
	}
}

void PaiMatch::keyEvent(){
	if(GetKeyState(0x51)<0){
		save();
		close();
		exit(EXIT_SUCCESS);
	}
	if(GetKeyState(0x53)<0){
		save();
	}
	if(GetKeyState(0x4E)<0){
		nowDisplay();
	}
}

void PaiMatch::matchOneLine(){
//	int num;
	for(int i=char_num-1;i<ipd.getOneLineNum();i++){
		if(match()){
			output();
		}
		keyEvent();
		char_num++;
	}
	setStr();
	char_num=1;
}

void PaiMatch::output(){
	if(count==0) fs<<num_str<<std::endl;
	fs<<ipd.getNowDir()<<" ";
	fs<<ipd.getNowFile()<<" ";
	fs<<ipd.getNowLine()-line_length+1<<" ";
	fs<<char_num<<" ";
	fs<<std::endl;
	count++;
}

int PaiMatch::getDigits() const{
	return digits;
}

void PaiMatch::matching(){
	open();
	init();
	do{
		if(count==0) pos = fs.tellg();
		std::cout << "\r" << num_str << "\t\t\t\t\t\t" << std::flush;
		while(c_str.getLength()>0){
			matchOneLine();
		}
	}while(next());
	last_save();
	close();
}

void PaiMatch::save(){
	std::ofstream ofs;
	ofs.open("PaiMatch.dat");
	ofs << num_str << std::endl;
	ofs<<ipd.getNowDir()<<" ";
	ofs<<ipd.getNowFile()<<" ";
	ofs<<ipd.getNowLine()-line_length+1<<" ";
	ofs<<char_num<<" ";
	ofs<<count<<" ";
	ofs<<pos;
	ofs<<std::endl;
	ofs.close();
}

void PaiMatch::last_save(){
	std::ofstream ofs;
	ofs.open("PaiMatch.dat");
	digits++;
	num_str.setLength(digits);
	ofs << num_str << std::endl;
	ofs<<1<<" ";
	ofs<<1<<" ";
	ofs<<1<<" ";
	ofs<<1<<" ";
	ofs<<0<<" ";
	ofs<<0;
	ofs<<std::endl;
	ofs.close();
}

void PaiMatch::load(){
	std::ifstream ifs;
	ifs.open("PaiMatch.dat");
	if(ifs.fail()){
		char_num=1;
		count=0;
		ipd.getLine(1,1,1);
		load_flag = false;
	}else{
		string str;
		int pos;
		ifs >> str;
		num_str.setNum(str.c_str());
		int line_num,file_num,dir_num;
		ifs >> dir_num;
		ifs >> file_num;
		ifs >> line_num;
		ifs >> char_num;
		ifs >> count;
		ifs >> pos;
		this->pos = pos;
		ipd.getLine(dir_num,file_num,line_num);

		ifs.close();
		load_flag = true;
	}
}

void PaiMatch::nowDisplay(){
	std::cout<< "\r" << num_str << " " << std::flush;
	std::cout<<ipd.getNowDir()<<" "<<std::flush;
	std::cout<<ipd.getNowFile()<<" "<<std::flush;
	std::cout<<ipd.getNowLine()-line_length+1<<" "<<std::flush;
	std::cout<<char_num<<" "<<std::flush;
	std::cout<<count<<" "<<std::flush;
	//std::cout<<fs.tellg()<<" "<<std::flush;
	//printf_s("¥033[2J");
}

}
