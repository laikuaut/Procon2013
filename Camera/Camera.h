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
 * カメラフレームサイズ定数
 *	  QVGA：320×240
 *	  VGA：640×480
 *	  XGA：1024×768
 * 	  HD：1280×720
 *	  UXGA：1600×1200
 *	  FULL HD：1920×1080
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

	f_kind fk;		// フレームサイズの種類
	int height;		// フレーム高さ
	int width;		// フレーム幅
	int fps;		// 表示間隔時間

	long interval;	// 自動キャプチャインターバル
	long cap_time;	// 自動キャプチャ総時間

	Dir a_dir;		// 自動キャプチャ先ディレクトリ
	Dir m_dir;		// 手動キャプチャ先ディレクトリ
	string a_name;	// 手動キャプチャ出力ファイル名
	string m_name;	// 自動キャプチャ出力ファイル名
	string w_name;	// Window名

	cv::VideoCapture cap;	// キャプチャ
	vector<int> params;  // JPEG圧縮パラメータ

private:

	void printCaptureInfo();  // キャプチャ情報を表示
	void setCap();

public:
	// フルHD、fps=30ms
	Camera(int jpgCR=95);
	Camera(int width,int height,int fps=30,int jpgCR=95);
	Camera(f_kind fk,int fps=30,int jpgCR=95);

	~Camera(void);

	void setFk(f_kind fk);
	f_kind getFk();

	void setFrameSize(int width,int height);
	void getFrameSize(int *width,int *height);
	int getFrameWidth();
	int getFrameHeight();

	void setFps(int fps);
	int getFps();

	void manualCapture();

	void autoCapture();
	void autoCapture(long interval,long time);

	void setJPEGParams(int jpgCR=95);

	void setWindowName(string name);
	string getWindowName();

	void setTimes(long aInterval,long aTime);
	long getInterval();
	long getTime();

	void setAutoCapture(Dir aDir,string aFName);
	void setAutoCapture(Dir aDir,string aFName,long aInterval,long aTime);
	string getAutoCapName();
	Dir getAutoCapDir();

	void setManualCapture(Dir aDir,string aFName);
	string getManualCapName();
	Dir getManualDir();

};

}