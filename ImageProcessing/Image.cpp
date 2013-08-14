#include "Image.h"

namespace pro{

Image::Image(void)
{
	Init();
}

Image::Image(const string& aName){
	Init(".",aName);
}

Image::Image(const string& aPath,const string& aName){
	Init(aPath,aName);
}


Image::~Image(void)
{

}

void Image::Init(string aPath,string aName){
	path = Dir();
	setPath(aPath);
	setName(aName);
	Load();
}

void Image::setName(const string& aName){
	if(!Dir::isPath(aName))
		throw DirException(DirException::PATH_ERROR,aName,"Image.cpp","Image::setName(string)",__LINE__);
	else
		this->name = aName;
}

string Image::getName() const{
	return name;
}

void Image::setPath(const string& aPath){
	if(!Dir::isPath(aPath))
		throw DirException(DirException::PATH_ERROR,aPath,"Image.cpp","Image::Image(string)",__LINE__);
	else
		this->path.cd(aPath);
}

string Image::getPath() const{
	return path.pwd();
}

void Image::Load(){
	if(!path.isExist(name))
		throw FileException(FileException::NOT_EXIST,path.pwd(name),"Image.cpp","Image::Load()",__LINE__);
	else if(path.isDirectory(name))
		throw FileException(FileException::DIRECTORY,path.pwd(name),"Image.cpp","Image::Load()",__LINE__);
	else
		img = cv::imread(path.pwd(name), 1);
}

void Image::Load(const string& aName){
	setName(aName);
	Load();
}

void Image::Save() const{
	cv::imwrite(path.pwd(name), img);
}

void Image::Save(const string& aName){
	setName(aName);
	Save();
}

void Image::Show(){
	cv::namedWindow(name);
	cv::imshow(name,img);
	cv::waitKey(0);
	cv::destroyWindow(name);
}

cv::Mat& Image::operator() (){
	return img;
}


void Image::test(){
	Image img("Manual_Cap","mCap1.jpg");
	img.Show();
	img.setName("test.jpg");
	img.Save();
}

}