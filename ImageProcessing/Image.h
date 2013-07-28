#pragma once

#include"Procon2013/Core/Core.h"
#include"opencv2\core\core.hpp"
#include"opencv2\highgui\highgui.hpp"
#include<string>

class PRO_EXPORTS cv::Mat;

namespace pro{

class PRO_EXPORTS Image
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

	cv::Mat img;
	string name;
	Dir path;

private:

	void Init(string aPath=".",string aName="img.jpg");

public:
	
	Image(void);
	Image(const string& aName);
	Image(const string& aPath,const string& aName);
	~Image(void);

	/********************
	 *  画像処理基本
	 */

	void Clone();
	void Binarization();
	void GrayScale();
	void Resize();
	//void Clean();
	void Save() const;
	void Save(const string& aName);
	void Load();
	void Load(const string& aName);
	void Show();


	/********************
	 *  描写処理
	 */

	void Dot();
	void Circle();
	void Line();
	void Rect();
	void Triangle();

	/********************
	 *   プロパティ
	 */

	void setName(const string& aName);
	string getName() const;

	void setPath(const string& aPath);
	string getPath() const;

	static void test();

	cv::Mat& operator() ();

};

}
