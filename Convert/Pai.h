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
	boost::uintmax_t digits;
	long all_line_num;
	long all_file_num;
	bool setting_flag;
	
	/*******************************
	 *   ê›íËÉÅÉìÉo
	 */

	Dir in_path;
	Dir out_base_path;
	
	string in_name;
	string out_name;

	int one_line_num;
	int line_num;
	int file_num;

	void init(boost::filesystem::path path,string name);

	// divide()ÇÃï‚èï
	void createDir(int dir_num);
	void createFile(int dir_num,int file_num,int file_max_num);
	void createLine(int one_line_num);

	void createIniFile();

public:
	
	PaiFileDivide(void);
	PaiFileDivide(string name);
	PaiFileDivide(boost::filesystem::path path,string name);
	~PaiFileDivide(void);

	long getDirNum() const;
	int getOneLineNum() const;
	int getLineNum() const;
	int getFileNum() const;
	const string getOutFileName() const;
	const string getOutPath() const;

	void fileSizeCalc();
	void fileSizeCalc(boost::uintmax_t digits);
	void divide();

	void getIniSetting();

	//void setNums(int file_num,int line_num,int one_line_num);

	const char* getLine(long dir_num,int file_num,int line_num);



};

class PRO_EXPORTS PaiMatch
{
public:
	PaiMatch(void);
	~PaiMatch(void);
};

}
