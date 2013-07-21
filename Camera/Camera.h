#pragma once


#include"Procon2013/Core/Core.h"

#include<sstream>
#include<string>
#include<vector>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

namespace pro{

// warning C4251: 'pro::Camera::cap' : class 'cv::VideoCapture' �� __export �L�[���[�h���g���� class 'pro::Camera' �ɃG�N�X�|�[�g���Ă��������B
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

private:

	f_kind fk;		// �t���[���T�C�Y�̎��
	int height;		// �t���[������
	int width;		// �t���[����	

	int fps;		// �\���Ԋu����

	long interval;	// �����L���v�`���C���^�[�o��
	long cap_time;	// �����L���v�`��������

	string a_name;	// �蓮�L���v�`���o�̓t�@�C����
	string m_name;	// �����L���v�`���o�̓t�@�C����

	int counter;

	cv::VideoCapture cap;	// �L���v�`��
	vector<int> params;  // JPEG���k�p�����[�^

public:

	string w_name;	// Window��

	Dir a_dir;		// �����L���v�`����f�B���N�g��
	Dir m_dir;		// �蓮�L���v�`����f�B���N�g��

private:

	void printCaptureInfo() const;  // �L���v�`������\��
	void initCap(f_kind aFk,int aWidth,int aHeight,int fps,int jpgCR);

public:
	Camera(int jpgCR=95);
	Camera(int width,int height,int fps=30,int jpgCR=95);
	Camera(f_kind fk,int fps=30,int jpgCR=95);

	~Camera(void);

	void setFk(f_kind fk);
	f_kind getFk() const;

	void setFrameSize(int width,int height);
	void getFrameSize(int *width,int *height) const;
	int getFrameWidth() const;
	int getFrameHeight() const;

	void setFps(int fps);
	int getFps() const;

	void setJPEGCR(int jpgCR=95);
	int getJPEGCR() const;

	void setTimes(long aInterval,long aTime);
	long getInterval() const;
	long getTime() const;
	
	void setAutoCaptureFileName(const string& aFName);
	const string getAutoCaptureFileName() const;

	void setManualCaptureFileName(const string& aFName);
	const string getManualCaptureFileName() const;

	void setCounter(int aCounter);
	int getCounter() const;
	
	void manualCapture();

	void autoCapture();
	void autoCapture(long interval,long time);

};

}