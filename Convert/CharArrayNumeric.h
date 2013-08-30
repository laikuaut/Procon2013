#pragma once

#include"Procon2013/Core/Core.h"
#include"CharArray.h"

namespace pro{

class PRO_EXPORTS CharArrayNumeric : private CharArray
{
public:

	typedef enum NumericKind{
		DEC
		,OCT
		,HEX
		,STRING
		,ORIGINAL
	}NumKind;

private:

	NumKind kind;

	const char* numString;
	int numLength;

	int getNumStringNum(char c);

public:
	CharArrayNumeric(void);
	CharArrayNumeric(int length);
	CharArrayNumeric(NumKind kind);
	CharArrayNumeric(NumKind kind,int length);
	~CharArrayNumeric(void);

	int getNumLength() const;
	const char* getNumString() const;
	NumKind getNumKind() const;

	char getChar(int n);
	int getLength() const;
	const char* getCstr() const;

	void init(int length,NumKind kind,const char* str=nullptr,int num=0);

	void setLength(int length);
	void setNumKind(NumKind kind,const char* str=nullptr,int num=0);

	bool add();
	bool add(int num);
	
	void addDigits();
	void addDigits(int num);

	bool sub();
	bool sub(int num);

	void first_num();
	void first_num(int length);

	void last_num();
	void last_num(int length);

	// 文字列数字セット
	void setNum(const char* str);
	void setNum(const char* str,int length);

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

	bool Equal(const CharArray& obj) const;
	bool Equal(const char* c_str) const;

	bool operator==(const CharArray& obj) const;
	bool operator==(const char* c_str) const;

	char operator[](int n);
	char operator()(int n);

	operator const char* () const;
	operator char* ();
};

}
