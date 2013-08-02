#pragma once

#include "PaiDivide.h"

namespace pro{

class PRO_EXPORTS OutPaiDivide : PaiDivide
{
private:
	
	std::ifstream input_file;
	string input_name;
	Dir input_path;

	bool dot_flag;
	
	// �������֐�
	void init(boost::filesystem::path i_full_path);
	void init(boost::filesystem::path i_path,string i_name);

	/*******************************
	 *  divide()�̕⏕���\�b�h
	 */

	void createDir(int dir_num);
	void createFile(int dir_num,int file_num,int file_max_num);
	void createLine(int one_line_num);
	void createFirstLine(int one_line_num);
	void createFirstDir();
	void createLastDir();

	// �t�@�C���T�C�Y���猅��
	void setDigits();
	// �����_�̂���Ȃ�
	void setDotFlag();
	
public:
	OutPaiDivide(void);
	OutPaiDivide(boost::filesystem::path i_full_path);
	OutPaiDivide(boost::filesystem::path i_path,string i_name);
	~OutPaiDivide(void);

	// �f�t�H���g�ݒ��PaiDivide.ini���쐬
	void createIniFileDefault();
	// �C�Ӑݒ��PaiDivide.ini���쐬
	void createIniFile(string path
					,string name
					,boost::uintmax_t digits
					,int file_num
					,int line_num
					,int one_line_num);

	// �������s���\�b�h
	void divide();
};

}