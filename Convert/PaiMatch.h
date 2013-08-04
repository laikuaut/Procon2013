#pragma once

#include"Procon2013/Core/Core.h"
#include<iostream>

#include"CharArray.h"
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

	CharArray c_str;	// �}�b�`������
	InPaiDivide ipd;	// �~���������t�@�C���f�[�^�擾�N���X


public:
	PaiMatch(void);
	~PaiMatch(void);
};

}
