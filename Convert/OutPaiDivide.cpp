#include "OutPaiDivide.h"

#include<sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/optional.hpp>

using namespace boost::property_tree;

namespace pro{

OutPaiDivide::OutPaiDivide(void)
{
	init("./Resource/PAI.txt");
}

OutPaiDivide::OutPaiDivide(boost::filesystem::path i_full_path){
	init(i_full_path);
}

OutPaiDivide::OutPaiDivide(boost::filesystem::path i_path,string i_name){
	init(i_path,i_name);
}

OutPaiDivide::~OutPaiDivide(void)
{

}

void OutPaiDivide::init(boost::filesystem::path i_full_path){
	init(i_full_path.parent_path(),i_full_path.filename().string());
}

void OutPaiDivide::init(boost::filesystem::path i_path,string i_name){
	if(!Dir(i_path).isExist(i_name))
		throw FileException(FileException::NOT_EXIST,Dir(i_path).pwd(i_name),"OutPaiDivide.cpp","OutPaiDivide::init(boost::filesystem::path,string)",__LINE__);
	input_path = Dir(i_path);
	input_name = i_name;
	setDotFlag();
}

void OutPaiDivide::setDigits(){
	boost::filesystem::path file(input_path.pwd(input_name));

	if(dot_flag)
		digits = boost::filesystem::file_size(file)-1;
	else
		digits = boost::filesystem::file_size(file);
}

void OutPaiDivide::setDotFlag(){
	input_file.open(this->input_path.pwd(input_name),std::ios::in);
	if(input_file.fail()) {
		throw FileException(FileException::OPEN,input_path.pwd(input_name),"Pai.cpp","OutPaiDivide::fileSizeCalc()",__LINE__);
	}

	char *buf = new char[3];
	input_file.read(buf,2);
	dot_flag = (buf[1]=='.');

	input_file.close();
}

void OutPaiDivide::createIniFileDefault(){

	setDigits();

	createIniFile("./Resource/PAI","pai",digits,1000,1000,1000);

}

void OutPaiDivide::createIniFile(
					 string path
					,string name
					,boost::uintmax_t digits
					,int file_num
					,int line_num
					,int one_line_num){
	ptree pt;
	pt.put("Divide.path",path);
	pt.put("Divide.name",name);
	pt.put("Divide.digits",digits);
	pt.put("Divide.oneLineNum",one_line_num);
	pt.put("Divide.LineNum",line_num);
	pt.put("Divide.FileNum",file_num);

	write_ini("./Pai.ini",pt);

	getIniSetting();
}

void OutPaiDivide::divide(){

	if(!getIniSetting()) createIniFileDefault();

	base_path.create(Dir::CREATE_DIRS | Dir::OVER_WRITE);

	input_file.open(this->input_path.pwd(input_name),std::ios::in);
	if(input_file.fail()) {
		throw FileException(FileException::OPEN,input_path.pwd(input_name),"Pai.cpp","OutPaiDivide::divide()",__LINE__);
	}

	createFirstDir();
	if(!input_file.is_open()) return;

	// 2つ目以降のディレクトリ処理
	for(int i=2;i<dir_num;i++){
		
		// directory作成
		createDir(i);

		for(int j=1;j<=file_num;j++){

			// file作成
			createFile(i,j,file_num);
			// 書き込み
			for(int k=0;k<line_num;k++){
				createLine(one_line_num);
			}
			fs.close();
		}
		std::cout << std::endl;

	}

	createLastDir();
	
	input_file.close();

}

void OutPaiDivide::createFirstDir(){
	// 最初のdirectory作成
	createDir(1);
	// file作成
	createFile(1,1,file_num);
	// 最初のライン作成
	if(dot_flag)
		createFirstLine(one_line_num+1);
	else
		createFirstLine(one_line_num);

	if(dir_num>1){
		// 書き込み
		for(int k=1;k<line_num;k++){
			createLine(one_line_num);
		}
		fs.close();

		for(int j=2;j<=file_num;j++){

			// file作成
			createFile(1,j,file_num);
			// 書き込み
			for(int k=0;k<line_num;k++){
				createLine(one_line_num);
			}
			fs.close();
		}
	}else if(dir_num==1){
		// 書き込み
		for(int k=1;k<line_num;k++){
			createLine(one_line_num);
		}
		fs.close();

		for(int j=2;j<last_file_num;j++){

			// file作成
			createFile(dir_num,j,last_file_num);
			for(int k=0;k<line_num;k++){
				createLine(one_line_num);
			}
			fs.close();
		}


		// 最後のfile作成
		createFile(dir_num,last_file_num,last_file_num);

		for(int k=1;k<last_line_num;k++){
			createLine(one_line_num);
		}

		// 最後のライン作成
		createLine(last_digits);
		fs.close();
		input_file.close();
	}
	std::cout << std::endl;
}

void OutPaiDivide::createLastDir(){

	// 最後のdirectory作成
	createDir(dir_num);

	for(int j=1;j<last_file_num;j++){

		// file作成
		createFile(dir_num,j,last_file_num);
		for(int k=0;k<line_num;k++){
			createLine(one_line_num);
		}
		fs.close();
	}


	// 最後のfile作成
	createFile(dir_num,last_file_num,last_file_num);

	for(int k=1;k<last_line_num;k++){
		createLine(one_line_num);
	}

	// 最後のライン作成
	createLine(last_digits);
	fs.close();
	std::cout << std::endl;
}

void OutPaiDivide::createDir(int dir_num){
	std::stringstream d_ss;
	d_ss << dir_num;
	path = Dir(base_path.pwd(d_ss.str()));
	path.create(Dir::CREATE_DIRS | Dir::OVER_WRITE_REMOVE_ALL);
}

void OutPaiDivide::createFile(int dir_num,int file_num,int file_max_num){
	std::stringstream f_ss;
	f_ss << name << "_" << file_num << ".txt";
	fs.open(path.pwd(f_ss.str()),std::ios::out);
	std::cout << "\rdir(" << dir_num << "/" << this->dir_num << ")___file(" << file_num << "/" << file_max_num << ")    ";
}

void OutPaiDivide::createLine(int one_line_num){
	char *buf = new char[one_line_num];
	input_file.read(buf,one_line_num);
	fs.write(buf,one_line_num);
	fs << std::endl;
}

void OutPaiDivide::createFirstLine(int one_line_num){
	char *buf = new char[one_line_num];
	input_file.read(buf,one_line_num);
	if(this->one_line_num == one_line_num-1){
		if(buf[1] == '.'){
			for(int i=2;i<one_line_num;i++){
				buf[i-1] = buf[i];
			}
			one_line_num--;
		}
	}
	fs.write(buf,one_line_num);
	fs << std::endl;
}

}