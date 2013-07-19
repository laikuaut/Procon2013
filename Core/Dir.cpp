#include "Dir.h"

#include<direct.h>
#include<iostream>

#include<boost/filesystem.hpp>

namespace pro{

Dir::Dir(void)
{/*
	rel_path = ".";
	char* path =new char[512];
	path = _getcwd(NULL,512);
	drive_name = path[0];
	abs_path = charToString(path);*/
}

Dir::Dir(string path){

}

Dir::~Dir(void)
{

}

bool Dir::isAbsPath(string path){
	string drive = drive_name + ":\\";
	string::size_type index = path.find(drive);
	return index == string::npos;
}

bool Dir::isRelPath(string path){
	return !isAbsPath(path);
}

std::string Dir::pwd(){
	return charToString(_getcwd(NULL,512));
}

void Dir::create(string path){

}

void Dir::remove(string path){

}

void Dir::cd(string path){

}

}