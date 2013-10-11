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

void StringPositions::add(int i,bool rev){
	if(!rev)
		positions.push_back(i);
	else
		reversePositions.push_back(i);
}

vector<char> StringPositions::getValue() const{
	return value;
}

void StringPositions::erase(int i,bool rev){
	if(rev){
		vector<int>::iterator it = positions.begin();
		positions.erase(it+i);
	}else{
		vector<int>::iterator it = reversePositions.begin();
		reversePositions.erase(it+i);
	}
}

int StringPositions::size(bool rev) const{
	if(!rev){
		return positions.size();
	}else{
		return reversePositions.size();
	}
}

int StringPositions::length() const{
	return value.size();
}

bool StringPositions::equal(vector<char> str,bool rev){
	if(!rev){
		bool flag=true;
		if(value.size()!=str.size()) return false;
		for(int i=0;i<value.size();i++){
			if(value[i]!=str[i]) flag=false;
		}
		return flag;
	}else{
		bool flag=true;
		if(value.size()!=str.size()) return false;
		for(int i=0;i<value.size();i++){
			if(value[value.size()-1-i]!=str[i]) flag=false;
		}
		return flag;
	}
}

int StringPositions::operator[](int i){
	if(i>=0){
		return positions[i];
	}else{
		return reversePositions[-(i+1)];
	}
}

}