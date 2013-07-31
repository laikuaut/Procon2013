#pragma once

#include"Procon2013/Core/Core.h"

namespace pro{

class PRO_EXPORTS CharArray
{
private:

	static int const DEFAULT_LENGTH = 8192;

	char *c_str;
	int length;

public:
	
	CharArray(void);
	CharArray(int length);
	CharArray(const char* c_str);
	CharArray(const char* c_str,int length);

	~CharArray(void);

	void create(const CharArray& obj);
	void create(const char* c_str);
	void create(const char* c_str,int length);

	void clear();

	void copy(CharArray& obj) const;
	void copy(char* c_str) const;
	void copy(char* c_str,int& length) const;

	void zero();
	void zero(int length);

	void allSame(char c);
	void allSame(char c,int length);
	
	void push_back(const CharArray& obj);
	void push_back(const char* c_str);
	void push_back(const char* c_str,int length);

	void pop_flont(int length);
	
	bool Equal(const CharArray& obj) const;
	bool Equal(const char* c_str) const;

	char getChar(int n);
	int getLength() const;
	const char* getCstr() const;
	
	char operator[](int n);
	char operator()(int n);
	const char* operator()(int s_num,int e_num);

	operator const char* () const;
	operator char* ();

	const CharArray& operator=(const char* c_str);
	//const CharArray& operator=(CharArray& obj);
	
	const CharArray& operator+=(const char* c_str);
	//const CharArray& operator+=(CharArray& obj);

	const char* operator+(const char* c_str);
	//const char* operator+(const CharArray& obj);

	bool operator==(const CharArray& obj) const;
	bool operator==(const char* c_str) const;

	bool operator!=(const CharArray& obj) const;
	bool operator!=(const char* c_str) const;

	void static test();
};

}