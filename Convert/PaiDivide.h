#pragma once

#include"Procon2013/Core/Core.h"
#include<iostream>

namespace pro{

class PRO_EXPORTS PaiDivide
{
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

public:
	PaiDivide(void);
	~PaiDivide(void);
	
	// PaiDivide.ini����f�[�^�擾
	bool getIniSetting();
	
	// ��������f�[�^�v�Z
	void fileSizeCalc(boost::uintmax_t digits);
};

}