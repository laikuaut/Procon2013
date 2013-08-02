#pragma once

#include"Procon2013/Core/Core.h"
#include<iostream>

namespace pro{

	
/**
   �~�����t�@�C���̕����Ɠǂݍ��݃N���X
 */
class PRO_EXPORTS PaiFileDivide
{
private:

//	Dir out_path;			// �o�̓f�B���N�g��
//	std::ifstream in_file;	// �~�����̌��t�@�C���X�g���[��
//	std::ofstream out_file; // �A�E�g�v�b�g�X�g���[��
//
//	/*******************************
//	 *  �v�Z���狁�߂郁���o
//	 */
//
//	long dir_num;			// �쐬�f�B���N�g����
//	int last_file_num;		// ���X�g�f�B���N�g�����̃t�@�C����
//	int last_line_num;		// ���X�g�t�@�C�����̃��C����
//	int last_digits;		// ���X�g���C���̌���
//	boost::uintmax_t digits;// ����
//	long all_line_num;		// �S���C����
//	long all_file_num;		// �S�t�@�C����
//	bool setting_flag;		// �f�[�^�擾�ォ�̔���t���O
//	
//	/*******************************
//	 *   �ݒ胁���o
//	 */
//
//	Dir in_path;			// ���̓t�@�C���f�B���N�g��
//	Dir out_base_path;		// �o�̓x�[�X�f�B���N�g��
//	
//	string in_name;			// ���̓t�@�C����
//	string out_name;		// �o�̓t�@�C����
//
//	int one_line_num;		// 1���C���̌���
//	int line_num;			// 1�t�@�C���̃��C����
//	int file_num;			// 1�f�B���N�g���̃t�@�C����
//
//	// �������֐�
//	void init(boost::filesystem::path path,string name);
//
//	/*******************************
//	 *  divide()�̕⏕���\�b�h
//	 */
//
//	void createDir(int dir_num);
//	void createFile(int dir_num,int file_num,int file_max_num);
//	void createLine(int one_line_num);
//
//
//public:
//	
//	PaiFileDivide(void);
//	PaiFileDivide(string name);
//	PaiFileDivide(boost::filesystem::path path,string name);
//	~PaiFileDivide(void);
//
//	/*******************************
//	 *  �v���p�e�B�Q
//	 */
//
//	long getDirNum() const;
//	int getOneLineNum() const;
//	int getLineNum() const;
//	int getFileNum() const;
//	const string getOutFileName() const;
//	const string getOutPath() const;
//
//	// �t�@�C���T�C�Y����f�[�^�v�Z
//	void fileSizeCalc();
//	// ��������f�[�^�v�Z
//	void fileSizeCalc(boost::uintmax_t digits);
//
//	// �������s���\�b�h
//	void divide();
//
//	// PaiDivide.ini����f�[�^�擾
//	void getIniSetting();
//	// �f�[�^����PaiDivide.ini�̍쐬
//	void createIniFile();
//
//	//void setNums(int file_num,int line_num,int one_line_num);
//
//	// ���C���擾
//	const char* getLine(long dir_num,int file_num,int line_num);
//
protected:

	std::fstream fs;

	/*******************************
	 *   �ݒ胁���o
	 */

	Dir path;				// �A�N�Z�X�p�t�@�C���f�B���N�g��
	Dir base_path;			// �x�[�X�f�B���N�g��
		
	string name;			// �t�@�C����

	int one_line_num;		// 1���C���̌���
	int line_num;			// 1�t�@�C���̃��C����
	int file_num;			// 1�f�B���N�g���̃t�@�C����

	/*******************************
	 *  �v�Z���狁�߂郁���o
	 */

	long dir_num;			// �쐬�f�B���N�g����
	int last_file_num;		// ���X�g�f�B���N�g�����̃t�@�C����
	int last_line_num;		// ���X�g�t�@�C�����̃��C����
	int last_digits;		// ���X�g���C���̌���
	boost::uintmax_t digits;// ����
	long all_line_num;		// �S���C����
	long all_file_num;		// �S�t�@�C����
	//bool setting_flag;	// �f�[�^�擾�ォ�̔���t���O

	// �������֐�
	//void init();

public:
	
	PaiFileDivide(void);
	~PaiFileDivide(void);
	
	// PaiDivide.ini����f�[�^�擾
	void getIniSetting();
	
	// ��������f�[�^�v�Z
	void fileSizeCalc(boost::uintmax_t digits);

};

class PRO_EXPORTS PaiFileDivideOut : PaiFileDivide
{
private:
	
	std::ifstream input_file;
	string input_name;
	Dir input_path;

	bool setting_flag;		// �f�[�^�擾�ォ�̔���t���O
	
	// �������֐�
	void init(boost::filesystem::path path,string name);

	/*******************************
	 *  divide()�̕⏕���\�b�h
	 */

	void createDir(int dir_num);
	void createFile(int dir_num,int file_num,int file_max_num);
	void createLine(int one_line_num);

public:
	
	PaiFileDivideOut(void);
	~PaiFileDivideOut(void);

	// �t�@�C���T�C�Y����f�[�^�v�Z
	void fileSizeCalc();
	// �������s���\�b�h
	void divide();
	// �f�[�^����PaiDivide.ini�̍쐬
	void createIniFile();
	
};

class PRO_EXPORTS PaiFileDivideIn : PaiFileDivide
{

};

class PRO_EXPORTS PaiMatch
{
private:



public:
	PaiMatch(void);
	~PaiMatch(void);
};

}
