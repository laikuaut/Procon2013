#include "StringPositions.h"

namespace pro{

StringPositions::StringPositions(void)
{
}


StringPositions::~StringPositions(void)
{
}

void StringPositions::init(vector<char> value,int i){
	this->value = value;
	positions.push_back(i);
}

void StringPositions::add(int i){
	positions.push_back(i);
}

vector<char> StringPositions::getValue() const{
	return value;
}

void StringPositions::erase(int i){
	vector<int>::iterator it = positions.begin();
	positions.erase(it+i);
}

int StringPositions::size() const{
	return positions.size();
}

int StringPositions::length() const{
	return value.size();
}

bool StringPositions::equal(vector<char> str){
	bool flag=true;
	if(value.size()!=str.size()) return false;
	for(int i=0;i<value.size();i++){
		if(value[i]!=str[i]) flag=false;
	}
	return flag;
}

int StringPositions::operator[](int i){
	return positions[i];
}

}