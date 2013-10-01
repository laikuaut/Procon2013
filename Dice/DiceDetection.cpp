#include "DiceDetection.h"

namespace pro{

DiceDetection::DiceDetection(void)
{
}


DiceDetection::~DiceDetection(void)
{
}

/******************
 *   初期化
 */

void DiceDetection::init(int num,std::vector<cv::Point2f> points,std::vector<int> sizes){
	this->num = num;
	this->points.resize(num);
	memset(&this->points[0],0,sizeof(cv::Point2f)*num);
	this->sizes.resize(num);
	memset(&this->sizes[0],0,sizeof(int)*num);
	this->flags.resize(num);
	memset(&this->flags[0],0,sizeof(short)*num);
	for(int i=0;i<num;i++){
		this->points[i] = points[i];
		this->sizes[i] = sizes[i];
		this->flags[i] = 1;
	}

	//dot1points.resize(num);
	//memset(dot1points[0],0,sizeof(Dot1Point)*num);
	//for(int i=0;i<num;i++){
	//	dot1points[i].pt = points[i];
	//	dot1points[i].size = sizes[i];
	//}
}
void DiceDetection::init(LabelingCenter lc){
	this->num = lc.num;
	this->points.resize(lc.num);
	memset(&this->points[0],0,sizeof(cv::Point2f)*lc.num);
	this->sizes.resize(lc.num);
	memset(&this->sizes[0],0,sizeof(int)*lc.num);
	this->flags.resize(lc.num);
	memset(&this->flags[0],0,sizeof(short)*lc.num);
	for(int i=0;i<lc.num;i++){
		if(lc.flags[i]){
			this->points[i] = lc(i);
			this->sizes[i] = lc.sizes[i];
			this->flags[i] = 1;
		}
	}

	//dot1points.resize(lc.num);
	//memset(&dot1points[0],0,sizeof(Dot1Point)*lc.num);
	//for(int i=0;i<lc.num;i++){
	//	dot1points[i].pt = lc(i);
	//	dot1points[i].size = lc.sizes[i];
	//}
}


/******************
 *   サイコロの目判定
 */

/******************
 *   サイコロの目厳選削除
 */

/******************
 *   描写処理
 */

void DiceDetection::drawAllPoints(Image& img,cv::Scalar scal){
	for(int i=0;i<num;i++){
		img.circle(points[i],(int)sqrt(sizes[i]/CV_PI),scal);
	}
}



}