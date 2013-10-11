#include "CharPositions.h"

namespace pro{

CharPositions::CharPositions(void)
{
}


CharPositions::~CharPositions(void)
{
}

void CharPositions::init(char value,int i){
	this->value = value;
	positions.push_back(i);
}

void CharPositions::add(int i){
	positions.push_back(i);
}

char CharPositions::getValue() const{
	return value;
}

int CharPositions::getNumAtStrNum(int i) const{
	for(int j=0;j<positions.size();j++){
		if(i==positions[j]) return j;
	}
}

void CharPositions::erase(int i){
	vector<int>::iterator it = positions.begin();
	positions.erase(it+i);
}

int CharPositions::size() const{
	return positions.size();
}

int CharPositions::operator[](int i){
	return positions[i];
}

}