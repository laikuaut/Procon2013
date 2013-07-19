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

	int test;

/*********************** 
 * フレームサイズ定数
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
 *    メンバ変数 
 **/
private:
	f_kind fk;		// フレームサイズの種類
	int height;		// フレーム高さ
	int width;		// フレーム幅
	int fps;		// 表示間隔時間

	Dir dir;		// キャプチャ先ディレクトリ
	string name;	// 出力ファイル名 and Window名

	cv::VideoCapture cap;	// キャプチャ
	vector<int> params;  // JPEG圧縮パラメータ

	// キャプチャ情報を表示
	void printCaptureInfo();
	
	void setCap();
	void setJPEGParams();


/*********************** 
 * コンストラクタ
 **/
public:
	// フルHD、fps=30ms
	Camera(void);
	Camera(int width,int height,int fps=30);
	Camera(f_kind fk,int fps=30);

/*********************** 
 * デストラクタ
 **/
public:
	~Camera(void);

/*********************** 
 * プロパティ
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