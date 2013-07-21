#include "Camera.h"

#include<iostream>

using namespace std;

namespace pro{

Camera::Camera(int jpgCR){
	initCap(FULL_HD,0,0,30,jpgCR);
}

Camera::Camera(int width,int height,int fps,int jpgCR){
	initCap(FULL_HD,width,height,fps,jpgCR);
}

Camera::Camera(Camera::f_kind fk,int fps,int jpgCR){
	initCap(fk,0,0,fps,jpgCR);
}

Camera::~Camera(void){

}

void Camera::printCaptureInfo() const{
	string fk_str;
	switch(fk){
	case QVGA:
		fk_str = "QVGA";
		break;
	case VGA:
		fk_str = "VGA";
		break;
	case XGA:
		fk_str = "XGA";
		break;
	case HD:
		fk_str = "HD";
		break;
	case UXGA:
		fk_str = "UVGA";
		break;
	case FULL_HD:
		fk_str = "FULL_HD";
		break;
	case FREE:
		fk_str = "FREE";
	default:
		break;
	}
	cout << "Frame_Kind : " << fk_str << "(" << width << "x" << height << ")" << endl;
	cout << "FPS : " << fps << endl;
	cout << "JPEG���k�p�����[�^ : " << params[1] << endl;
}

void Camera::initCap(f_kind aFk,
					 int aWidth,
					 int aHeight,
					 int fps,
					 int jpgCR){

	cap = cv::VideoCapture(0);

	if(aFk == FREE)
		setFrameSize(aWidth,aHeight);
	else
		setFk(aFk);

	setJPEGCR(jpgCR);

	setFps(fps);
	setTimes(10,60);
	
	setAutoCaptureFileName("aCap");
	setManualCaptureFileName("mCap");

	w_name = "Capture";
	a_dir = Dir("Auto_Cap");
	m_dir = Dir("Manual_Cap");

	setCounter(5);

	// �l�X�Ȑݒ�...
	cap.set(CV_CAP_PROP_FRAME_WIDTH, width);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, height);

}

void Camera::setFk(Camera::f_kind fk){
	this->fk = fk;
	switch(fk){
	case QVGA:
		this->width = QVGA_WIDTH;
		this->height = QVGA_HEIGHT;
		break;
	case VGA:
		this->width = VGA_WIDTH;
		this->height = VGA_HEIGHT;
		break;
	case XGA:
		this->width = XGA_WIDTH;
		this->height = XGA_HEIGHT;
		break;
	case HD:
		this->width = HD_WIDTH;
		this->height = HD_HEIGHT;
		break;
	case UXGA:
		this->width = UXGA_WIDTH;
		this->height = UXGA_HEIGHT;
		break;
	case FULL_HD:
		this->width = FULL_HD_WIDTH;
		this->height = FULL_HD_HEIGHT;
		break;
	default:
		break;
	}
}

Camera::f_kind Camera::getFk() const{
	return this->fk;
}

void Camera::setFrameSize(int width,int height){
	this->width = width;
	this->height = height;
	if(width == QVGA_WIDTH && height == QVGA_HEIGHT)
		this->fk = QVGA;
	else if(width == VGA_WIDTH && height == VGA_HEIGHT)
		this->fk = VGA;
	else if(width == XGA_WIDTH && height == XGA_HEIGHT)
		this->fk = XGA;
	else if(width == HD_WIDTH && height == HD_HEIGHT)
		this->fk = QVGA;
	else if(width == UXGA_WIDTH && height == UXGA_HEIGHT)
		this->fk = UXGA;
	else if(width == FULL_HD_WIDTH && height == FULL_HD_HEIGHT)
		this->fk = FULL_HD;
	else
		this->fk = FREE;
}
void Camera::getFrameSize(int *width,int *height) const{
	*width = this->width;
	*height = this->height;
}

int Camera::getFrameWidth() const{
	return this->width;
}

int Camera::getFrameHeight() const{
	return this->height;
}

void Camera::setFps(int fps){
	if(fps<1)
		throw OutOfRangeException<int>(fps,"fps","Camera.cpp","Camera::setFps(int)");
	this->fps = fps;
}

int Camera::getFps() const{
	return this->fps;
}

void Camera::setJPEGCR(int jpgCR){
	params = vector<int>(2);
	
	// JPEG���k�p�����[�^
	params[0] = CV_IMWRITE_JPEG_QUALITY;
	params[1] = jpgCR;
}

int Camera::getJPEGCR() const{
	return params[1];
}

void Camera::setTimes(long aInterval,long aTime){
	if(aInterval <= 0)
		throw OutOfRangeException<long>(aInterval,"aInterval","Camera.cpp","Camera::setTimes(long,long)");
	else if(aTime < 0)
		throw OutOfRangeException<long>(aTime,"aTime","Camera.cpp","Camera::setTimes(long,long)");
	this->interval = aInterval;
	this->cap_time = aTime;
}

long Camera::getInterval() const{
	return this->interval;
}

long Camera::getTime() const{
	return this->cap_time;
}

void Camera::setAutoCaptureFileName(const string& aFName){
	if(Dir::isPath(aFName))
		throw DirException(DirException::PATH_ERROR,aFName,"Camera.cpp","Camera::setAutoCaptureFileName(string)");
	this->a_name = aFName;
}

const string Camera::getAutoCaptureFileName() const{
	return this->a_name;
}

void Camera::setManualCaptureFileName(const string& aFName){
	if(Dir::isPath(aFName))
		throw DirException(DirException::PATH_ERROR,aFName,"Camera.cpp","Camera::setManualCaptureFileName(string)");
	this->m_name = aFName;
}

const string Camera::getManualCaptureFileName() const{
	return this->m_name;
}

void Camera::setCounter(int aCounter){
	if(counter < 1)
		throw OutOfRangeException<int>(aCounter,"aCounter","Camera.cpp","Camera::setCounter(int)");
	this->counter = aCounter;
}

int Camera::getCounter() const{
	return this->counter;
}

void Camera::manualCapture(){

	// �J�������I�[�v���ł������̊m�F
	if(!cap.isOpened()){
		cout << "not camera opened" << endl;
		return;
	}

	printCaptureInfo();

	cout<<"c:�L���v�`���[�ۑ�"<<endl;
	cout<<"q:�I��"<<endl;

	cv::namedWindow(w_name, CV_WINDOW_NORMAL|CV_WINDOW_KEEPRATIO);

	// �L���v�`���摜�ԍ�
	long num=0;	

	while(1) {
		cv::Mat frame;
		cap >> frame;  // �L���v�`��

		// �L���v�`���ԍ��p
		stringstream ss;
		ss.str("");
		ss.clear(stringstream::goodbit);

		// Window�̐����m�F
		void* life = cvGetWindowHandle(w_name.c_str());
		if(life == NULL) break;

		cv::imshow(w_name, frame); // �\��
		switch(cv::waitKey(fps)){
		case 'c':  // �摜�ۑ�
			ss << num++;
			cv::imwrite(m_dir.pwd() + m_name + ss.str() + ".jpg", frame, params);
			cout << m_name << ss.str() << ".jpg" << endl;
			break;
		case 'q':  // �I��
			cv::destroyWindow(w_name);
			break;
		default:			
			break;
		}
	}
}

void Camera::autoCapture(){
	autoCapture(interval,cap_time);
}

void Camera::autoCapture(long interval,long time){

	pro::Timer timer;

	// �L���v�`���摜�i���o�[
	long num;
	long num_m=0;
	
	// �B�e�J�E���^�[�p
	int counter;
	int init_counter;
	if(interval > this->counter)
		counter = init_counter = this->counter;
	else
		counter = init_counter = interval;

	// �J�������I�[�v���ł������̊m�F
	if(!cap.isOpened()){
		cout << "not camera opened" << endl;
		return;
	}

	// �J�����B�e���̕\��
	printCaptureInfo();
	
	// ������@�{�������ԏ��\��
	cout << "s:�J�n �X�y�[�X:��~/�ĊJ r:���Z�b�g q:�I�� " << endl;
	cout << "��������:" << time << endl;
	cout << "�Ԋu:" << interval << "[s]" << endl;

	cv::namedWindow(w_name, CV_WINDOW_NORMAL|CV_WINDOW_KEEPRATIO);
	
	// �J�������[�v�J�n
	while(1) {
		cv::Mat frame;
		cap >> frame;  // �L���v�`��

		// �����L���v�`���ԍ��p
		stringstream ss;
		ss.str("");
		ss.clear(stringstream::goodbit);
		// �蓮�L���v�`���ԍ��p
		stringstream ss_m;
		ss_m.str("");
		ss_m.clear(stringstream::goodbit);

		// Window�̐����m�F
		void* life = cvGetWindowHandle(w_name.c_str());
		if(life == NULL) break;

		cv::imshow(w_name, frame); // �\��
		switch(cv::waitKey(fps)){
		case 's':  // �^�C�}�J�n
			timer.start();
			num=0;	
			cout << "start" << endl;
			break;
		case ' ':  // ��~/�ĊJ
			// ��~����
			if(timer.getState()==Timer::START){
				timer.stop();
				cout << "stop:" << timer.getNow() << endl;
			// �ĊJ����
			}else if(timer.getState()==Timer::STOP){
				timer.restart();
				cout << "restart" << endl;
			}
			break;
		case 'c':  // �蓮�L���v�`��
			ss_m << num_m++;
			cv::imwrite(m_dir.pwd() + m_name + ss_m.str() + ".jpg", frame, params);
			cout << m_name << ss_m.str() << ".jpg" << endl;
			break;
		case 'r':  // ���Z�b�g
			timer.reset();
			cout << "reset" << endl;
			break;
		case 'q':  // �I��
			cv::destroyWindow(w_name);
			break;
		default:	
			break;
		}

		// �B�e����
		if(timer.getDiff() > Timer::m_sec(interval)){

			// �m�F�\��
			//cout << timer.getDiff() << endl;
			//cout << timer.getNow() << endl;
			try{
				timer.lap(Timer::m_sec(interval));
			}catch(const OutOfRangeException<long>& e){
				e.showError();
				throw OutOfRangeException<long>(interval,"interval","Camera.cpp","autoCapture()");
			}
			ss << num++;
			cv::imwrite(a_dir.pwd() + a_name + ss.str() + ".jpg", frame, params);
			cout << a_name << ss.str() << ".jpg" << endl;
			counter = init_counter;

		// �B�e�J�E���^
		}else if((Timer::m_sec(interval) - timer.getDiff())/Timer::PER_SEC < counter){
			cout << counter-- << " " << flush;
		}

		// �B�e�I��
		if(timer.getNow() > Timer::m_sec(time) && time!=0){
			cv::destroyWindow(w_name);		
		}
	}	
}

}

