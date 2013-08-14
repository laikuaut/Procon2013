#pragma once

#include"PaiMatch.h"

namespace pro{

class InPaiMatch : public PaiMatch
{
private:

	int dir_num;
	int file_num;
	int line_num;

	void init();		// �������֐�

	void open();		// �J��
	void nowDisplay(){}	// ���ݏ󋵂̕\��
	void keyEvent(){}	// �L�[�C�x���g�֐�

	void setCount();

public:
	
	int getDirNum() const;
	int getFileNum() const;
	int getLineNum() const;
	int getCharNum() const;
	int getCount() const;
	
	void setNum(const char* str);

	bool next();		// ���̐��l�ɃA�N�Z�X

	InPaiMatch(void);
	~InPaiMatch(void);

};

}
