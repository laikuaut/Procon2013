#include "Pai.h"

#include<sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/optional.hpp>

using namespace boost::property_tree;

namespace pro{
	
PaiFileDivide::PaiFileDivide(){
}

PaiFileDivide::~PaiFileDivide(){
}

void PaiFileDivide::getIniSetting(){
	ptree pt;
	try{
		read_ini("./PaiDivide.ini",pt);
	}catch(ini_parser_error e){
		std::cout << e.what() << std::endl;
		return;
	}
	if(boost::optional<string> path = pt.get_optional<string>("Pai.path"))
		this->base_path = Dir(path.get());
	if(boost::optional<string> name = pt.get_optional<string>("Pai.name"))
		this->name = name.get();
	if(boost::optional<boost::uintmax_t> digits = pt.get_optional<boost::uintmax_t>("Pai.digits"))
		this->digits = digits.get();
	if(boost::optional<int> one_line_num = pt.get_optional<int>("Pai.oneLineNum"))
		this->one_line_num = one_line_num.get();
	if(boost::optional<int> line_num = pt.get_optional<int>("Pai.LineNum"))
		this->line_num = line_num.get();
	if(boost::optional<int> file_num = pt.get_optional<int>("Pai.FileNum"))
		this->file_num = file_num.get();

	fileSizeCalc(this->digits);
}

void PaiFileDivide::fileSizeCalc(boost::uintmax_t digits){
	this->digits = digits;
	last_digits = digits%one_line_num;

	all_line_num = last_digits==0 ? 
		static_cast<long>(digits/one_line_num) : 
		static_cast<long>(digits/one_line_num+1);
	last_line_num = all_line_num%line_num;

	all_file_num = last_line_num==0 ? 
		static_cast<long>(digits/(one_line_num*line_num)) : 
		static_cast<long>(digits/(one_line_num*line_num)+1);
	last_file_num = all_file_num%file_num;

	dir_num = last_file_num==0 ? all_file_num/file_num : all_file_num/file_num+1;

	//std::cout <<"file_size:"<<file_size<< std::endl;
	std::cout <<"digits:"<<digits<< std::endl;
	std::cout <<"all_line_num:"<<all_line_num<< std::endl;
	std::cout <<"all_file_num:"<<all_file_num<< std::endl;
	std::cout <<"dir_num:"<<dir_num<< std::endl;
	std::cout <<"file_num:"<<file_num<< std::endl;
	std::cout <<"line_num:"<<line_num<< std::endl;
	std::cout <<"one_line_num:"<<one_line_num<< std::endl;
	std::cout <<"last_digits:"<<last_digits<< std::endl;
	std::cout <<"last_line_num:"<<last_line_num<< std::endl;
	std::cout <<"last_file_num:"<<last_file_num<< std::endl;
	std::cout << std::endl;
}

//PaiFileDivide::PaiFileDivide(){
//	init("./Resource","Pi - Hex - Chudnovsky.txt");
//}
//
//PaiFileDivide::PaiFileDivide(string name){
//	init("./Resource",name);
//}
//
//PaiFileDivide::PaiFileDivide(boost::filesystem::path path,string name){
//	init(path,name);
//}
//
//PaiFileDivide::~PaiFileDivide(){
//}
//
//void PaiFileDivide::init(boost::filesystem::path path,string name){
//	this->in_path = Dir(path);
//	out_base_path = Dir("./Resource/PAI");
//	in_name = name;
//	out_name = "pai";
//	one_line_num = 1000;
//	line_num = 1000;
//	file_num = 1000;
//	setting_flag=false;
//}
//
//void PaiFileDivide::createIniFile(){
//	ptree pt;
//	pt.put("Pai.digits",digits);
//	pt.put("Pai.oneLineNum",one_line_num);
//	pt.put("Pai.LineNum",line_num);
//	pt.put("Pai.FileNum",file_num);
//	//pt.put("Pai.outName",out_name);
//
//	write_ini(out_base_path.pwd("PaiDivide.ini"),pt);
//}
//
//void PaiFileDivide::getIniSetting(){
//	ptree pt;
//	try{
//		read_ini(out_base_path.pwd("PaiDivide.ini"),pt);
//	}catch(ini_parser_error e){
//		std::cout << e.what() << std::endl;
//		return;
//	}
//
//	if(boost::optional<boost::uintmax_t> digits = pt.get_optional<boost::uintmax_t>("Pai.digits"))
//		this->digits = digits.get();
//	if(boost::optional<int> one_line_num = pt.get_optional<int>("Pai.oneLineNum"))
//		this->one_line_num = one_line_num.get();
//	if(boost::optional<int> line_num = pt.get_optional<int>("Pai.LineNum"))
//		this->line_num = line_num.get();
//	if(boost::optional<int> file_num = pt.get_optional<int>("Pai.FileNum"))
//		this->file_num = file_num.get();
//
//	fileSizeCalc(this->digits);
//}
//
//long PaiFileDivide::getDirNum() const{
//	return dir_num;
//}
//
//int PaiFileDivide::getOneLineNum() const{
//	return one_line_num;
//}
//
//int PaiFileDivide::getLineNum() const{
//	return line_num;
//}
//
//int PaiFileDivide::getFileNum() const{
//	return file_num;
//}
//
//const string PaiFileDivide::getOutFileName() const{
//	return out_name;
//}
//
//const string PaiFileDivide::getOutPath() const{
//	return out_path.pwd();
//}
//
//void PaiFileDivide::fileSizeCalc(){
//	boost::filesystem::path file(in_path.pwd(in_name));
//	//file_size = boost::filesystem::file_size(file);
//
//	in_file.open(this->in_path.pwd(in_name),std::ios::in);
//	if(in_file.fail()) {
//		throw FileException(FileException::OPEN,in_path.pwd(in_name),"Pai.cpp","PaiFileDivide::fileSizeCalc()");
//	}
//
//	char *buf = new char[3];
//	in_file.read(buf,3);
//
//	if(buf[1]=='.')
//		fileSizeCalc(boost::filesystem::file_size(file)-1);
//	else
//		fileSizeCalc(boost::filesystem::file_size(file));
//
//	in_file.close();
//
//}
//
//void PaiFileDivide::fileSizeCalc(boost::uintmax_t digits){
//	this->digits = digits;
//	last_digits = digits%one_line_num;
//
//	all_line_num = last_digits==0 ? 
//		static_cast<long>(digits/one_line_num) : 
//		static_cast<long>(digits/one_line_num+1);
//	last_line_num = all_line_num%line_num;
//
//	all_file_num = last_line_num==0 ? 
//		static_cast<long>(digits/(one_line_num*line_num)) : 
//		static_cast<long>(digits/(one_line_num*line_num)+1);
//	last_file_num = all_file_num%file_num;
//
//	dir_num = last_file_num==0 ? all_file_num/file_num : all_file_num/file_num+1;
//
//	//std::cout <<"file_size:"<<file_size<< std::endl;
//	std::cout <<"digits:"<<digits<< std::endl;
//	std::cout <<"all_line_num:"<<all_line_num<< std::endl;
//	std::cout <<"all_file_num:"<<all_file_num<< std::endl;
//	std::cout <<"dir_num:"<<dir_num<< std::endl;
//	std::cout <<"file_num:"<<file_num<< std::endl;
//	std::cout <<"line_num:"<<line_num<< std::endl;
//	std::cout <<"one_line_num:"<<one_line_num<< std::endl;
//	std::cout <<"last_digits:"<<last_digits<< std::endl;
//	std::cout <<"last_line_num:"<<last_line_num<< std::endl;
//	std::cout <<"last_file_num:"<<last_file_num<< std::endl;
//	std::cout << std::endl;
//
//	setting_flag = true;
//
//	createIniFile();
//}
//
//void PaiFileDivide::divide(){
//
//	out_base_path.create(Dir::CREATE_DIRS | Dir::OVER_WRITE_REMOVE_ALL);
//
//	if(!setting_flag)	fileSizeCalc();
//	else				createIniFile();
//
//	in_file.open(this->in_path.pwd(in_name),std::ios::in);
//	if(in_file.fail()) {
//		throw FileException(FileException::OPEN,in_path.pwd(in_name),"Pai.cpp","PaiFileDivide::divide()");
//	}
//
//	// 最初のdirectory作成
//	createDir(1);
//	// file作成
//	createFile(1,1,file_num);
//	// 最初のライン作成
//	createLine(one_line_num+1);
//
//	if(dir_num>1){
//		// 書き込み
//		for(int k=1;k<line_num;k++){
//			createLine(one_line_num);
//		}
//		out_file.close();
//
//		for(int j=2;j<=file_num;j++){
//
//			// file作成
//			createFile(1,j,file_num);
//			// 書き込み
//			for(int k=0;k<line_num;k++){
//				createLine(one_line_num);
//			}
//			out_file.close();
//		}
//	}else if(dir_num==1){
//		// 書き込み
//		for(int k=1;k<line_num;k++){
//			createLine(one_line_num);
//		}
//		out_file.close();
//
//		for(int j=1;j<last_file_num;j++){
//
//			// file作成
//			createFile(dir_num,j,last_file_num);
//			for(int k=0;k<line_num;k++){
//				createLine(one_line_num);
//			}
//			out_file.close();
//		}
//
//
//		// 最後のfile作成
//		createFile(dir_num,last_file_num,last_file_num);
//
//		for(int k=0;k<last_line_num;k++){
//			createLine(one_line_num);
//		}
//
//		// 最後のライン作成
//		createLine(last_digits);
//		out_file.close();
//	}
//
//	// 2つ目以降のディレクトリ処理
//	for(int i=2;i<dir_num;i++){
//		
//		// directory作成
//		createDir(i);
//
//		for(int j=1;j<=file_num;j++){
//
//			// file作成
//			createFile(i,j,file_num);
//			// 書き込み
//			for(int k=0;k<line_num;k++){
//				createLine(one_line_num);
//			}
//			out_file.close();
//		}
//
//	}
//
//	// 最後のdirectory作成
//	createDir(dir_num);
//
//	for(int j=1;j<last_file_num;j++){
//
//		// file作成
//		createFile(dir_num,j,last_file_num);
//		for(int k=0;k<line_num;k++){
//			createLine(one_line_num);
//		}
//		out_file.close();
//	}
//
//
//	// 最後のfile作成
//	createFile(dir_num,last_file_num,last_file_num);
//
//	for(int k=0;k<last_line_num;k++){
//		createLine(one_line_num);
//	}
//
//	// 最後のライン作成
//	createLine(last_digits);
//	out_file.close();
//	
//	
//	in_file.close();
//
//
//}
//
//void PaiFileDivide::createDir(int dir_num){
//	std::stringstream d_ss;
//	d_ss << dir_num;
//	out_path = Dir(out_base_path.pwd(d_ss.str()));
//	out_path.create(Dir::CREATE_DIRS | Dir::OVER_WRITE_REMOVE_ALL);
//}
//
//void PaiFileDivide::createFile(int dir_num,int file_num,int file_max_num){
//	std::stringstream f_ss;
//	f_ss << out_name << "_" << file_num << ".txt";
//	out_file.open(out_path.pwd(f_ss.str()),std::ios::out);
//	std::cout << "dir(" << dir_num << "/" << this->dir_num << ")___file(" << file_num << "/" << file_max_num << ")    \r";
//}
//
//void PaiFileDivide::createLine(int one_line_num){
//	char *buf = new char[one_line_num];
//	in_file.read(buf,one_line_num);
//	if(this->one_line_num == one_line_num-1){
//		if(buf[1] == '.'){
//			for(int i=2;i<one_line_num;i++){
//				buf[i-1] = buf[i];
//			}
//			one_line_num--;
//		}
//	}
//	out_file.write(buf,one_line_num);
//	out_file << std::endl;
//}
//
//const char* PaiFileDivide::getLine(long dir_num,int file_num,int line_num){
//	std::ifstream in_file;
//	
//	std::stringstream d_ss;
//	std::stringstream f_ss;
//	d_ss << dir_num;
//	f_ss << out_name << "_" << file_num << ".txt";
//
//	out_path = Dir(out_base_path.pwd(d_ss.str()));
//
//	in_file.open(out_path.pwd(f_ss.str()));
//	if(in_file.fail())
//		throw FileException(FileException::OPEN,in_path.pwd(in_name),"Pai.cpp","PaiFileDivide::getLine(long,int,int)");
//
//	char *c_str;
//	int one_line;
//
//	if( dir_num == this->dir_num &&
//		file_num == this->last_file_num &&
//		line_num == this->last_line_num){
//		one_line = last_digits+1;
//	}else{
//		one_line = one_line_num+1;
//	}
//
//	c_str = new char[one_line];
//
//	in_file.seekg((line_num-1)*(one_line+1),std::ios_base::beg);
//
//	in_file.getline(c_str,one_line);
//
//	in_file.close();
//
//	return c_str;
//}

}
