#include "PaiDivide.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/optional.hpp>

using namespace boost::property_tree;

namespace pro{

PaiDivide::PaiDivide(void)
{
}


PaiDivide::~PaiDivide(void)
{
}

bool PaiDivide::getIniSetting(){
	ptree pt;
	try{
		read_ini("./Pai.ini",pt);
	}catch(ini_parser_error e){
		std::cout << e.what() << std::endl;
		return false;
	}
	if(boost::optional<string> path = pt.get_optional<string>("Divide.path"))
		this->base_path = Dir(path.get(),false);
	if(boost::optional<string> name = pt.get_optional<string>("Divide.name"))
		this->name = name.get();
	if(boost::optional<boost::uintmax_t> digits = pt.get_optional<boost::uintmax_t>("Divide.digits"))
		this->digits = digits.get();
	if(boost::optional<int> one_line_num = pt.get_optional<int>("Divide.oneLineNum"))
		this->one_line_num = one_line_num.get();
	if(boost::optional<int> line_num = pt.get_optional<int>("Divide.LineNum"))
		this->line_num = line_num.get();
	if(boost::optional<int> file_num = pt.get_optional<int>("Divide.FileNum"))
		this->file_num = file_num.get();

	fileSizeCalc(this->digits);

	return true;
}

void PaiDivide::fileSizeCalc(boost::uintmax_t digits){
	this->digits = digits;
	last_digits = digits%one_line_num==0?one_line_num:digits%one_line_num;

	all_line_num = last_digits==one_line_num ? 
		static_cast<long>(digits/one_line_num) : 
		static_cast<long>(digits/one_line_num+1);
	last_line_num = all_line_num%line_num==0?line_num:all_line_num%line_num;

	all_file_num = last_line_num==line_num ? 
		static_cast<long>(digits/(one_line_num*line_num)) : 
		static_cast<long>(digits/(one_line_num*line_num)+1);
		last_file_num = all_file_num%file_num==0?file_num:all_file_num%file_num;

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

}