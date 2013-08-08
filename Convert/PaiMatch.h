#pragma once

#include"Procon2013/Core/Core.h"
#include<iostream>

#include"CharArray.h"
#include"CharArrayNumeric.h"
#include"InPaiDivide.h"

namespace pro{

class PRO_EXPORTS PaiMatch
{
private:

	int digits;			// �}�b�`���O���錅��
	int length;			// �}�b�`���O����Ƃ��̕����񒷂�
	int line_length;	// �����񂪌ׂ����C���̒���

	int char_num;		// �����ԍ�
	//int line_num;		// ���C���ԍ�
	//int file_num;		// �t�@�C���ԍ�
	//int dir_num;		// �f�B���N�g���ԍ�

	long long unsigned count;			// ��v���J�E���g

	CharArray c_str;	// �}�b�`�ۑ�������
	CharArrayNumeric num_str; // ���l������

	InPaiDivide ipd;	// �~���������t�@�C���f�[�^�擾�N���X

	Dir path;
	std::fstream fs;
	std::fstream count_fs;

	bool load_flag;
	
	void setStr();
	void init();
	bool next();
	void open();
	void close();
	bool match();
	void matchOneLine();
	void output();

	// �r���o��
	void save();
	void last_save();
	void load();

public:
	PaiMatch(int digits=1,CharArrayNumeric::NumKind kind=CharArrayNumeric::HEX);
	~PaiMatch(void);

	int getDigits() const;

	void matching();

};

}
