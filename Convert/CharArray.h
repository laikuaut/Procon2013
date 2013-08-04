#pragma once

#include"Procon2013/Core/Core.h"

namespace pro{

class PRO_EXPORTS CharArray
{
protected:

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
	
	virtual void push_back(const CharArray& obj);
	virtual void push_back(const char* c_str);
	virtual void push_back(const char* c_str,int length);
	virtual void push_flont(const CharArray& obj);
	virtual void push_flont(const char* c_str);
	virtual void push_flont(const char* c_str,int length);

	virtual void pop_flont(int length);
	virtual void pop_back(int length);
	
	virtual bool Equal(const CharArray& obj) const;
	virtual bool Equal(const char* c_str) const;

	virtual char getChar(int n);
	virtual int getLength() const;
	virtual const char* getCstr() const;
	
	virtual char operator[](int n);
	virtual char operator()(int n);
	virtual const char* operator()(int s_num,int e_num);

	virtual operator const char* () const;
	virtual operator char* ();

	virtual const CharArray& operator=(const char* c_str);
	//const CharArray& operator=(CharArray& obj);
	
	virtual const CharArray& operator+=(const char* c_str);
	//const CharArray& operator+=(CharArray& obj);

	virtual const char* operator+(const char* c_str);
	//const char* operator+(const CharArray& obj);

	virtual bool operator==(const CharArray& obj) const;
	virtual bool operator==(const char* c_str) const;

	virtual bool operator!=(const CharArray& obj) const;
	virtual bool operator!=(const char* c_str) const;

};

}