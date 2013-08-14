#pragma once

#include"PaiMatch.h"

namespace pro{

class OutPaiMatch : public PaiMatch
{
private:
	int length;			// �}�b�`���O����Ƃ��̕����񒷂�
	int line_length;	// �����񂪌ׂ����C���̒���
	
	InPaiDivide ipd;	// �~���������t�@�C���f�[�^�擾�N���X
	
	CharArray c_str;	// �}�b�`�ۑ�������	

	bool load_flag;		// ���[�h�t���O


	// ��������X�V
	void setStr();		
	// �������v
	bool match();		
	// ��񕶎����v
	void matchOneLine();
	// ��v���W�o��
	void output();		

	/*****************************
	 *  �r���o��
	 */
	// �r���o�ߕۑ�
	void save();		
	// �Ō�܂ň�v�������̕ۑ�
	void last_save();	
	// �r���o�߃��[�h
	void load();		
	// ���̐��l�ɃA�N�Z�X
	bool next();

	/*****************************
	 *  �I�[�o�[���C�h�֐�
	 */
	// �������֐�
	void init();		
	// �J��
	void open();		
	// ���ݏ󋵂̕\��
	void nowDisplay();	
	// �L�[�C�x���g�֐�
	void keyEvent();	

public:

	OutPaiMatch(int digits=1,CharArrayNumeric::NumKind kind=CharArrayNumeric::HEX);
	~OutPaiMatch(void);
	
	void matching();

};

}
