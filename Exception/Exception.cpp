#include"Exception.h"

#include<iostream>

using namespace std;

namespace pro{

Exception::Exception(void) : name("Exception")
{

}

Exception::Exception(const string& aMessage) : 
							name("Exception"),
							message(aMessage){
}

Exception::Exception(const string& aMessage,
				const string& aFile,
				const string& aFunc) : 
							name("Exception"),
							message(aMessage),
							fileName(aFile),
							functionName(aFunc){
}

Exception::~Exception(void)
{

}

const char* Exception::getName() const throw(){
	return name.c_str();
}

const char* Exception::what() const throw(){
	return message.c_str();
}

const char* Exception::getFileName() const throw(){
	return fileName.c_str();
}

const char* Exception::getFuncName() const throw(){
	return functionName.c_str();
}

void Exception::showError() const throw(){
	cout	<< getName()  
		<< " [" << getFileName() << " , " << getFuncName() << "] "
				<< ": "	<< what()
				<< endl;
}

}