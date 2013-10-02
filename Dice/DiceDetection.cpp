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
void DiceDetection::init(Image src){
	this->src.clone(src);
}


/******************
 *   必要要素の取得
 */
void DiceDetection::getAllPoints(){

	// 2値化
	Image bin;
	bin.grayeScale(src);
	bin.binarization(bin);

	// 点検出
	LabelingCenter lc;
	lc.init(bin);
	lc.setCenter(bin);
	
	ptNum=0;
	DotPoint dot;

	// 黒点
	// 小サイコロの点を抽出
	lc.circleFilter(1,2);
	lc.sizeFilter(20,100);
	for(int i=0;i<lc.num;i++){
		if(lc.flags[i]){
			dot.init(lc(i),lc.sizes[i]);
			this->allPoints.push_back(dot);
			this->ptTypes.push_back(DiceInfo::small);
			this->ptFlags.push_back(1);
			ptNum++;
		}
	}
	lc.filterReset();

	// 中サイコロ
	lc.circleFilter(1,2);
	lc.sizeFilter(100,250);
	for(int i=0;i<lc.num;i++){
		if(lc.flags[i]){
			dot.init(lc(i),lc.sizes[i]);
			this->allPoints.push_back(dot);
			this->ptTypes.push_back(DiceInfo::middle);
			this->ptFlags.push_back(1);
			ptNum++;
		}
	}
	lc.filterReset();

	// 大サイコロ
	lc.circleFilter(1,2);
	lc.sizeFilter(250,500);
	for(int i=0;i<lc.num;i++){
		if(lc.flags[i]){
			dot.init(lc(i),lc.sizes[i]);
			this->allPoints.push_back(dot);
			this->ptTypes.push_back(DiceInfo::large);
			this->ptFlags.push_back(1);
			ptNum++;
		}
	}
	lc.filterReset();

	// １の目大中サイコロ
	lc.circleFilter(1,2);
	lc.sizeFilter(500,2000);
	for(int i=0;i<lc.num;i++){
		if(lc.flags[i]){
			dot.init(lc(i),lc.sizes[i]);
			this->allPoints.push_back(dot);
			this->ptTypes.push_back(DiceInfo::none);
			this->ptFlags.push_back(1);
			ptNum++;
		}
	}
	lc.filterReset();
	
}

void DiceDetection::getAllLines(int maxRadius){
	maxLineRadius = maxRadius;
	LineSegment ls;
	lineNum = 0;
	for(int i=0;i<ptNum;i++){
		if(!ptFlags[i]) continue;
		for(int j=i+1;j<ptNum;j++){
			if(!ptFlags[j]) continue;
			if(Calc::getDistance(allPoints[i],allPoints[j]) < pow(maxRadius,2)){
				ls.init(allPoints[i],allPoints[j]);
				allLine.push_back(ls);
				lineFlags.push_back(1);
				lineNum++;
			}
		}
	}
}

/******************
 *   サイコロの目判定
 */
void DiceDetection::getDot1Points(){
	Image hue1,hue2,dst;
	
	// 赤の点抽出
	hue1.hsvColorExtraction(src,0,60,100,100);
	hue2.hsvColorExtraction(src,120,180,100,100);
	dst.bitwiseOr(hue1,hue2);

	// 重心特徴点抽出
	LabelingCenter lc;
	lc.init(dst);
	lc.setCenter(dst);
	lc.circleFilter(1,2);
	lc.sizeFilter(200,2000);

	Dot1Point dot1;

	// 1の目の点登録
	for(int i=0;i<lc.num;i++){
		if(lc.flags[i]){
			dot1.init(lc(i),lc.sizes[i]);
			dot1Points.push_back(dot1);
		}
	}

	// 点群から1の目の削除
	eraseDot1Points();

}

/******************
 *   サイコロの目厳選削除
 */

void DiceDetection::eraseDot1Points(){
	vector<int> dot1Num;
	// 点群から１の目削除
	for(int j=0;j<dot1Points.size();j++){
		for(int i=0;i<ptNum;i++){
			int radius = allPoints[i].size;
			if(radius<dot1Points[j].size) radius = dot1Points[j].size;
			if(pow(allPoints[i].pt.x - dot1Points[j].pt.x,2)+pow(allPoints[i].pt.y - dot1Points[j].pt.y,2) < radius){
				ptFlags[i] = 0;
				dot1Num.push_back(i);
				if(ptTypes[i] == DiceInfo::large){
					ptTypes[i] = DiceInfo::small;
					dot1Points[j].type = DiceInfo::small;
				}
				break;
			}
		}
	}

	// サイコロの大中判別
	for(int j=0;j<dot1Points.size();j++){
		if(dot1Points[j].type!=DiceInfo::none)
			continue;
		for(int i=0;i<ptNum;i++){
			//if(dot1Num[j]==i) continue;
			if(!ptFlags[i]) continue;
			if(pow(allPoints[i].pt.x - dot1Points[j].pt.x,2)+pow(allPoints[i].pt.y - dot1Points[j].pt.y,2) < pow(70,2)){
				dot1Points[j].type = DiceInfo::middle;
				ptTypes[dot1Num[j]] = DiceInfo::middle;
				break;
			}
		}
		if(dot1Points[j].type==DiceInfo::none){
			dot1Points[j].type = DiceInfo::large;
			ptTypes[dot1Num[j]] = DiceInfo::large;
		}
	}
}

/******************
 *   描写処理
 */

void DiceDetection::drawAllPoints(Image& img,cv::Scalar scal){
	for(int i=0;i<ptNum;i++){
		allPoints[i].draw(img,scal);
		//img.circle(points[i],(int)sqrt(sizes[i]/CV_PI),scal);
	}
}

void DiceDetection::drawTruePoints(Image& img,cv::Scalar scal){
	for(int i=0;i<ptNum;i++){
		if(ptFlags[i]){
			allPoints[i].draw(img,scal);
			//img.circle(points[i],(int)sqrt(sizes[i]/CV_PI),scal);
		}
	}
}

void DiceDetection::drawFalsePoints(Image& img,cv::Scalar scal){
	for(int i=0;i<ptNum;i++){
		if(!ptFlags[i])	
			allPoints[i].draw(img,scal);
			//img.circle(points[i],(int)sqrt(sizes[i]/CV_PI),scal);
	}
}

void DiceDetection::drawAllLine(Image& img,cv::Scalar dot_col,cv::Scalar line_col,int thickness){
	for(int i=0;i<lineNum;i++){
		allLine[i].draw(img,dot_col,line_col,thickness);
	}
}

void DiceDetection::drawTrueLine(Image& img,cv::Scalar dot_col,cv::Scalar line_col,int thickness){
	for(int i=0;i<lineNum;i++){
		if(lineFlags[i])
			allLine[i].draw(img,dot_col,line_col,thickness);
	}
}

void DiceDetection::drawFalseLine(Image& img,cv::Scalar dot_col,cv::Scalar line_col,int thickness){
	for(int i=0;i<lineNum;i++){
		if(!lineFlags[i])
			allLine[i].draw(img,dot_col,line_col,thickness);
	}
}

void DiceDetection::drawDot1Points(Image& img,cv::Scalar scal){
	for(int i=0;i<dot1Points.size();i++){	
		//img.circle(dot1Points[i].pt,(int)sqrt(dot1Points[i].size/CV_PI),scal);
		//if(dot1Points[i].type == DiceInfo::large)
			dot1Points[i].draw(img,scal);
	}
}




}