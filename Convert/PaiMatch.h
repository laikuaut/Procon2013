#pragma once

#include"Procon2013/Core/Core.h"
#include<iostream>

#include"CharArray.h"
#include"CharArrayNumeric.h"
#include"InPaiDivide.h"

namespace pro{

class PRO_EXPORTS PaiMatch
{
protected:

	int digits;						// �}�b�`���O���錅��

	int char_num;					// �����ԍ�
	std::ifstream::pos_type pos;	// �J�n�ʒu

	long long unsigned count;		// ��v���J�E���g

	CharArrayNumeric num_str;		// ���l������

	Dir path;						// �f�B���N�g���p�X
	std::fstream fs;				// ���W�t�@�C���X�g���[��
	std::fstream count_fs;			// �J�E���g�t�@�C���X�g���[��

	// �������֐�
	virtual void init();	

	// �J��
	virtual void open() = 0;
	// ����
	void close();					

	// ���ݏ󋵂̕\��
	virtual void nowDisplay() = 0;	
	// �L�[�C�x���g�֐�
	virtual void keyEvent() = 0;	

public:
	PaiMatch(int digits=1,CharArrayNumeric::NumKind kind=CharArrayNumeric::HEX);
	~PaiMatch(void);

	// �����擾
	int getDigits() const;
	
};

}
