#include "OutPaiMatch.h"

#include<sstream>
#include<Windows.h>

namespace pro{

OutPaiMatch::OutPaiMatch(int digits, CharArrayNumeric::NumKind kind) : PaiMatch(digits,kind)
{
	load();
	this->digits = num_str.getLength();
}

OutPaiMatch::~OutPaiMatch(void)
{
}

void OutPaiMatch::open(){
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

void OutPaiMatch::init(){
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

}

bool OutPaiMatch::next(){
	
	if(count>0)
		count_fs << num_str << " " << count << " " << pos << std::endl;

	count = 0;

	ipd.getLine(1,1,1);

	init();

	return num_str.add();
}

void OutPaiMatch::setStr(){
	c_str.pop_flont(ipd.getOneLineNum());
	c_str.push_back(ipd.nextLine());
	if(ipd.getLine().getLength() == 0)
		line_length--;
}

bool OutPaiMatch::match(){
	try{
		return num_str==c_str(char_num-1,char_num-1+digits);
	}catch(const Exception&){
		return false;
	}
}

void OutPaiMatch::keyEvent(){
	// qキー
	if(GetKeyState(0x51)<0){
		save();
		close();
		exit(EXIT_SUCCESS);
	}
	// sキー
	if(GetKeyState(0x53)<0){
		save();
	}
	// nキー
	if(GetKeyState(0x4E)<0){
		nowDisplay();
	}
}

void OutPaiMatch::matchOneLine(){
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

void OutPaiMatch::output(){
	if(count==0) fs<<num_str<<std::endl;
	fs<<ipd.getNowDir()<<" ";
	fs<<ipd.getNowFile()<<" ";
	fs<<ipd.getNowLine()-line_length+1<<" ";
	fs<<char_num<<" ";
	fs<<std::endl;
	count++;
}

void OutPaiMatch::matching(){
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

void OutPaiMatch::save(){
	std::ofstream ofs;
	ofs.open("OutPaiMatch.dat");
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

void OutPaiMatch::last_save(){
	std::ofstream ofs;
	ofs.open("OutPaiMatch.dat");
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

void OutPaiMatch::load(){
	std::ifstream ifs;
	ifs.open("OutPaiMatch.dat");
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

void OutPaiMatch::nowDisplay(){
	std::cout<< "\r" << num_str << " " << std::flush;
	std::cout<<ipd.getNowDir()<<" "<<std::flush;
	std::cout<<ipd.getNowFile()<<" "<<std::flush;
	std::cout<<ipd.getNowLine()-line_length+1<<" "<<std::flush;
	std::cout<<char_num<<" "<<std::flush;
	std::cout<<count<<" "<<std::flush;
}


}
