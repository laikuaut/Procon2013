#include "Image.h"

namespace pro{

Image::Image(void) : path(Dir()){
	
}

void Image::init(int width,int height){
	w = width;
	h = height;
	img = cv::Mat::zeros(cv::Size(w,h),CV_8UC3);
}

void Image::w_h_reset(){
	w = img.rows;
	h = img.cols;
}

void Image::release(){
	if(!img.empty()){
		img.release();
	}
}

void Image::clone(const Image& src){
	release();
	w = src.w;
	h = src.h;
	img = src.img.clone();
}

void Image::swap(Image& src){
	Image tmp;
	tmp.img = img.clone();
	tmp.w = w;
	tmp.h = h;
	img = src.img.clone();
	w = src.w , h = src.h;
	src.clone(tmp);	
}

void Image::resize(const Image& src){
	cv::resize(src.img,img,cv::Size(w,h));
}
void Image::resize(const Image& src,double fx,double fy){
	cv::resize(src.img,img,cv::Size(),fx,fy);
	w_h_reset();
}
void Image::resize(const Image& src,cv::Size size){
	cv::resize(src.img,img,size);
	w_h_reset();
}

void Image::grayeScale(const Image& src){
	cv::cvtColor(src.img, img, CV_BGR2GRAY);
	w_h_reset();
}

void Image::binarization(const Image& src){
	cv::threshold(src.img, img, 0, 255, cv::THRESH_BINARY_INV|cv::THRESH_OTSU);
	w_h_reset();
}

void Image::adaptiveBinarization(const Image& src){
	cv::adaptiveThreshold(src.img, img, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 7, 8);
	w_h_reset();
}

void Image::load(string name){
	try{
		if(!path.isExist(name))
			throw FileException(FileException::NOT_EXIST,path.pwd(name),"Image.cpp","Image::Load()",__LINE__);
		else if(path.isDirectory(name))
			throw FileException(FileException::DIRECTORY,path.pwd(name),"Image.cpp","Image::Load()",__LINE__);
		else{
			img = cv::imread(path.pwd(name), 1);
			w = img.rows;
			h = img.cols;
		}
	}catch(const FileException& e){
		e.showError();
		exit(EXIT_FAILURE);
	}
}

void Image::save(string name){
	vector<int> params;
	params = vector<int>(2);
	// JPEGˆ³kƒpƒ‰ƒ[ƒ^
	params[0] = CV_IMWRITE_JPEG_QUALITY;
	params[1] = 95;
	cv::imwrite(path.pwd(name), img , params);
}

void Image::circle(cv::Point center,int radius,cv::Scalar scal){
	cv::circle(img,center,radius,scal, -1, CV_AA);
}

void Image::rectangle(cv::Point pt1,cv::Point pt2,cv::Scalar scal,int thickness){
	cv::rectangle(img,pt1,pt2,scal,thickness,8);
}
void Image::rectangle(cv::Point center,int w,int h,cv::Scalar scal,int thickness){
	cv::rectangle(img,cv::Point(center.x-w/2,center.y-h/2),cv::Point(center.x+w/2,center.y+h/2),scal,thickness,8);
}

void Image::line(cv::Point pt1,cv::Point pt2,cv::Scalar scal,int thickness){
	cv::line(img,pt1,pt2,scal,thickness,8);
}

void Image::triangle(cv::Point pt1,cv::Point pt2,cv::Point pt3,cv::Scalar scal,int thickness){
	cv::line(img,pt1,pt2,scal,thickness,8);
	cv::line(img,pt2,pt3,scal,thickness,8);
	cv::line(img,pt3,pt1,scal,thickness,8);
}


Image::operator cv::Mat &(){
	return img;
}

//Image::operator cv::InputArray (){
//	return img.clone();
//}


//
//Image::Image(void)
//{
//	Init();
//}

//Image::Image(const string& aName){
//	Init(".",aName);
//}
//
//Image::Image(const string& aPath,const string& aName){
//	Init(aPath,aName);
//}
//
//
//Image::~Image(void)
//{
//
//}
//
//void Image::Init(string aPath,string aName){
//	path = Dir();
//	setPath(aPath);
//	setName(aName);
//	Load();
//}
//
//void Image::setName(const string& aName){
//	if(!Dir::isPath(aName))
//		throw DirException(DirException::PATH_ERROR,aName,"Image.cpp","Image::setName(string)",__LINE__);
//	else
//		this->name = aName;
//}
//
//string Image::getName() const{
//	return name;
//}
//
//void Image::setPath(const string& aPath){
//	if(!Dir::isPath(aPath))
//		throw DirException(DirException::PATH_ERROR,aPath,"Image.cpp","Image::Image(string)",__LINE__);
//	else
//		this->path.cd(aPath);
//}
//
//string Image::getPath() const{
//	return path.pwd();
//}
//
//void Image::Load(){
//	if(!path.isExist(name))
//		throw FileException(FileException::NOT_EXIST,path.pwd(name),"Image.cpp","Image::Load()",__LINE__);
//	else if(path.isDirectory(name))
//		throw FileException(FileException::DIRECTORY,path.pwd(name),"Image.cpp","Image::Load()",__LINE__);
//	else
//		img = cv::imread(path.pwd(name), 1);
//}
//
//void Image::Load(const string& aName){
//	setName(aName);
//	Load();
//}
//
//void Image::Save() const{
//	cv::imwrite(path.pwd(name), img);
//}
//
//void Image::Save(const string& aName){
//	setName(aName);
//	Save();
//}
//
//void Image::Show(){
//	cv::namedWindow(name);
//	cv::imshow(name,img);
//	cv::waitKey(0);
//	cv::destroyWindow(name);
//}
//
//Image Image::Clone(){
//	Image img(path.pwd(),name);
//	setMat(this->img.clone());
//	return img;
//}
//
//void Image::Resize(int width,int height){
//	cv::Mat dst;
//	cv::resize(img.clone(),img,cv::Size(width,height),cv::INTER_CUBIC);
//}
//
//cv::Mat& Image::operator() (){
//	return img;
//}
//
//void Image::setMat(cv::Mat& img){
//	this->img = img;
//}
//
//cv::Mat& Image::getMat(){
//	return img;
//}

}