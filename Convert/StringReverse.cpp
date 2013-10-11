//#include "StringReverse.h"
//
//namespace pro{
//
//StringReverse::StringReverse(void)
//{
//}
//
//
//StringReverse::~StringReverse(void)
//{
//}
//
//void StringReverse::init(vector<char> value){//,int pos){//,int rev_pos){
//	this->value = value;
//	//positions.push_back(pos);
//	//reversePositions.push_back(rev_pos);
//}
//
//void StringReverse::add(int pos){//,int rev_pos){
//	positions.push_back(pos);
//	//reversePositions.push_back(rev_pos);
//}
//
//vector<char> StringReverse::getValue() const{
//	return value;
//}
//
//void StringReverse::erase(int i){
//	vector<int>::iterator it = positions.begin();
//	positions.erase(it+i);
//	//it = reversePositions.begin();
//	//reversePositions.erase(it+i);
//}
//
//void StringReverse::reverse(vector<char> &str){
//	vector<char> reverse = str;
//	for(int i=0;i<reverse.size();i++){
//		str[i] = reverse[reverse.size()-1-i];
//	}
//}
//
//int StringReverse::size() const{
//	return positions.size();
//}
//
//int StringReverse::length() const{
//	return value.size();
//}
//
//bool StringReverse::equal(vector<char> str,bool rev){
//	if(!rev){
//		bool flag=true;
//		if(value.size()!=str.size()) return false;
//		for(int i=0;i<value.size();i++){
//			if(value[i]!=str[i]) flag=false;
//		}
//		return flag;
//	}else{
//		bool flag=true;
//		if(value.size()!=str.size()) return false;
//		for(int i=0;i<value.size();i++){
//			if(value[value.size()-1-i]!=str[i]) flag=false;
//		}
//		return flag;
//	}
//}
//
//int StringReverse::operator[](int i){
//	return positions[i];
//}
//
//}