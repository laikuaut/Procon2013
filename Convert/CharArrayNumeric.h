#pragma once

#include"Procon2013/Core/Core.h"
#include"CharArray.h"

namespace pro{

class PRO_EXPORTS CharArrayNumeric : public CharArray
{
private:

	typedef enum NumericKind{
		DEC
		,OCT
		,HEX
		,ORIGINAL
	}NumKind;

	NumKind kind;

	const char* numString;
	int numLength;

	void setNumKind(NumKind kind,const char* str=nullptr,int num=0);

	int getNumStringNum(char c);

public:
	CharArrayNumeric(void);
	CharArrayNumeric(int length);
	CharArrayNumeric(NumKind kind);
	CharArrayNumeric(NumKind kind,int length);
	~CharArrayNumeric(void);

	int getNumLength() const;
	const char* getNumString() const;

	bool add();
	bool add(int num);

	bool sub();
	bool sub(int num);

	/*
     * �ۑ�F ���l�̏������l����
	 */

	void setNum(const char* str);

	// ��u���C���N�������g���Z�q
	const char* operator ++(int);
	// �O�u���C���N�������g���Z�q
	const CharArrayNumeric& operator ++();
	// ���Z���
	const CharArrayNumeric& operator +=(int num);
	
	// ��u���f�N�������g���Z�q
	const char* operator --(int);
	// �O�u���f�N�������g���Z�q
	const CharArrayNumeric& operator --();
	// ���Z���
	const CharArrayNumeric& operator -=(int num);
};

}
