#include "LabelingCenter.h"

#include<fstream>

namespace pro{

LabelingCenter::LabelingCenter(cv::Size size) : labels(size)
{
	init(size);
}


LabelingCenter::~LabelingCenter(void)
{
}

void LabelingCenter::init(cv::Size size){
	labels.init(size);
	centers.resize(labels.w*labels.h);
	memset(&centers[0],0,sizeof(cv::Point)*labels.w*labels.h);
}

void LabelingCenter::setCenter(const unsigned char* bins){
	int x,y;
	//vector<int> counts;
	// ラベリング処理
	labels.labeling(bins);
	
	num = labels.num;
	sizes.resize(num);
	flags.resize(num);
	memset(&sizes[0],0,sizeof(int)*num);
	memset(&flags[0],0,sizeof(char)*num);


	// 重心点の初期化
	for(int i=0;i<num;i++){
		centers[i].x = 0;
		centers[i].y = 0;
		sizes[i] = 0;
		flags[i] = 1;
	}
	// 重心計算開始
	for(y = 0;y < labels.h;y++){
		for(x = 0;x < labels.w;x++){
			centers[labels(x,y)].x += x;
			centers[labels(x,y)].y += y;
			sizes[labels(x,y)] += 1;
		}
	}
	for(int i=0;i<num;i++){
		centers[i].x /= sizes[i];
		centers[i].y /= sizes[i];
 	}
	// 重心計算終了

}

void LabelingCenter::circleFilter(){
	int _num=0;
	int x,y;
	
	vector<int> counts;
	counts.resize(num);
	memset(&counts[0],0,sizeof(int)*num);
	for(int i=0;i<num;i++){
		counts[i] = 0;
	}
	// 円形のフィルター
	for(y = 0;y < labels.h;y++){
		for(x = 0;x < labels.w;x++){
			if(pow(centers[labels(x,y)].x-x,2)+pow(centers[labels(x,y)].y-y,2) < sizes[labels(x,y)]){
				counts[labels(x,y)]++;
			}
		}
	}
	// サイズのフィルター
	for(int i=0;i<num;i++){
		// サイコロのサイズ指定ができる場所
		if(sizes[i]>counts[i] || sizes[i]<10 || sizes[i] > 2000){
			flags[i] = 0;
		}
	}
}

void LabelingCenter::outputCenter(){
	
	std::ofstream ofs;
	ofs.open("Centers.txt");
	for(int i=0;i<num;i++){
		if(flags[i])
			ofs <<	centers[i].x << " " 
				<<	centers[i].y << " " 
				<<	sizes[i]	 << " "
				<<	(int)flags[i]<< std::endl;
	}

}

cv::Point LabelingCenter::operator() (const int num){
	return centers[num];
}



}