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
     * 課題： 数値の順序を考える
	 */

	void setNum(const char* str);

	// 後置きインクリメント演算子
	const char* operator ++(int);
	// 前置きインクリメント演算子
	const CharArrayNumeric& operator ++();
	// 加算代入
	const CharArrayNumeric& operator +=(int num);
	
	// 後置きデクリメント演算子
	const char* operator --(int);
	// 前置きデクリメント演算子
	const CharArrayNumeric& operator --();
	// 減算代入
	const CharArrayNumeric& operator -=(int num);
};

}
