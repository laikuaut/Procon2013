#pragma once

#include"Procon2013/Core/Core.h"
#include<iostream>

namespace pro{

class PRO_EXPORTS PaiFileDivide
{
private:

	Dir out_path;
	std::ifstream in_file;
	std::ofstream out_file;

	long dir_num;
	int last_file_num;
	int last_line_num;
	int last_digits;
	//boost::uintmax_t file_size;
	boost::uintmax_t digits;
	long all_line_num;
	long all_file_num;
	bool setting_flag;
	
	/*******************************
	 *   �ݒ胁���o
	 */

	Dir in_path;
	Dir out_base_path;
	
	string in_name;
	string out_name;

	int one_line_num;
	int line_num;
	int file_num;

	void init(boost::filesystem::path path,string name);

	// divide()�̕⏕
	void createDir(int dir_num);
	void createFile(int dir_num,int file_num,int file_max_num);
	void createLine(int one_line_num);

	void createIniFile();

public:
	
	PaiFileDivide(void);
	PaiFileDivide(string name);
	PaiFileDivide(boost::filesystem::path path,string name);
	~PaiFileDivide(void);

	long getDirNum();
	int getOneLineNum();
	int getLineNum();
	int getFileNum();
	const string getOutFileName();
	const string getOutPath();
	


	void fileSizeCalc();
	void fileSizeCalc(boost::uintmax_t digits);
	void divide();

	void getIniSetting();

	void setNums(int dir_num,int file_num,int one_line_num);



};

class PRO_EXPORTS PaiMatch
{
public:
	PaiMatch(void);
	~PaiMatch(void);
};

}
