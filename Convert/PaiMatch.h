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
	int line_num;		// ���C���ԍ�
	int file_num;		// �t�@�C���ԍ�
	int dir_num;		// �f�B���N�g���ԍ�

	long count;

	CharArray c_str;	// �}�b�`�ۑ�������
	CharArrayNumeric num_str; // ���l������

	InPaiDivide ipd;	// �~���������t�@�C���f�[�^�擾�N���X

	std::fstream fs;
	std::fstream count_fs;
	
	void setStr();

	void init();
	bool next();

	bool match();

	void matchOneLine();

	void output();

public:
	PaiMatch(void);
	~PaiMatch(void);

	void matching();

};

}
