#pragma once

#include"Procon2013/Core/Core.h"
#include<opencv2\core\core.hpp>
#include"Image.h"
#include"Labeling.h"

namespace pro{

class PRO_EXPORTS LabelingCenter
{
private:

	Labeling labels;
	vector<cv::Point> centers;

public:
	LabelingCenter(cv::Size size);
	~LabelingCenter(void);

	void init(cv::Size size);
	void setCenter(const unsigned char* bins);
	void circleFilter();
	void outputCenter();

	cv::Point operator() (const int num);

public:
	int num;
	vector<int> sizes;
	vector<char> flags;
};

}