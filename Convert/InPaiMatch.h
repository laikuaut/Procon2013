#pragma once

#include"PaiMatch.h"

namespace pro{

class InPaiMatch : public PaiMatch
{
private:

	int dir_num;
	int file_num;
	int line_num;

	int flag_count;

	void init();		// �������֐�

	void open();		// �J��
	void keyEvent(){}	// �L�[�C�x���g�֐�

	void setDigits(int digits);

public:

	InPaiMatch(int digits=1, CharArrayNumeric::NumKind kind=CharArrayNumeric::HEX);
	~InPaiMatch(void);
	
	int getDirNum() const;
	int getFileNum() const;
	int getLineNum() const;
	int getCharNum() const;
	long long unsigned getCount() const;
	const char* getNumStr() const;
	
	bool setNum();
	bool setNum(const char* str);

	bool next();		// ���̗v�f�ɃA�N�Z�X
	bool nextNum();		// ���̐��l�ɃA�N�Z�X

	void Reset();

	void nowDisplay();	// ���ݏ󋵂̕\��


};

}
