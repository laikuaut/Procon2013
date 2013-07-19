#pragma once


#include"Procon2013/Core/Core.h"

#include<sstream>
#include<string>
#include<vector>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

namespace pro{

class PRO_EXPORTS cv::VideoCapture;

class PRO_EXPORTS Camera
{
public:

/**************************
 * �J�����t���[���T�C�Y�萔
 *	  QVGA�F320�~240
 *	  VGA�F640�~480
 *	  XGA�F1024�~768
 * 	  HD�F1280�~720
 *	  UXGA�F1600�~1200
 *	  FULL HD�F1920�~1080
 **/
	typedef enum f_kind{
		QVGA,VGA,XGA,HD,UXGA,FULL_HD,FREE
	}f_kind;

	int test;

/*********************** 
 * �t���[���T�C�Y�萔
 **/
public:
	static int const QVGA_WIDTH = 320;
	static int const QVGA_HEIGHT = 240;

	static int const VGA_WIDTH = 640;
	static int const VGA_HEIGHT = 480;

	static int const XGA_WIDTH = 1040;
	static int const XGA_HEIGHT = 768;

	static int const HD_WIDTH = 1280;
	static int const HD_HEIGHT = 720;

	static int const UXGA_WIDTH = 1600;
	static int const UXGA_HEIGHT = 1200;

	static int const FULL_HD_WIDTH = 1920;
	static int const FULL_HD_HEIGHT = 1080;

/*********************** 
 *    �����o�ϐ� 
 **/
private:
	f_kind fk;		// �t���[���T�C�Y�̎��
	int height;		// �t���[������
	int width;		// �t���[����
	int fps;		// �\���Ԋu����

	Dir dir;		// �L���v�`����f�B���N�g��
	string name;	// �o�̓t�@�C���� and Window��

	cv::VideoCapture cap;	// �L���v�`��
	vector<int> params;  // JPEG���k�p�����[�^

	// �L���v�`������\��
	void printCaptureInfo();
	
	void setCap();
	void setJPEGParams();


/*********************** 
 * �R���X�g���N�^
 **/
public:
	// �t��HD�Afps=30ms
	Camera(void);
	Camera(int width,int height,int fps=30);
	Camera(f_kind fk,int fps=30);

/*********************** 
 * �f�X�g���N�^
 **/
public:
	~Camera(void);

/*********************** 
 * �v���p�e�B
 **/
public:
	void setFk(f_kind fk);
	f_kind getFk();

	void setFrameSize(int width,int height);
	void getFrameSize(int *width,int *height);

	void setFps(int fps);
	int getFps();

	void manualCapture();
	void autoCapture(long interval,long time);

};

}