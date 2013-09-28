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
	w = img.size().width;
	h = img.size().height;
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
	img.data;
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

void Image::oneColor(cv::Scalar scal){
	img = cv::Mat(cv::Size(w, h), CV_8UC3, scal);
}

void Image::reversal(const Image& src){
	img = ~src.img;
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
			w = img.size().width;
			h = img.size().height;
		}
	}catch(const FileException& e){
		e.showError();
		exit(EXIT_FAILURE);
	}
}

void Image::save(string name){
	vector<int> params;
	params = vector<int>(2);
	// JPEGà≥èkÉpÉâÉÅÅ[É^
	params[0] = CV_IMWRITE_JPEG_QUALITY;
	params[1] = 95;
	cv::imwrite(path.pwd(name), img , params);
}

bool Image::empty(){
	return img.empty();
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

void Image::rectangle(cv::Point center,int w,int h,int angle,cv::Scalar scal,int thickness){
	cv::Point pt1[1][4];
	int npt[] = {4};
	//double c=cos(angle*CV_PI/180),s=sin(angle*CV_PI/180);
	const cv::Point *ppt[1] = {pt1[0]};
	pt1[0][0] = cv::Point(center+Calc::PointRotate(w/2,h/2,angle));
	pt1[0][1] = cv::Point(center+Calc::PointRotate(w/2,-h/2,angle));
	pt1[0][2] = cv::Point(center+Calc::PointRotate(-w/2,-h/2,angle));
	pt1[0][3] = cv::Point(center+Calc::PointRotate(-w/2,h/2,angle));
	cv::polylines(img,ppt,npt,1,true,scal,thickness);
}

void Image::line(cv::Point pt1,cv::Point pt2,cv::Scalar scal,int thickness){
	cv::line(img,pt1,pt2,scal,thickness,8);
}

void Image::triangle(cv::Point pt1,cv::Point pt2,cv::Point pt3,cv::Scalar scal,int thickness){
	cv::line(img,pt1,pt2,scal,thickness,8);
	cv::line(img,pt2,pt3,scal,thickness,8);
	cv::line(img,pt3,pt1,scal,thickness,8);
}

void Image::imshow(string windowName){
	cv::imshow(windowName,img);
}

Image::operator cv::Mat &(){
	return img;
}

Image::operator unsigned char *(){
	return img.data;
}
Image::operator const unsigned char *(){
	return img.data;
}

Image::operator cv::Size (){
	return cv::Size(w,h);
}



}