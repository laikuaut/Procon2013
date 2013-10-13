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
void DiceDetection::init(){
	this->iniFileName = "DiceDetection.ini";
	readIniFile();
	src.path = dir;
	src.load(name);
	src.resize(src,cv::Size(1920,1080));

	// イベント系
	mode.init(cv::Point(0,0),0,DiceInfo::large,1);
	modeFlag = 2;
	centerNum = -1;

	run();

}

void DiceDetection::init(Dir dir,string name){
	this->iniFileName = "DiceDetection.ini";
	readIniFile();
	this->dir = dir;
	src.path = dir;
	src.load(name);
	src.resize(src,cv::Size(1920,1080));

	// イベント系
	mode.init(cv::Point(0,0),0,DiceInfo::large,1);
	modeFlag = 2;
	centerNum = -1;

	run();

}

/******************
 *   クラスDotPoints
 */

DiceDetection::DotPoints::DotPoints(){
	num=0;
}

void DiceDetection::DotPoints::add(DotPoint dot,short flag,DiceInfo::dtype type,int kind){
	points.push_back(dot);
	flags.push_back(flag);
	types.push_back(type);
	kinds.push_back(kind);
	num++;
}

int DiceDetection::DotPoints::size() const{
	return num;
}

void DiceDetection::DotPoints::setKind(int kind,int number){
	kinds[number] = kind;
	if(kind)
		flags[number] = 0;
	else
		flags[number] = 1;
}

void DiceDetection::DotPoints::clear(){
	points.clear();
	flags.clear();
	types.clear();
	kinds.clear();
	num=0;
}

DotPoint DiceDetection::DotPoints::operator[] (int i) const{
	return points[i];
}

/******************
 *   クラスLineSegments
 */

DiceDetection::LineSegments::LineSegments(){
	num=0;
}

void DiceDetection::LineSegments::add(LineSegment lseg,short flag,DiceInfo::dtype type,int kind,int dotNum1,int dotNum2){
	lines.push_back(lseg);
	flags.push_back(flag);
	types.push_back(type);
	kinds.push_back(kind);
	dotNums[0].push_back(dotNum1);
	dotNums[1].push_back(dotNum2);
	num++;
}

int DiceDetection::LineSegments::size() const{
	return num;
}

void DiceDetection::LineSegments::clear(){
	lines.clear();
	flags.clear();
	types.clear();
	kinds.clear();
	dotNums[0].clear();
	dotNums[1].clear();
	num=0;
}

LineSegment DiceDetection::LineSegments::operator[](int i) const{
	return lines[i];
}

/******************
 *   クラスAllDot3Points
 */

DiceDetection::AllDot3Points::AllDot3Points(){
	num = 0;
}

void DiceDetection::AllDot3Points::add(Dot3Point dot3,short flag,DiceInfo::dtype type,int kind,int dotNum1,int dotNum2,int dotNum3){
	dot3s.push_back(dot3);
	flags.push_back(flag);
	types.push_back(type);
	kinds.push_back(kind);
	dotNums[0].push_back(dotNum1);
	dotNums[1].push_back(dotNum2);
	dotNums[2].push_back(dotNum3);
	num++;
}

int DiceDetection::AllDot3Points::size() const{
	return num;
}

void DiceDetection::AllDot3Points::clear(){
	dot3s.clear();
	flags.clear();
	types.clear();
	kinds.clear();
	dotNums[0].clear();
	dotNums[1].clear();
	dotNums[2].clear();
	num=0;
}

Dot3Point DiceDetection::AllDot3Points::operator[](int i){
	return dot3s[i];
}

/******************
 *   クラスDotCenters
 */

DiceDetection::DotCenters::DotCenters(){
	num = 0;
}

void DiceDetection::DotCenters::clear(){
	centers.clear();
	types.clear();
	kinds.clear();
	numbers.clear();
	num=0;
}

void DiceDetection::DotCenters::add(DotPoint center,DiceInfo::dtype type,int kind,int number){
	centers.push_back(center);
	types.push_back(type);
	kinds.push_back(kind);
	numbers.push_back(number);
	num++;
}

int DiceDetection::DotCenters::size() const{
	return num;
}

DotPoint DiceDetection::DotCenters::operator[](int i){
	return centers[i];
}

/******************
 *   クラスDot1Points
 */

DiceDetection::Dot1Points::Dot1Points(){
	num=0;
}

void DiceDetection::Dot1Points::clear(){
	dot1s.clear();
	pointNums.clear();
	num=0;
}

void DiceDetection::Dot1Points::erase(int i){
	vector<Dot1Point>::iterator it = dot1s.begin();
	dot1s.erase(it+i);
	vector<int>::iterator int_it = pointNums.begin();
	pointNums.erase(int_it+i);
	num--;
}

void DiceDetection::Dot1Points::add(Dot1Point dot1,int number){
	dot1s.push_back(dot1);
	pointNums.push_back(number);
	num++;
}

void DiceDetection::Dot1Points::add(DotPoint center,DiceInfo::dtype type){
	Dot1Point dot1;
	int radius,size;
	if(type == DiceInfo::small){
		size = smallSize;
	}else if(type == DiceInfo::middle){
		size = middleSize;
	}else if(type == DiceInfo::large){
		size = largeSize;
	}else{
		size = 0;
		radius = 0;
	}
	DotPoint dot;
	dot.init(center,size);
	dot1.init(dot,type);
	dot1s.push_back(dot1);
	pointNums.push_back(-1);
	num++;
}

int DiceDetection::Dot1Points::size() const{
	return num;
}

Dot1Point DiceDetection::Dot1Points::operator[](int i){
	return dot1s[i];
}

/******************
 *   クラスDot2Points
 */

DiceDetection::Dot2Points::Dot2Points(){
	num=0;
}

void DiceDetection::Dot2Points::clear(){
	dot2s.clear();
	for(int i=0;i<2;i++){
		pointNums[i].clear();
	}
	num=0;
}

void DiceDetection::Dot2Points::erase(int i){
	vector<Dot2Point>::iterator it = dot2s.begin();
	dot2s.erase(it+i);
	for(int j=0;j<2;j++){
		vector<int>::iterator int_it = pointNums[j].begin();
		pointNums[j].erase(int_it+i);
	}
	num--;
}

void DiceDetection::Dot2Points::add(Dot2Point dot2,int number1
									,int number2){
	dot2s.push_back(dot2);
	pointNums[0].push_back(number1);
	pointNums[1].push_back(number2);
	num++;
}

void DiceDetection::Dot2Points::add(DotPoint center,DiceInfo::dtype type){
	Dot2Point dot2;
	DotPoint dots[2];
	int radius,size;
	if(type == DiceInfo::small){
		size = smallSize;
		radius = smallRadius;
	}else if(type == DiceInfo::middle){
		size = middleSize;
		radius = middleRadius;
	}else if(type == DiceInfo::large){
		size = largeSize;
		radius = largeRadius;
	}else{
		size = 0;
		radius = 0;
	}
	dots[0].init(cv::Point2f(center.pt.x + radius,center.pt.y + radius),size);
	dots[1].init(cv::Point2f(center.pt.x - radius,center.pt.y - radius),size);
	dot2.init(dots,type);
	dot2s.push_back(dot2);
	for(int i=0;i<2;i++){
		pointNums[i].push_back(-1);
	}
	num++;
}

int DiceDetection::Dot2Points::size() const{
	return num;
}

Dot2Point DiceDetection::Dot2Points::operator[](int i){
	return dot2s[i];
}

/******************
 *   クラスDot3Points
 */

DiceDetection::Dot3Points::Dot3Points(){
	num=0;
}

void DiceDetection::Dot3Points::clear(){
	dot3s.clear();
	for(int i=0;i<3;i++){
		pointNums[i].clear();
	}
	num=0;
}

void DiceDetection::Dot3Points::erase(int i){
	vector<Dot3Point>::iterator it = dot3s.begin();
	dot3s.erase(it+i);
	for(int j=0;j<3;j++){
		vector<int>::iterator int_it = pointNums[j].begin();
		pointNums[j].erase(int_it+i);
	}
	num--;
}

void DiceDetection::Dot3Points::add(Dot3Point dot3,int number1
									,int number2
									,int number3){
	dot3s.push_back(dot3);
	pointNums[0].push_back(number1);
	pointNums[1].push_back(number2);
	pointNums[2].push_back(number3);
	num++;
}

void DiceDetection::Dot3Points::add(DotPoint center,DiceInfo::dtype type){
	Dot3Point dot3;
	DotPoint dots[3];
	LineSegment lsegs[2];
	int radius,size;
	if(type == DiceInfo::small){
		size = smallSize;
		radius = smallRadius;
	}else if(type == DiceInfo::middle){
		size = middleSize;
		radius = middleRadius;
	}else if(type == DiceInfo::large){
		size = largeSize;
		radius = largeRadius;
	}else{
		size = 0;
		radius = 0;
	}
	dots[0].init(center,size);
	dots[1].init(cv::Point2f(center.pt.x + radius,center.pt.y + radius),size);
	dots[2].init(cv::Point2f(center.pt.x - radius,center.pt.y - radius),size);
	lsegs[0].init(dots[0],dots[1]);
	lsegs[1].init(dots[0],dots[2]);
	dot3.init(lsegs[0],lsegs[1],type);
	dot3s.push_back(dot3);
	for(int i=0;i<3;i++){
		pointNums[i].push_back(-1);
	}
	num++;
}

int DiceDetection::Dot3Points::size() const{
	return num;
}

Dot3Point DiceDetection::Dot3Points::operator[](int i){
	return dot3s[i];
}

/******************
 *   クラスDot4Points
 */

DiceDetection::Dot4Points::Dot4Points(){
	num=0;
}

void DiceDetection::Dot4Points::clear(){
	dot4s.clear();
	for(int i=0;i<4;i++){
		pointNums[i].clear();
	}
	num=0;
}

void DiceDetection::Dot4Points::erase(int i){
	vector<Dot4Point>::iterator it = dot4s.begin();
	dot4s.erase(it+i);
	for(int j=0;j<4;j++){
		vector<int>::iterator int_it = pointNums[j].begin();
		pointNums[j].erase(int_it+i);
	}
	num--;
}

void DiceDetection::Dot4Points::add(Dot4Point dot4,int number1
									,int number2
									,int number3
									,int number4){
	dot4s.push_back(dot4);
	pointNums[0].push_back(number1);
	pointNums[1].push_back(number2);
	pointNums[2].push_back(number3);
	pointNums[3].push_back(number4);
	num++;
}

void DiceDetection::Dot4Points::add(DotPoint center,DiceInfo::dtype type){
	Dot4Point dot4;
	DotPoint dots[4];
	LineSegment lsegs[2];
	int radius,size;
	if(type == DiceInfo::small){
		size = smallSize;
		radius = smallRadius;
	}else if(type == DiceInfo::middle){
		size = middleSize;
		radius = middleRadius;
	}else if(type == DiceInfo::large){
		size = largeSize;
		radius = largeRadius;
	}else{
		size = 0;
		radius = 0;
	}
	center.init(center,size);
	dots[0].init(cv::Point2f(center.pt.x + radius,center.pt.y + radius),size);
	dots[1].init(cv::Point2f(center.pt.x - radius,center.pt.y - radius),size);
	dots[2].init(cv::Point2f(center.pt.x + radius,center.pt.y - radius),size);
	dots[3].init(cv::Point2f(center.pt.x - radius,center.pt.y + radius),size);
	lsegs[0].init(dots[0],dots[1]);
	lsegs[1].init(dots[2],dots[3]);
	dot4.init(lsegs[0],lsegs[1],center,type);
	dot4s.push_back(dot4);
	for(int i=0;i<4;i++){
		pointNums[i].push_back(-1);
	}
	num++;
}

int DiceDetection::Dot4Points::size() const{
	return num;
}

Dot4Point DiceDetection::Dot4Points::operator[](int i){
	return dot4s[i];
}

/******************
 *   クラスDot5Points
 */

DiceDetection::Dot5Points::Dot5Points(){
	num=0;
}

void DiceDetection::Dot5Points::clear(){
	dot5s.clear();
	for(int i=0;i<5;i++){
		pointNums[i].clear();
	}
	num=0;
}

void DiceDetection::Dot5Points::erase(int i){
	vector<Dot5Point>::iterator it = dot5s.begin();
	dot5s.erase(it+i);
	for(int j=0;j<5;j++){
		vector<int>::iterator int_it = pointNums[j].begin();
		pointNums[j].erase(int_it+i);
	}
	num--;
}

void DiceDetection::Dot5Points::add(Dot5Point dot5,int number1
									,int number2
									,int number3
									,int number4
									,int number5){
	dot5s.push_back(dot5);
	pointNums[0].push_back(number1);
	pointNums[1].push_back(number2);
	pointNums[2].push_back(number3);
	pointNums[3].push_back(number4);
	pointNums[4].push_back(number5);
	num++;
}


void DiceDetection::Dot5Points::add(DotPoint center,DiceInfo::dtype type){
	Dot5Point dot5;
	DotPoint dots[5];
	LineSegment lsegs[4];
	Dot3Point dot3s[2];
	int radius,size;
	if(type == DiceInfo::small){
		size = smallSize;
		radius = smallRadius;
	}else if(type == DiceInfo::middle){
		size = middleSize;
		radius = middleRadius;
	}else if(type == DiceInfo::large){
		size = largeSize;
		radius = largeRadius;
	}else{
		size = 0;
		radius = 0;
	}
	dots[0].init(cv::Point2f(center.pt.x + radius,center.pt.y + radius),size);
	dots[1].init(cv::Point2f(center.pt.x - radius,center.pt.y - radius),size);
	dots[2].init(cv::Point2f(center.pt.x + radius,center.pt.y - radius),size);
	dots[3].init(cv::Point2f(center.pt.x - radius,center.pt.y + radius),size);
	dots[4].init(center,size);
	lsegs[0].init(dots[4],dots[0]);
	lsegs[1].init(dots[4],dots[1]);
	lsegs[2].init(dots[4],dots[2]);
	lsegs[3].init(dots[4],dots[3]);
	dot3s[0].init(lsegs[0],lsegs[1],type);
	dot3s[1].init(lsegs[2],lsegs[3],type);
	dot5.init(dot3s[0],dot3s[1],type);
	dot5s.push_back(dot5);
	for(int i=0;i<5;i++){
		pointNums[i].push_back(-1);
	}
	num++;
}

int DiceDetection::Dot5Points::size() const{
	return num;
}

Dot5Point DiceDetection::Dot5Points::operator[](int i){
	return dot5s[i];
}


/******************
 *   クラスDot6Points
 */

DiceDetection::Dot6Points::Dot6Points(){
	num=0;
}

void DiceDetection::Dot6Points::clear(){
	dot6s.clear();
	for(int i=0;i<6;i++){
		pointNums[i].clear();
	}
	num=0;
}

void DiceDetection::Dot6Points::erase(int i){
	vector<Dot6Point>::iterator it = dot6s.begin();
	dot6s.erase(it+i);
	for(int j=0;j<6;j++){
		vector<int>::iterator int_it = pointNums[j].begin();
		pointNums[j].erase(int_it+i);
	}
	num--;
}

void DiceDetection::Dot6Points::add(Dot6Point dot6,int number1
									,int number2
									,int number3
									,int number4
									,int number5
									,int number6){
	dot6s.push_back(dot6);
	pointNums[0].push_back(number1);
	pointNums[1].push_back(number2);
	pointNums[2].push_back(number3);
	pointNums[3].push_back(number4);
	pointNums[4].push_back(number5);
	pointNums[5].push_back(number6);
	num++;
}


void DiceDetection::Dot6Points::add(DotPoint center,DiceInfo::dtype type){
	Dot6Point dot6;
	DotPoint dots[6];
	LineSegment lsegs[4];
	Dot3Point dot3s[2];
	int radius,size;
	if(type == DiceInfo::small){
		size = smallSize;
		radius = smallRadius;
	}else if(type == DiceInfo::middle){
		size = middleSize;
		radius = middleRadius;
	}else if(type == DiceInfo::large){
		size = largeSize;
		radius = largeRadius;
	}else{
		size = 0;
		radius = 0;
	}
	dots[0].init(cv::Point2f(center.pt.x + radius/3,center.pt.y),size);
	dots[1].init(cv::Point2f(center.pt.x - radius/3,center.pt.y),size);
	dots[2].init(cv::Point2f(center.pt.x + radius/3,center.pt.y + radius/2),size);
	dots[3].init(cv::Point2f(center.pt.x - radius/3,center.pt.y + radius/2),size);
	dots[4].init(cv::Point2f(center.pt.x + radius/3,center.pt.y - radius/2),size);
	dots[5].init(cv::Point2f(center.pt.x - radius/3,center.pt.y - radius/2),size);
	lsegs[0].init(dots[0],dots[2]);
	lsegs[1].init(dots[0],dots[4]);
	lsegs[2].init(dots[1],dots[3]);
	lsegs[3].init(dots[1],dots[5]);
	dot3s[0].init(lsegs[0],lsegs[1],type);
	dot3s[1].init(lsegs[2],lsegs[3],type);
	dot6.init(dot3s[0],dot3s[1],type);
	dot6s.push_back(dot6);
	for(int i=0;i<6;i++){
		pointNums[i].push_back(-1);
	}
	num++;
}

int DiceDetection::Dot6Points::size() const{
	return num;
}

Dot6Point DiceDetection::Dot6Points::operator[](int i){
	return dot6s[i];
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
	//
	//Image draw;
	//draw.clone(src);
	//lc.circleFilter(dotCircleFilterPer,2);
	//lc.sizeFilter(dotNoneMinSize,3000);
	//// 円表示
	//for(int i=0;i<lc.num;i++){
	//	if(lc.flags[i]){
	//		draw.circle(lc(i),(int)sqrt(lc.sizes[i]/CV_PI),cv::Scalar(255,0,0));
	//		//cout << "OK:" << labelCenter.sizes[i] << endl;
	//	}else{
	//		if(lc.sizes[i]<2000)
	//			draw.circle(lc(i),(int)sqrt(lc.sizes[i]/CV_PI),cv::Scalar(0,255,0));
	//		//cout << "NG:" << labelCenter.sizes[i] << endl;
	//	}
	//}
	//draw.imshow("test");

	DotPoint dot;

	// 黒点
	// 小サイコロの点を抽出
	lc.circleFilter(dotCircleFilterPer,dotCircleFilterRadiusPer);
	lc.sizeFilter(dotSmallMinSize,dotSmallMaxSize);
	for(int i=0;i<lc.num;i++){
		if(lc.flags[i]){
			dot.init(lc(i),lc.sizes[i]);
			allPoints.add(dot,1,DiceInfo::small,0);
		}
	}
	lc.filterReset();

	// 中サイコロ
	lc.circleFilter(dotCircleFilterPer,dotCircleFilterRadiusPer);
	lc.sizeFilter(dotMiddleMinSize,dotMiddleMaxSize);
	for(int i=0;i<lc.num;i++){
		if(lc.flags[i]){
			dot.init(lc(i),lc.sizes[i]);
			allPoints.add(dot,1,DiceInfo::middle,0);
		}
	}
	lc.filterReset();

	// 大サイコロ
	lc.circleFilter(dotCircleFilterPer,dotCircleFilterRadiusPer);
	lc.sizeFilter(dotLargeMinSize,dotLargeMaxSize);
	for(int i=0;i<lc.num;i++){
		if(lc.flags[i]){
			dot.init(lc(i),lc.sizes[i]);
			allPoints.add(dot,1,DiceInfo::large,0);
		}
	}
	lc.filterReset();

	// １の目大中サイコロ
	lc.circleFilter(dotCircleFilterPer,dotCircleFilterRadiusPer);
	lc.sizeFilter(dotNoneMinSize,dotNoneMaxSize);
	for(int i=0;i<lc.num;i++){
		if(lc.flags[i]){
			dot.init(lc(i),lc.sizes[i]);
			allPoints.add(dot,1,DiceInfo::none,0);
		}
	}
	lc.filterReset();
	
}

void DiceDetection::getAllLines(){
	LineSegment ls;
	double radius;

	// 独立した点の削除用
	vector<short> flags;
	for(int i=0;i<allPoints.size();i++){
		flags.push_back(allPoints.flags[i]);
	}

	for(int i=0;i<allPoints.size();i++){
		if(!allPoints.flags[i]) continue;
		
		// サイコロのサイズごとに半径変更 
		if(allPoints.types[i]== DiceInfo::small)
			radius = lineSmallRadius;
		else if(allPoints.types[i] == DiceInfo::middle)
			radius = lineMiddleRadius;
		else if(allPoints.types[i] == DiceInfo::large)
			radius = lineLargeRadius;

		// 線分検出
		for(int j=0;j<allPoints.size();j++){
			if(i==j) continue;
			if(allPoints.types[i] != allPoints.types[j]) continue;
			if(!allPoints.flags[j]) continue;
			if(Calc::getDistance2(allPoints[i],allPoints[j]) < pow(radius,2)){
				ls.init(allPoints[i],allPoints[j]);
				allLines.add(ls,1,allPoints.types[i],0,i,j);
				flags[i] = flags[j] = 0; // 独立していない点
			}
		}
	}

	// 独立した点の削除
	for(int i=0;i<allPoints.size();i++){
		if(flags[i]){

			// 最終処理保険
			if(allPoints.types[i] == DiceInfo::large) continue;

				allPoints.flags[i] = 0;
				allPoints.types[i] = DiceInfo::none;
		}
	}

}

void DiceDetection::getAllDot3Points(){
	int minDistance,maxDistance,distance;
	Dot3Point dot3;

	// 線分の撮り直し
	clearAllLines();
	getAllLines();
	
	for(int i=0;i<allLines.size();i++){
		if(allLines.types[i] == DiceInfo::small){
			minDistance = allDot3SmallMinDistance;
			maxDistance = allDot3SmallMaxDistance;
		}else if(allLines.types[i] == DiceInfo::middle){
			minDistance = allDot3MiddleMinDistance;
			maxDistance = allDot3MiddleMaxDistance;
		}else if(allLines.types[i] == DiceInfo::large){
			minDistance = allDot3LargeMinDistance;
			maxDistance = allDot3LargeMaxDistance;
		}

		if(pow(minDistance,2) < pow(allLines[i].distance,2) && pow(allLines[i].distance,2) < pow(maxDistance,2)){
			allLines.flags[i] = 1;
//			dot2Nums.push_back(allLines.dotNums[0][i]);
//			dot2Nums.push_back(allLines.dotNums[1][i]);
		}else{
			allLines.flags[i] = 0;
		}
	}

	// allDot3Points抽出


	for(int i=0;i<allLines.size();i++){
		if(!allLines.flags[i]) continue;
		for(int j=0;j<allLines.size();j++){
			if(i==j) continue;
			if(!allLines.flags[j]) continue;
			if(allLines.types[i] != allLines.types[j]) continue;
			//if(Calc::getDistance2(dot2Points.dot2s[i].dot[0],dot2Points.dot2s[j].dot[0]) < dot2Points.dot2s[j].dot[0].size/CV_PI){
			if(Calc::getDistance2(allLines[i].dot[0],allLines[j].dot[0]) < allLines[j].dot[0].size/CV_PI){
			//	&& Calc::getDistance2(allLines[i].dot[1],allLines[j].dot[1]) > allLines[i].dot[1].size/CV_PI){
				dot3.init(allLines[i],allLines[j],allLines.types[i]);
				if(dot3.formedAngle > allDot3Angle){
					allDot3Points.add(dot3,1,dot3.type,0,allLines.dotNums[0][i],allLines.dotNums[1][i],allLines.dotNums[1][j]);
					allLines.flags[i]=0;
					allLines.flags[j]=0;
				}
			}	
		}
	}

}

void DiceDetection::getAllDotCenters(){

	clearAllDotCenters();

	for(int i=0;i<dot1Points.size();i++)
		allDotCenters.add(dot1Points.dot1s[i],dot1Points.dot1s[i].type,1,i);
	for(int i=0;i<dot2Points.size();i++)
		allDotCenters.add(dot2Points.dot2s[i].center,dot2Points.dot2s[i].type,2,i);
	for(int i=0;i<dot3Points.size();i++)
		allDotCenters.add(dot3Points.dot3s[i].center,dot3Points.dot3s[i].type,3,i);
	for(int i=0;i<dot4Points.size();i++)
		allDotCenters.add(dot4Points.dot4s[i].center,dot4Points.dot4s[i].type,4,i);
	for(int i=0;i<dot5Points.size();i++)
		allDotCenters.add(dot5Points.dot5s[i].center,dot5Points.dot5s[i].type,5,i);
	for(int i=0;i<dot6Points.size();i++)
		allDotCenters.add(dot6Points.dot6s[i].center,dot6Points.dot6s[i].type,6,i);	
	
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

	//dst.imshow("hsv");

	// 重心特徴点抽出
	LabelingCenter lc;
	lc.init(dst);
	lc.setCenter(dst);
	lc.circleFilter(dot1CircleFilterPer,dot1CircleFilterRadiusPer);
	lc.sizeFilter(dot1MinSize,dot1MaxSize);


	//Image draw;
	//draw.clone(src);
	////lc.circleFilter(dotCircleFilterPer,2);
	////lc.sizeFilter(dotNoneMinSize,3000);
	//// 円表示
	//for(int i=0;i<lc.num;i++){
	//	if(lc.flags[i]){
	//		draw.circle(lc(i),(int)sqrt(lc.sizes[i]/CV_PI),cv::Scalar(255,0,0));
	//		//cout << "OK:" << labelCenter.sizes[i] << endl;
	//	}else{
	//		if(lc.sizes[i]<2000)
	//			draw.circle(lc(i),(int)sqrt(lc.sizes[i]/CV_PI),cv::Scalar(0,255,0));
	//		//cout << "NG:" << labelCenter.sizes[i] << endl;
	//	}
	//}
	//draw.imshow("test");

	//	Image draw;
	//draw.clone(src);
	//drawTypePoints(draw,DiceInfo::none,cv::Scalar(255,0,0));
	//drawTypePoints(draw,DiceInfo::small,cv::Scalar(0,255,0));
	//drawTypePoints(draw,DiceInfo::middle,cv::Scalar(255,255,0));
	//drawTypePoints(draw,DiceInfo::large,cv::Scalar(255,0,255));
	//draw.imshow("test");
	//cv::waitKey(0);

	Dot1Point dot1;
	vector<int> dot1Num;

	// 1の目の点登録
	for(int i=0;i<lc.num;i++){
		if(!lc.flags[i]) continue;
		for(int j=0;j<allPoints.size();j++){
			if(Calc::getDistance2(allPoints[j],lc(i)) < allPoints[j].size/CV_PI){
				dot1.init(lc(i),lc.sizes[i]);
				dot1Points.add(dot1,j);
				allPoints.setKind(1,j);
			}
		}
	}

	// 点群から1の目の削除
	for(int j=0;j<dot1Points.size();j++){
		if(allPoints.types[dot1Points.pointNums[j]] == DiceInfo::large || 
			allPoints.types[dot1Points.pointNums[j]] == DiceInfo::middle){
			allPoints.types[dot1Points.pointNums[j]] = DiceInfo::small;
			dot1Points.dot1s[j].type = DiceInfo::small;
		}
	}


	// サイコロの大中判別
	for(int j=0;j<dot1Points.size();j++){
		if(dot1Points.dot1s[j].type!=DiceInfo::none)	continue;
		//else if(flag) continue;
		for(int i=0;i<allPoints.size();i++){
			//if(!allPoints.flags[i]) continue;
			if(i==dot1Points.pointNums[j]) continue;

			if(Calc::getDistance2(allPoints[i],dot1Points.dot1s[j]) < pow(dot1LMDetectRadius,2)){
				if(allPoints.types[i] == DiceInfo::middle || allPoints.kinds[i]==1){
					dot1Points.dot1s[j].type = DiceInfo::middle;
					allPoints.types[dot1Points.pointNums[j]] = DiceInfo::middle;
					break;
				}
			}
		}
		if(dot1Points.dot1s[j].type==DiceInfo::none){
			dot1Points.dot1s[j].type = DiceInfo::large;
			allPoints.types[dot1Points.pointNums[j]] = DiceInfo::large;
		}
	}

	// 確認
	//Image draw;
	//draw.clone(src);
	//drawTypePoints(draw,DiceInfo::none,cv::Scalar(255,0,0));
	//drawTypePoints(draw,DiceInfo::small,cv::Scalar(0,255,0));
	//drawTypePoints(draw,DiceInfo::middle,cv::Scalar(255,255,0));
	//drawTypePoints(draw,DiceInfo::large,cv::Scalar(255,0,255));
	//draw.imshow("test");
	//cv::waitKey(0);


	// さらに大サイコロと誤認した中サイコロの修正
	for(int i=0;i<dot1Points.size();i++){
		if(dot1Points.dot1s[i].type != DiceInfo::large) continue;
		for(int j=0;j<dot1Points.size();j++){
			if(dot1Points.dot1s[j].type == DiceInfo::middle){
				if(Calc::getDistance2(dot1Points.dot1s[i],dot1Points.dot1s[j])<pow(dot1LMCorrectRadius,2)){
					dot1Points.dot1s[i].type = DiceInfo::middle;
					allPoints.types[dot1Points.pointNums[i]] = DiceInfo::middle;
					break;
				}
			}
		}
	}
}

void DiceDetection::getDot2Points(){

	int minDistance,maxDistance,distance;
	Dot2Point dot2;
	vector<int> dot2Nums;

	// 2の目の点を含まない線分を抽出
	for(int i=0;i<allLines.size();i++){
		if(allLines.types[i] == DiceInfo::small){
			minDistance = dot2SmallMinDistance;
			maxDistance = dot2SmallMaxDistance;
		}else if(allLines.types[i] == DiceInfo::middle){
			minDistance = dot2MiddleMinDistance;
			maxDistance = dot2MiddleMaxDistance;
		}else if(allLines.types[i] == DiceInfo::large){
			minDistance = dot2LargeMinDistance;
			maxDistance = dot2LargeMaxDistance;
		}

		if(pow(minDistance,2) < pow(allLines[i].distance,2) && pow(allLines[i].distance,2) < pow(maxDistance,2)){
			allLines.flags[i] = 1;
			dot2Nums.push_back(allLines.dotNums[0][i]);
			dot2Nums.push_back(allLines.dotNums[1][i]);
		}else{
			allLines.flags[i] = 0;
		}
	}

	//Image draw;
	//draw.clone(src);
	//cv::namedWindow("test",0);
	//drawTrueLine(draw,cv::Scalar(0,0,255),cv::Scalar(0,255,0));
	//draw.imshow("test");
	//cv::waitKey(0);

	// 2の目の点を抽出
	vector<Dot1Point> dot1s;
	Dot1Point dot1;
	vector<int> dot1Nums;
	for(int i=0;i<allPoints.size();i++){
		if(allPoints.flags[i]){
			bool flag = true;
			for(int j=0;j<dot2Nums.size();j++){
				if(i==dot2Nums[j]){
					flag = false;
					break;
				}
			}
			if(flag){
				dot1.init(allPoints[i],allPoints.types[i]);
				dot1s.push_back(dot1);
				dot1Nums.push_back(i);
			}
		}
	}

	//Image draw;
	//draw.clone(src);
	//cv::namedWindow("test",0);
	//for(int i=0;i<dot1s.size();i++){
	//		dot1s[i].draw(draw,cv::Scalar(255,0,0));
	//}
	//draw.imshow("test");
	//cv::waitKey(0);



	// 2の目を決定
	vector<int> dot2sNum[2];
	for(int i=0;i<dot2Points.size();i++){
		dot2sNum[0].push_back(-1);
		dot2sNum[1].push_back(-1);
	}
	
	for(int i=0;i<dot1s.size();i++){

		// 距離指定
		if(dot1s[i].type == DiceInfo::small){
			distance = dot2SmallDistance;
		}else if(dot1s[i].type == DiceInfo::middle){
			distance = dot2MiddleDistance;
		}else if(dot1s[i].type == DiceInfo::large){
			distance = dot2LargeDistance;
		}

		for(int j=i+1;j<dot1s.size();j++){
			//if(i==j) continue;
			if(dot1s[i].type != dot1s[j].type) continue;
			if(Calc::getDistance2(dot1s[i],dot1s[j]) < pow(distance,2) ){
				// 角度フィルター
				//double tan = abs(dot1s[i].pt.y - dot1s[j].pt.y)/abs(dot1s[i].pt.x - dot1s[j].pt.x);
				//double sita = atan(tan)*180/CV_PI;
				double sita = Calc::getAngle(dot1s[i],dot1s[j]);
				if(sita>dot2MinAngle && sita<dot2MaxAngle){
					dot2.init(dot1s[i],dot1s[j],dot1s[i].type);
					
					// 削除
					bool flag=true;
					for(int k=0;k<dot2Points.size();k++){
						if(Calc::getDistance2(dot2.center,dot2Points.dot2s[k].center) < dot2.center.size){
							eraseDot2Points(k);
							//vector<Dot2Point>::iterator it = dot2Points.begin();
							//for(it = dot2Points.begin(); it != dot2Points.end(); ++it){
							//	it = dot2Points.erase(it);
							//	break;
							//}
							//if(dot2sNum[0][k]==-1) continue;
							//if(dot2sNum[1][k]==-1) continue;
							//allPoints.flags[dot1Nums[dot2sNum[0][k]]] = 1;
							//allPoints.kinds[dot1Nums[dot2sNum[0][k]]] = 0;
							//allPoints.flags[dot1Nums[dot2sNum[1][k]]] = 1;
							//allPoints.kinds[dot1Nums[dot2sNum[1][k]]] = 0;
							//for(int l=0;l<2;l++){
							//	vector<int>::iterator int_it = dot2sNum[l].begin();
							//	for(int_it = dot2sNum[l].begin(); int_it != dot2sNum[l].end(); ++int_it){
							//		int_it = dot2sNum[l].erase(int_it);
							//		break;
							//	}
							//}
							flag = false;
							break;
						}
					}

					// 追加
					if(flag){
						dot2Points.add(dot2,dot1Nums[i],dot1Nums[j]);
						dot2sNum[0].push_back(i);
						dot2sNum[1].push_back(j);
						allPoints.setKind(2,dot1Nums[i]);
						allPoints.setKind(2,dot1Nums[j]);
						break;
					}
				}
			}
		}
	}
}

void DiceDetection::getDot4Points(){

	int minDistance,maxDistance,distance;
	vector<int> dot4Nums;

	// ４の目を含まない点を抽出
	for(int i=0;i<allLines.size();i++){
		if(allLines.types[i] == DiceInfo::small){
			minDistance = dot4SmallMinDistance;
			maxDistance = dot4SmallMaxDistance;
		}else if(allLines.types[i] == DiceInfo::middle){
			minDistance = dot4MiddleMinDistance;
			maxDistance = dot4MiddleMaxDistance;
		}else if(allLines.types[i] == DiceInfo::large){
			minDistance = dot4LargeMinDistance;
			maxDistance = dot4LargeMaxDistance;
		}

		if(pow(minDistance,2) < pow(allLines[i].distance,2) && pow(allLines[i].distance,2) < pow(maxDistance,2)){
			allLines.flags[i] = 1;
			dot4Nums.push_back(allLines.dotNums[0][i]);
			dot4Nums.push_back(allLines.dotNums[1][i]);
		}else{
			allLines.flags[i] = 0;
		}
	}

	// 4の目の点を抽出(2の目と同じ処理)
	DotPoints dots;
	Dot1Point dot1;
	vector<int> dot1Nums;
	for(int i=0;i<allPoints.size();i++){
		if(allPoints.flags[i]){
			bool flag = true;
			for(int j=0;j<dot4Nums.size();j++){
				if(i==dot4Nums[j]){
					flag = false;
					break;
				}
			}
			if(flag){
				dot1.init(allPoints[i],allPoints.types[i]);
				dots.add(dot1,1,dot1.type,0);
				dot1Nums.push_back(i);
			}
		}
	}

	// 4の目の点から2の目のアルゴリズム適応
	Dot2Point dot2;
	LineSegments lsegs;
	for(int i=0;i<dots.size();i++){
		if(!dots.flags[i]) continue;

		// 距離指定
		if(dots.types[i] == DiceInfo::small){
			distance = dot4SmallDistance;
		}else if(dots.types[i] == DiceInfo::middle){
			distance = dot4MiddleDistance;
		}else if(dots.types[i] == DiceInfo::large){
			distance = dot4LargeDistance;
		}

		for(int j=0;j<dots.size();j++){
			if(i==j) continue;
			if(dots.types[i] != dots.types[j]) continue;
			if(!dots.flags[j]) continue;
			if(Calc::getDistance2(dots[i],dots[j]) < pow(distance,2) ){
				// 角度フィルター
				//double tan = abs(dot1s[i].pt.y - dot1s[j].pt.y)/abs(dot1s[i].pt.x - dot1s[j].pt.x);
				//double sita = atan(tan)*180/CV_PI;
				double sita = Calc::getAngle(dots[i],dots[j]);
				if(sita>35 && sita<55){
					dot2.init(dots[i],dots[j],dots.types[i]);
					lsegs.add(dot2,1,dots.types[i],4,dot1Nums[i],dot1Nums[j]);
					dots.flags[i] = 0;
					dots.flags[j] = 0;
					break;
				}
			}
		}
	}

	// 4の目の決定
	Dot4Point dot4;
	Dot2Point dot2s[2];
	for(int i=0;i<lsegs.size();i++){
		if(!lsegs.flags[i]) continue;
		dot2s[0].init(lsegs[i],lsegs.types[i]);
		for(int j=0;j<lsegs.size();j++){
			if(!lsegs.flags[j]) continue;
			if(j==i) continue;
			if(lsegs.types[i] != lsegs.types[j]) continue;
			dot2s[1].init(lsegs[j],lsegs.types[j]);
			if(Calc::getDistance2(dot2s[0].center,dot2s[1].center) < dot2s[0].center.size/CV_PI){
				dot4.init(dot2s[0],dot2s[1],dot2s[0].center,dot2s[0].type);
				dot4Points.add(dot4,lsegs.dotNums[0][i]
										 ,lsegs.dotNums[0][j]
										 ,lsegs.dotNums[1][i]
										 ,lsegs.dotNums[1][j]);
				lsegs.flags[i] = 0;
				lsegs.flags[j] = 0;
				for(int k=0;k<2;k++){
					allPoints.setKind(4,lsegs.dotNums[k][i]);
					allPoints.setKind(4,lsegs.dotNums[k][j]);
				}
			}
		}
	}


}

void DiceDetection::_getDot4Points(){

	int minDistance,maxDistance,distance;
	vector<int> dot4Nums;

	DotPoints dots;
	vector<int> dot1Nums;
	for(int i=0;i<allPoints.size();i++){
		if(!allPoints.flags[i]) continue;
		dots.add(allPoints[i],1,allPoints.types[i],4);
		dot1Nums.push_back(i);
	}

		
	//Image draw;
	//draw.clone(src);
	//for(int i=0;i<dots.size();i++)
	//	dots[i].draw(draw,cv::Scalar(0,255,0));
	//draw.imshow("dots");


	Dot2Point dot2;
	LineSegments lsegs;
	int count=0;

	do{
		for(int i=0;i<dots.size();i++)
			dots.flags[i] = 1;
		lsegs.clear();
		dot4Points.clear();


		// 4の目の点から2の目のアルゴリズム適応
		for(int i=0;i<dots.size();i++){
			if(!dots.flags[i]) continue;

			// 距離指定
			if(dots.types[i] == DiceInfo::small){
				distance = dot4SmallDistance;
			}else if(dots.types[i] == DiceInfo::middle){
				distance = dot4MiddleDistance;
			}else if(dots.types[i] == DiceInfo::large){
				distance = dot4LargeDistance;
			}

			for(int j=0;j<dots.size();j++){
				if(i==j) continue;
				if(dots.types[i] != dots.types[j]) continue;
				if(!dots.flags[j]) continue;
				if(Calc::getDistance2(dots[i],dots[j]) < pow(distance,2) ){
					// 角度フィルター
					//double tan = abs(dot1s[i].pt.y - dot1s[j].pt.y)/abs(dot1s[i].pt.x - dot1s[j].pt.x);
					//double sita = atan(tan)*180/CV_PI;
					double sita = Calc::getAngle(dots[i],dots[j]);
					if(sita>=dot4MinAngle && sita<=dot4MaxAngle){
						dot2.init(dots[i],dots[j],dots.types[i]);
						bool flag = true;
						for(int l=0;l<missDotCenters.size();l++){
							if(dot2.type == DiceInfo::middle && Calc::getDistance2(missDotCenters[l],dot2.center) < dot2.center.size/CV_PI)
								flag = false;
						}
						if(flag){
							lsegs.add(dot2,1,dots.types[i],4,dot1Nums[i],dot1Nums[j]);
							dots.flags[i] = 0;
							dots.flags[j] = 0;
							break;
						}
					}
				}
			}
		}
		
		//Image draw;
		//draw.clone(src);
		//for(int i=0;i<lsegs.size();i++)
		//	lsegs[i].draw(draw,cv::Scalar(255,0,0),cv::Scalar(0,255,0));
		//draw.imshow("lsegs");

		// 4の目の決定
		Dot4Point dot4;
		Dot2Point dot2s[2];
		for(int i=0;i<lsegs.size();i++){
			if(!lsegs.flags[i]) continue;
			dot2s[0].init(lsegs[i],lsegs.types[i]);
			for(int j=0;j<lsegs.size();j++){
				if(!lsegs.flags[j]) continue;
				if(j==i) continue;
				if(lsegs.types[i] != lsegs.types[j]) continue;
				dot2s[1].init(lsegs[j],lsegs.types[j]);
				if(Calc::getDistance2(dot2s[0].center,dot2s[1].center) < dot2s[0].center.size/CV_PI){
					dot4.init(dot2s[0],dot2s[1],dot2s[0].center,dot2s[0].type);
					// 使える中心点であるか確認
					dot4Points.add(dot4,lsegs.dotNums[0][i]
										 ,lsegs.dotNums[0][j]
										 ,lsegs.dotNums[1][i]
										 ,lsegs.dotNums[1][j]);
					lsegs.flags[i] = 0;
					lsegs.flags[j] = 0;
					for(int k=0;k<2;k++){
						allPoints.setKind(4,lsegs.dotNums[k][i]);
						allPoints.setKind(4,lsegs.dotNums[k][j]);
					}					
				}
			}
		}

		//Image draw;
		//draw.clone(src);
		//for(int i=0;i<missDotCenters.size();i++)
		//	missDotCenters[i].draw(draw,cv::Scalar(0,255,255));
		//draw.imshow("missDotCenters");

		if(dot4CorrectMiddleLoopCount==count++) break;


	}while(correctMiddleDot4Points());
}


void DiceDetection::getDot5Points(){
	Dot5Point dot5;
	for(int i=0;i<allDot3Points.size();i++){
		if(!allDot3Points.flags[i]) continue;
		for(int j=i+1;j<allDot3Points.size();j++){
			if(!allDot3Points.flags[j]) continue;
			if(i==j) continue;
			if(allDot3Points.types[i] != allDot3Points.types[i]) continue;
			if(Calc::getDistance2(allDot3Points[i].center,allDot3Points[j].center) < allDot3Points[i].center.size/CV_PI){
				dot5.init(allDot3Points[i],allDot3Points[j],allDot3Points.types[i]);
				
				dot5Points.add(dot5,allDot3Points.dotNums[0][i]
											,allDot3Points.dotNums[1][i]
											,allDot3Points.dotNums[1][j]
											,allDot3Points.dotNums[2][i]
											,allDot3Points.dotNums[2][j]);
				
				allDot3Points.flags[i] = 0;
				allDot3Points.flags[j] = 0;
				
				for(int k=0;k<3;k++){
					allPoints.setKind(5,allDot3Points.dotNums[k][i]);
					allPoints.setKind(5,allDot3Points.dotNums[k][j]);
				}
				break;
			}
		}
	}
}

void DiceDetection::getDot3Points(){
	for(int i=0;i<allDot3Points.size();i++){
		if(!allDot3Points.flags[i]) continue;
		if(35<allDot3Points[i].angle && allDot3Points[i].angle<55){
			dot3Points.add(allDot3Points[i]	,allDot3Points.dotNums[0][i]
											,allDot3Points.dotNums[1][i]
											,allDot3Points.dotNums[2][i]);
			allDot3Points.flags[i]=0;
			for(int k=0;k<3;k++){
				allPoints.setKind(3,allDot3Points.dotNums[k][i]);
				allPoints.flags[allDot3Points.dotNums[k][i]] = 0;
				allPoints.kinds[allDot3Points.dotNums[k][i]] = 3;
			}
		}
	}
}

void DiceDetection::getDot6Points(){
	Dot6Point dot6;
	int radius=0;
	int distance = 0;

	// 点間距離によるallDot3Pointsの厳選
	for(int i=0;i<allDot3Points.size();i++){
		if(!allDot3Points.flags[i]) continue;
		if(allDot3Points.types[i] == DiceInfo::small)
			distance = dot6SmallDistance;
		else if(allDot3Points.types[i] == DiceInfo::middle)
			distance = dot6MiddleDistance;
		else if(allDot3Points.types[i] == DiceInfo::large)
			distance = dot6LargeDistance;
		if(Calc::getDistance2(allDot3Points[i].center,allDot3Points[i].dot[0]) > pow(distance,2) ||
		   Calc::getDistance2(allDot3Points[i].center,allDot3Points[i].dot[1]) > pow(distance,2) ){
			   allDot3Points.flags[i] = 0;
		}
	}

	// 中心間距離による抽出
	for(int i=0;i<allDot3Points.size();i++){
		if(!allDot3Points.flags[i]) continue;
		if(allDot3Points.types[i] == DiceInfo::small)
			radius = dot6SmallRadius;
		else if(allDot3Points.types[i] == DiceInfo::middle)
			radius = dot6MiddleRadius;
		else if(allDot3Points.types[i] == DiceInfo::large)
			radius = dot6LargeRadius;

		for(int j=0;j<allDot3Points.size();j++){
			if(i==j) continue;
			if(!allDot3Points.flags[j]) continue;
			if(allDot3Points.types[i] != allDot3Points.types[j]) continue;
			if(Calc::getDistance2(allDot3Points[i].center,allDot3Points[j].center) < pow(radius,2) ){
				dot6.init(allDot3Points[i],allDot3Points[j],allDot3Points.types[i]);
				dot6Points.add(dot6 ,allDot3Points.dotNums[0][i]
									,allDot3Points.dotNums[0][j]
									,allDot3Points.dotNums[1][i]
									,allDot3Points.dotNums[1][j]
									,allDot3Points.dotNums[2][i]
									,allDot3Points.dotNums[2][j]);
				allDot3Points.flags[i] = 0;
				allDot3Points.flags[j] = 0;
				for(int k=0;k<3;k++){
					allPoints.setKind(6,allDot3Points.dotNums[k][i]);
					allPoints.setKind(6,allDot3Points.dotNums[k][j]);
				}
			}
		}
	}
}

void DiceDetection::getOddPoints(){
	correctOddMiddleToLarge();
	clearAllLines();
	getAllLines();
	getDot2Points();
	getAllDot3Points();
	getDot5Points();
	getDot3Points();
	getDot6Points();
	getDot4Points();
}



/******************
 *   erase
 */

void DiceDetection::eraseDot1Points(int i){
	if(dot1Points.pointNums[i]!=-1)
		allPoints.setKind(0,dot1Points.pointNums[i]);
	dot1Points.erase(i);
}

void DiceDetection::eraseTypeDot1Points(DiceInfo::dtype type){
	for(int i=0;i<dot1Points.size();i++){
		if(dot1Points.dot1s[i].type == type){
			eraseDot1Points(i);
			i--;
		}
	}
}

void DiceDetection::eraseDot2Points(int i){
	if(dot2Points.pointNums[0][i]!=-1){
		for(int j=0;j<2;j++){
			allPoints.setKind(0,dot2Points.pointNums[j][i]);
		}
	}
	dot2Points.erase(i);
}

void DiceDetection::eraseTypeDot2Points(DiceInfo::dtype type){
	for(int i=0;i<dot2Points.size();i++){
		if(dot2Points.dot2s[i].type == type){
			eraseDot2Points(i);
			i--;
		}
	}
}

void DiceDetection::eraseDot3Points(int i){
	if(dot3Points.pointNums[0][i]!=-1){
		for(int j=0;j<3;j++){
			allPoints.setKind(0,dot3Points.pointNums[j][i]);
		}
	}
	dot3Points.erase(i);
}

void DiceDetection::eraseTypeDot3Points(DiceInfo::dtype type){
	for(int i=0;i<dot3Points.size();i++){
		if(dot3Points.dot3s[i].type == type){
			eraseDot3Points(i);
			i--;
		}
	}
}

void DiceDetection::eraseDot4Points(int i){
	if(dot4Points.pointNums[0][i]!=-1){
		for(int j=0;j<4;j++){
			allPoints.setKind(0,dot4Points.pointNums[j][i]);
		}
	}
	dot4Points.erase(i);
}

void DiceDetection::eraseTypeDot4Points(DiceInfo::dtype type){
	for(int i=0;i<dot4Points.size();i++){
		if(dot4Points.dot4s[i].type == type){
			eraseDot4Points(i);
			i--;
		}
	}
}

void DiceDetection::eraseDot5Points(int i){
	if(dot5Points.pointNums[0][i]!=-1){
		for(int j=0;j<5;j++){
			allPoints.setKind(0,dot5Points.pointNums[j][i]);
		}
	}
	dot5Points.erase(i);
}

void DiceDetection::eraseTypeDot5Points(DiceInfo::dtype type){
	for(int i=0;i<dot5Points.size();i++){
		if(dot5Points.dot5s[i].type == type){
			eraseDot5Points(i);
			i--;
		}
	}
}

void DiceDetection::eraseDot6Points(int i){
	if(dot6Points.pointNums[0][i]!=-1){
		for(int j=0;j<6;j++){
			allPoints.setKind(0,dot6Points.pointNums[j][i]);
		}
	}
	dot6Points.erase(i);
}

void DiceDetection::eraseTypeDot6Points(DiceInfo::dtype type){
	for(int i=0;i<dot6Points.size();i++){
		if(dot6Points.dot6s[i].type == type){
			eraseDot6Points(i);
			i--;
		}
	}
}

/******************
 *   clear
 */

void DiceDetection::clearAll(){
	clearAllPoints();
	clearAllLines();
	clearAllDot3Points();
	clearAllDotCenters();
	clearDot1Points();
	clearDot2Points();
	clearDot3Points();
	clearDot4Points();
	clearDot5Points();
	clearDot6Points();
}

void DiceDetection::clearAllPoints(){
	allPoints.clear();
}

void DiceDetection::clearAllLines(){
	allLines.clear();
}

void DiceDetection::clearAllDot3Points(){
	allDot3Points.clear();
}

void DiceDetection::clearAllDotCenters(){
	allDotCenters.clear();
}

void DiceDetection::clearDot1Points(){
	for(int i=0;i<dot1Points.size();i++){
		allPoints.setKind(0,dot1Points.pointNums[i]);
	}
	dot1Points.clear();
}

void DiceDetection::clearDot2Points(){
	for(int i=0;i<dot2Points.size();i++){
		for(int j=0;j<2;j++){
			allPoints.setKind(0,dot2Points.pointNums[j][i]);
		}
	}
	dot2Points.clear();
}

void DiceDetection::clearDot3Points(){
	for(int i=0;i<dot3Points.size();i++){
		for(int j=0;j<3;j++){
			allPoints.setKind(0,dot3Points.pointNums[j][i]);
		}
	}
	dot3Points.clear();
}

void DiceDetection::clearDot4Points(){
	for(int i=0;i<dot4Points.size();i++){
		for(int j=0;j<4;j++){
			allPoints.setKind(0,dot4Points.pointNums[j][i]);
		}
	}
	dot4Points.clear();
}

void DiceDetection::clearDot5Points(){
	for(int i=0;i<dot5Points.size();i++){
		for(int j=0;j<5;j++){
			allPoints.setKind(0,dot5Points.pointNums[j][i]);
		}
	}
	dot5Points.clear();
}

void DiceDetection::clearDot6Points(){
	for(int i=0;i<dot6Points.size();i++){
		for(int j=0;j<6;j++){
			allPoints.setKind(0,dot6Points.pointNums[j][i]);
		}
	}
	dot6Points.clear();
}


void DiceDetection::setTypeDot1Points(DiceInfo::dtype type,int num){
	dot1Points.dot1s[num].type = type;
	allPoints.types[dot1Points.pointNums[num]] = type;
}

void DiceDetection::setTypeDot2Points(DiceInfo::dtype type,int num){
	dot2Points.dot2s[num].type = type;
	for(int i=0;i<2;i++){
		allPoints.types[dot2Points.pointNums[i][num]] = type;
	}
}

void DiceDetection::setTypeDot3Points(DiceInfo::dtype type,int num){
	dot3Points.dot3s[num].type = type;
	for(int i=0;i<3;i++){
		allPoints.types[dot3Points.pointNums[i][num]] = type;
	}
}

void DiceDetection::setTypeDot4Points(DiceInfo::dtype type,int num){
	dot4Points.dot4s[num].type = type;
	for(int i=0;i<4;i++){
		allPoints.types[dot4Points.pointNums[i][num]] = type;
	}
}

void DiceDetection::setTypeDot5Points(DiceInfo::dtype type,int num){
	dot5Points.dot5s[num].type = type;
	for(int i=0;i<5;i++){
		allPoints.types[dot5Points.pointNums[i][num]] = type;
	}
}

void DiceDetection::setTypeDot6Points(DiceInfo::dtype type,int num){
	dot6Points.dot6s[num].type = type;
	for(int i=0;i<6;i++){
		allPoints.types[dot6Points.pointNums[i][num]] = type;
	}
}

/******************
 *   修正処理
 */

void DiceDetection::correctPointType(){

	int Lmatch=0,Mmatch=0;

	// 中サイコロを大サイコロに誤判した修正
	for(int i=0;i<allPoints.size();i++){
		Lmatch=0,Mmatch=0;
		if(allPoints.types[i] != DiceInfo::large) continue;
		if(allPoints.kinds[i] == 1) continue;
		for(int j=0;j<allPoints.size();j++){
			if(allPoints.types[j]==DiceInfo::large){
				if(Calc::getDistance2(allPoints[i],allPoints[j]) < pow(correctLargeRadius,2)){
					Lmatch++;
				}
			}else if(allPoints.types[j]==DiceInfo::middle){
				if(Calc::getDistance2(allPoints[i],allPoints[j]) < pow(correctMiddleRadius,2)){
					if(allPoints.kinds[j] == 1){
						Mmatch+=5;
					}else{
						Mmatch++;
					}
				}
			}
		}
		if(Mmatch>=Lmatch)
			if(allPoints[i].size<correctMiddleMaxSize)
				allPoints.types[i] = DiceInfo::middle;
	}

	// 大サイコロを中サイコロに誤判した修正 
	for(int i=0;i<allPoints.size();i++){
		Lmatch=0,Mmatch=0;
		if(allPoints.types[i] != DiceInfo::middle) continue;
		//if(allPoints.kinds[i] == 1) continue;
		for(int j=0;j<allPoints.size();j++){
			if(allPoints.types[j]==DiceInfo::large){
				if(Calc::getDistance2(allPoints[i],allPoints[j]) < pow(correctLargeRadius,2)){
					Lmatch++;
				}
			}else if(allPoints.types[j]==DiceInfo::middle){
				if(Calc::getDistance2(allPoints[i],allPoints[j]) < pow(correctMiddleRadius,2)){
					if(allPoints.kinds[j] == 1){
						Mmatch+=5;
					}else{
						Mmatch++;

					}
				}
			}
		}
		if(Mmatch<=Lmatch){
			if(allPoints[i].size>correctLargeMinSize)
				allPoints.types[i] = DiceInfo::large;
		}
	}
	
}

int DiceDetection::correctMiddleDot4Points(){
	int missNum=0;
	bool flag = true;
	for(int i = 0;i<allPoints.size();i++){
		if(allPoints.types[i] != DiceInfo::middle) continue;
		if(allPoints.flags[i]) missNum++;
	}

	//std::cout<<"missNum:"<<missNum<<std::endl;
	//std::cout<<"missDotCenters Num:"<<missDotCenters.size()<<std::endl;

	if(missNum==0) return 0;

	getAllDotCenters();

	for(int i=0;i<allDotCenters.size();i++){
		flag = true;
		if(allDotCenters.kinds[i] != 4) continue;
		if(allDotCenters.types[i] != DiceInfo::middle) continue;
		for(int j=0;j<allDotCenters.size();j++){
			if(allDotCenters.types[j] != DiceInfo::middle) continue;
			if(i==j) continue;
			if(Calc::getDistance2(allDotCenters[i],allDotCenters[j]) < pow(dot4CorrectMiddleDistance,2)){
				flag = false;
				break;
			}
		}
		if(flag){
			//if(missDotCenters.size()){
			for(int j=0;j<missDotCenters.size();j++){
				if(Calc::getDistance2(allDotCenters[i],missDotCenters[j]) < allDotCenters[i].size/CV_PI)
					flag = false;
			}
			if(flag) 
				missDotCenters.add(allDotCenters[i],DiceInfo::middle,4,allDotCenters.numbers[i]);
			//}else{
			//	missDotCenters.add(allDotCenters[i],DiceInfo::middle,4);
			//}
		}
	}

	return missNum;
}


void DiceDetection::correctOddMiddleToLarge(){
	for(int i=0;i<allPoints.size();i++){
		if(!allPoints.flags[i]) continue;
		if(allPoints.types[i] == DiceInfo::large ||
			allPoints.types[i] == DiceInfo::none)
			allPoints.types[i] = DiceInfo::middle;
	}
}

/******************
 *   描写処理
 */

void DiceDetection::drawAllPoints(Image& img,cv::Scalar scal){
	for(int i=0;i<allPoints.size();i++){
		allPoints[i].draw(img,scal);
	}
}

void DiceDetection::drawTruePoints(Image& img,cv::Scalar scal){
	for(int i=0;i<allPoints.size();i++){
		if(allPoints.flags[i]){
			allPoints[i].draw(img,scal);
		}
	}
}

void DiceDetection::drawFalsePoints(Image& img,cv::Scalar scal){
	for(int i=0;i<allPoints.size();i++){
		if(!allPoints.flags[i])	
			allPoints[i].draw(img,scal);
	}
}

void DiceDetection::drawTypePoints(Image& img,DiceInfo::dtype type,cv::Scalar scal){
	for(int i=0;i<allPoints.size();i++){
		if(allPoints.types[i] == type)
			allPoints[i].draw(img,scal);
	}
}

void DiceDetection::drawKindPoints(Image& img,int kind,cv::Scalar scal){
	for(int i=0;i<allPoints.size();i++){
		if(allPoints.kinds[i] == kind)
			allPoints[i].draw(img,scal);
	}
}

void DiceDetection::drawAllLine(Image& img,cv::Scalar dot_col,cv::Scalar line_col,int thickness){
	for(int i=0;i<allLines.size();i++){
		allLines[i].draw(img,dot_col,line_col,thickness);
	}
}

void DiceDetection::drawTrueLine(Image& img,cv::Scalar dot_col,cv::Scalar line_col,int thickness){
	for(int i=0;i<allLines.size();i++){
		if(allLines.flags[i])
			allLines[i].draw(img,dot_col,line_col,thickness);
	}
}

void DiceDetection::drawFalseLine(Image& img,cv::Scalar dot_col,cv::Scalar line_col,int thickness){
	for(int i=0;i<allLines.size();i++){
		if(!allLines.flags[i])
			allLines[i].draw(img,dot_col,line_col,thickness);
	}
}

void DiceDetection::drawTypeLine(Image& img,DiceInfo::dtype type,cv::Scalar dot_col,cv::Scalar line_col,int thickness){
	for(int i=0;i<allLines.size();i++){
		if(allLines.types[i] == type)
			allLines[i].draw(img,dot_col,line_col,thickness);
	}
}

void DiceDetection::drawKindLine(Image& img,int kind,cv::Scalar dot_col,cv::Scalar line_col,int thickness){
	for(int i=0;i<allLines.size();i++){
		if(allLines.kinds[i] == kind)
			allLines[i].draw(img,dot_col,line_col,thickness);
	}
}

void DiceDetection::drawDot1Points(Image& img,cv::Scalar scal){
	for(int i=0;i<dot1Points.size();i++){	
			dot1Points.dot1s[i].draw(img,scal);
	}
}

void DiceDetection::drawTypeDot1Points(Image& img,DiceInfo::dtype type,cv::Scalar scal){
	for(int i=0;i<dot1Points.size();i++){	
		if(dot1Points.dot1s[i].type == type)
			dot1Points.dot1s[i].draw(img,scal);
	}
}

void DiceDetection::drawDot2Points(Image& img,cv::Scalar dot_col,cv::Scalar line_col,int thickness){
	for(int i=0;i<dot2Points.size();i++){
		dot2Points.dot2s[i].draw(img,dot_col,line_col,thickness);
	}
}

void DiceDetection::drawTypeDot2Points(Image& img,DiceInfo::dtype type,cv::Scalar dot_col,cv::Scalar line_col,int thickness){
	for(int i=0;i<dot2Points.size();i++){
		if(dot2Points.dot2s[i].type == type)
			dot2Points.dot2s[i].draw(img,dot_col,line_col,thickness);
	}
}

void DiceDetection::drawDot2Center(Image& img,cv::Scalar scal){
	for(int i=0;i<dot2Points.size();i++){
		dot2Points.dot2s[i].drawCenter(img,scal);
	}
}

void DiceDetection::drawDot4Points(Image& img,cv::Scalar dot_col,cv::Scalar line_col,int thickness){
	for(int i=0;i<dot4Points.size();i++){
		dot4Points.dot4s[i].draw(img,dot_col,line_col,thickness);
	}
}

void DiceDetection::drawTypeDot4Points(Image& img,DiceInfo::dtype type,cv::Scalar dot_col,cv::Scalar line_col,int thickness){
	for(int i=0;i<dot4Points.size();i++){
		if(dot4Points.dot4s[i].type == type)
			dot4Points.dot4s[i].draw(img,dot_col,line_col,thickness);
	}
}

void DiceDetection::drawDot4Center(Image& img,cv::Scalar scal){
	for(int i=0;i<dot4Points.size();i++){
		dot4Points.dot4s[i].drawCenter(img,scal);
	}
}

void DiceDetection::drawAllDot3Points(Image& img,cv::Scalar dot_col,cv::Scalar line_col,int thickness){
	for(int i=0;i<allDot3Points.size();i++){
		allDot3Points[i].draw(img,dot_col,line_col,thickness);
	}
}

void DiceDetection::drawAllDot3Center(Image& img,cv::Scalar scal){
	for(int i=0;i<allDot3Points.size();i++){
		allDot3Points[i].drawCenter(img,scal);
	}
}

void DiceDetection::drawTrueAllDot3Points(Image& img,cv::Scalar dot_col,cv::Scalar line_col,int thickness){
	for(int i=0;i<allDot3Points.size();i++){
		if(allDot3Points.flags[i])
			allDot3Points[i].draw(img,dot_col,line_col,thickness);
	}
}

void DiceDetection::drawFalseAllDot3Points(Image& img,cv::Scalar dot_col,cv::Scalar line_col,int thickness){
	for(int i=0;i<allDot3Points.size();i++){
		if(!allDot3Points.flags[i])
			allDot3Points[i].draw(img,dot_col,line_col,thickness);
	}
}

void DiceDetection::drawTypeAllDot3Points(Image& img,DiceInfo::dtype type,cv::Scalar dot_col,cv::Scalar line_col,int thickness){
	for(int i=0;i<allDot3Points.size();i++){
		if(allDot3Points.types[i] == type)
			allDot3Points[i].draw(img,dot_col,line_col,thickness);
	}
}

void DiceDetection::drawKindAllDot3Points(Image& img,int kind,cv::Scalar dot_col,cv::Scalar line_col,int thickness){
	for(int i=0;i<allDot3Points.size();i++){
		if(allDot3Points.kinds[i] == kind)
			allDot3Points[i].draw(img,dot_col,line_col,thickness);
	}
}

void DiceDetection::drawDot5Points(Image& img,cv::Scalar dot_col,cv::Scalar line_col,int thickness){
	for(int i=0;i<dot5Points.size();i++){
		dot5Points.dot5s[i].draw(img,dot_col,line_col,thickness);
	}
}

void DiceDetection::drawTypeDot5Points(Image& img,DiceInfo::dtype type,cv::Scalar dot_col,cv::Scalar line_col,int thickness){
	for(int i=0;i<dot5Points.size();i++){
		if(dot5Points.dot5s[i].type == type)
			dot5Points.dot5s[i].draw(img,dot_col,line_col,thickness);
	}
}

void DiceDetection::drawDot5Center(Image& img,cv::Scalar scal){
	for(int i=0;i<dot5Points.size();i++){
		dot5Points.dot5s[i].drawCenter(img,scal);
	}
}

void DiceDetection::drawDot3Points(Image& img,cv::Scalar dot_col,cv::Scalar line_col,int thickness){
	for(int i=0;i<dot3Points.size();i++){
		dot3Points.dot3s[i].draw(img,dot_col,line_col,thickness);
	}
}

void DiceDetection::drawTypeDot3Points(Image& img,DiceInfo::dtype type,cv::Scalar dot_col,cv::Scalar line_col,int thickness){
	for(int i=0;i<dot3Points.size();i++){
		if(dot3Points.dot3s[i].type == type)
			dot3Points.dot3s[i].draw(img,dot_col,line_col,thickness);
	}
}

void DiceDetection::drawDot3Center(Image& img,cv::Scalar scal){
	for(int i=0;i<dot3Points.size();i++){
		dot3Points.dot3s[i].drawCenter(img,scal);
	}
}

void DiceDetection::drawDot6Points(Image& img,cv::Scalar dot_col,cv::Scalar line_col,int thickness){
	for(int i=0;i<dot6Points.size();i++){
		dot6Points.dot6s[i].draw(img,dot_col,line_col,thickness);
	}
}

void DiceDetection::drawTypeDot6Points(Image& img,DiceInfo::dtype type,cv::Scalar dot_col,cv::Scalar line_col,int thickness){
	for(int i=0;i<dot6Points.size();i++){
		if(dot6Points.dot6s[i].type == type)
			dot6Points.dot6s[i].draw(img,dot_col,line_col,thickness);
	}
}

void DiceDetection::drawDot6Center(Image& img,cv::Scalar scal){
	for(int i=0;i<dot6Points.size();i++){
		dot6Points.dot6s[i].drawCenter(img,scal);
	}
}

void DiceDetection::drawAllDotCenters(Image& img,cv::Scalar scal){
	for(int i=0;i<allDotCenters.size();i++){
		allDotCenters[i].draw(img,0.5,scal);
	}
}

void DiceDetection::drawTypeAllDotCenters(Image& img,DiceInfo::dtype type,cv::Scalar scal){
	for(int i=0;i<allDotCenters.size();i++){
		if(allDotCenters.types[i] == type)
			allDotCenters[i].draw(img,0.5,scal);
	}
}

void DiceDetection::drawKindAllDotCenters(Image& img,int kind,cv::Scalar scal){
	for(int i=0;i<allDotCenters.size();i++){
		if(allDotCenters.kinds[i] == kind)
			allDotCenters[i].draw(img,0.5,scal);
	}
}



/******************
 *   個数取得
 */

int DiceDetection::getNumAllPoints() const{
	return allPoints.size();
}

int DiceDetection::getNumTrueAllPoints() const{
	int count=0;
	for(int i=0;i<allPoints.size();i++){
		if(allPoints.flags[i]) count++;
	}
	return count;
}

int DiceDetection::getNumFalseAllPoints() const{
	int count=0;
	for(int i=0;i<allPoints.size();i++){
		if(!allPoints.flags[i]) count++;
	}
	return count;
}

int DiceDetection::getNumTypeAllPoints(DiceInfo::dtype type) const{
	int count=0;
	for(int i=0;i<allPoints.size();i++){
		if(allPoints.types[i] == type) count++;
	}
	return count;
}

int DiceDetection::getNumKindAllPoints(int kind) const{
	int count=0;
	for(int i=0;i<allPoints.size();i++){
		if(allPoints.kinds[i] == kind) count++;
	}
	return count;
}

int DiceDetection::getNumAllLines() const{
	return allLines.size();
}

int DiceDetection::getNumTrueAllLines() const{
	int count=0;
	for(int i=0;i<allLines.size();i++){
		if(allLines.flags[i]) count++;
	}
	return count;
}

int DiceDetection::getNumFalseAllLines() const{
	int count=0;
	for(int i=0;i<allLines.size();i++){
		if(!allLines.flags[i]) count++;
	}
	return count;
}

int DiceDetection::getNumTypeAllLines(DiceInfo::dtype type) const{
	int count=0;
	for(int i=0;i<allLines.size();i++){
		if(allLines.types[i] == type) count++;
	}
	return count;
}

int DiceDetection::getNumKindAllLines(int kind) const{
	int count=0;
	for(int i=0;i<allLines.size();i++){
		if(allLines.kinds[i] == kind) count++;
	}
	return count;
}

int DiceDetection::getNumAllDot3Points() const{
	return allDot3Points.size();
}

int DiceDetection::getNumTrueAllDot3Points() const{
	int count=0;
	for(int i=0;i<allDot3Points.size();i++){
		if(allDot3Points.flags[i]) count++;
	}
	return count;
}

int DiceDetection::getNumFalseAllDot3Points() const{
	int count=0;
	for(int i=0;i<allDot3Points.size();i++){
		if(!allDot3Points.flags[i]) count++;
	}
	return count;
}

int DiceDetection::getNumTypeAllDot3Points(DiceInfo::dtype type) const{
	int count=0;
	for(int i=0;i<allDot3Points.size();i++){
		if(allDot3Points.types[i] == type) count++;
	}
	return count;
}

int DiceDetection::getNumKindAllDot3Points(int kind) const{
	int count=0;
	for(int i=0;i<allDot3Points.size();i++){
		if(allDot3Points.kinds[i] == kind) count++;
	}
	return count;
}

int DiceDetection::getNumAllDotCenters() const{
	return allDotCenters.size();
}

int DiceDetection::getNumTypeAllDotCenters(DiceInfo::dtype type) const{
	int count = 0;
	for(int i=0;i<allDotCenters.size();i++){
		if(allDotCenters.types[i] == type) count++;
	}
	return count;
}

int DiceDetection::getNumKindAllDotCenters(int kind) const{
	int count = 0;
	for(int i=0;i<allDotCenters.size();i++){
		if(allDotCenters.kinds[i] == kind) count++;
	}
	return count;
}

int DiceDetection::getNumDot1Points(DiceInfo::dtype type) const{
	int count = 0;
	if(type == DiceInfo::none) 
		return dot1Points.size();
	for(int i=0;i<dot1Points.size();i++){
		if(dot1Points.dot1s[i].type == type) count++;
	}
	return count;
}

int DiceDetection::getNumDot2Points(DiceInfo::dtype type) const{
	int count = 0;
	if(type == DiceInfo::none) 
		return dot2Points.size();
	for(int i=0;i<dot2Points.size();i++){
		if(dot2Points.dot2s[i].type == type) count++;
	}
	return count;
}

int DiceDetection::getNumDot3Points(DiceInfo::dtype type) const{
	int count = 0;
	if(type == DiceInfo::none) 
		return dot3Points.size();
	for(int i=0;i<dot3Points.size();i++){
		if(dot3Points.dot3s[i].type == type) count++;
	}
	return count;
}

int DiceDetection::getNumDot4Points(DiceInfo::dtype type) const{
	int count = 0;
	if(type == DiceInfo::none) 
		return dot4Points.size();
	for(int i=0;i<dot4Points.size();i++){
		if(dot4Points.dot4s[i].type == type) count++;
	}
	return count;
}

int DiceDetection::getNumDot5Points(DiceInfo::dtype type) const{
	int count = 0;
	if(type == DiceInfo::none) 
		return dot5Points.size();
	for(int i=0;i<dot5Points.size();i++){
		if(dot5Points.dot5s[i].type == type) count++;
	}
	return count;
}

int DiceDetection::getNumDot6Points(DiceInfo::dtype type) const{
	int count = 0;
	if(type == DiceInfo::none) 
		return dot6Points.size();
	for(int i=0;i<dot6Points.size();i++){
		if(dot6Points.dot6s[i].type == type) count++;
	}
	return count;
}



/******************
 *   イベント関連
 */
//
//void DiceDetection::onMouseOdd(int event,int x,int y,int flag,void *data){
//	DiceDetection *dd = reinterpret_cast<DiceDetection*>(data);
//	dd->onMouseOdd_impl(event,x,y,flag);
//}
//
//void DiceDetection::onMouseOdd_impl(int event,int x,int y,int flag){
//	switch(event) {
//	case cv::EVENT_MOUSEMOVE:
//		setMousePointDot(x,y);
//		break;
//	case cv::EVENT_LBUTTONDOWN:
//		correctDice();
//		break;
//	}
//}

void DiceDetection::onMouse_impl(int event,int x,int y,int flag){
	switch(event) {
	case cv::EVENT_MOUSEMOVE:
		setMousePointCenter(x,y);
		//std::cout<<x<<","<<y<<std::endl;
		break;
	case cv::EVENT_LBUTTONDOWN:
		switch (modeFlag)
		{
		case 0:
			mouseCorrectType();
			break;
		case 1:
			mouseCorrectKind();
			break;
		case 2:
			mouseCreateKind();
			break;
		case 3:
			mouseRotatoCenterPoint();
		default:
			break;
		}
		break;
	case cv::EVENT_RBUTTONDOWN:
		int kind = mode.kind;
		mode.kind=0;
		mouseCorrectKind();
		mode.kind = kind;
		break;
	}
}

int DiceDetection::keyEvent(int key){
	switch(key){
	case '0':
		//mode.kind = 0;
		break;
	case '1':
		mode.kind = 1;
		break;
	case '2':
		mode.kind = 2;
		break;
	case '3':
		mode.kind = 3;
		break;
	case '4':
		mode.kind = 4;
		break;
	case '5':
		mode.kind = 5;
		break;
	case '6':
		mode.kind = 6;
		break;
	case 'l':
		mode.type = DiceInfo::large;
		break;
	case 'm':
		//mode.type = DiceInfo::middle;
		break;
	case 's':
		mode.type = DiceInfo::small;
		break;
	case 'n':
		//mode.type = DiceInfo::none;
		break;
	case 't':
		//modeFlag = 0;
		break;
	case 'k':
		//modeFlag = 1;
		break;
	case 'c':
		modeFlag = 2;
		break;
	case 'o':
		outEncode();
		std::cout << std::endl;
		std::cout << "Out Put Dncode" << std::endl; 
		break;
	case 'r':
		modeFlag = 3;
		rotationImage();
		break;
	case 'q':
		return 0;
		break;
	default:
		break;
	}
	return 1;
}

void DiceDetection::setMousePointCenter(int x,int y){
	bool flag = true;
	for(int i=0;i<allDotCenters.size();i++){
		if(Calc::getDistance2(cv::Point2f(x,y),allDotCenters[i]) < allDotCenters.centers[i].size*3){
			this->x = allDotCenters.centers[i].pt.x;
			this->y = allDotCenters.centers[i].pt.y;
			//now_mouse.type = allDotCenters.types[i];
			//now_mouse.kind = allDotCenters.kinds[i];
			centerNum = i;
			flag = false;
			break;
		}
	}
	if(flag){
		//now_mouse.type = DiceInfo::none;
		//now_mouse.kind = 0;
		centerNum = -1;
		this->x=x;
		this->y=y;
	}
}

void DiceDetection::mouseCorrectType(){
	
	if(centerNum==-1) return;
	if(allDotCenters.types[centerNum] == mode.type) return;
	switch (allDotCenters.kinds[centerNum])
	{
	case 1:
		if(dot1Points.pointNums[allDotCenters.numbers[centerNum]]!=-1){
			setTypeDot1Points(mode.type,allDotCenters.numbers[centerNum]);
		}else{
			eraseDot1Points(allDotCenters.numbers[centerNum]);
			dot1Points.add(allDotCenters[centerNum],mode.type);
		}
		break;
	case 2:		
		if(dot2Points.pointNums[0][allDotCenters.numbers[centerNum]]!=-1){
			setTypeDot2Points(mode.type,allDotCenters.numbers[centerNum]);
		}else{
			eraseDot2Points(allDotCenters.numbers[centerNum]);
			dot2Points.add(allDotCenters[centerNum],mode.type);
		}
		break;
	case 3:
		if(dot3Points.pointNums[0][allDotCenters.numbers[centerNum]]!=-1){
			setTypeDot3Points(mode.type,allDotCenters.numbers[centerNum]);
		}else{
			eraseDot3Points(allDotCenters.numbers[centerNum]);
			dot3Points.add(allDotCenters[centerNum],mode.type);
		}
		break;
	case 4:
		if(dot4Points.pointNums[0][allDotCenters.numbers[centerNum]]!=-1){
			setTypeDot4Points(mode.type,allDotCenters.numbers[centerNum]);
		}else{
			eraseDot4Points(allDotCenters.numbers[centerNum]);
			dot4Points.add(allDotCenters[centerNum],mode.type);
		}
		break;
	case 5:
		if(dot5Points.pointNums[0][allDotCenters.numbers[centerNum]]!=-1){
			setTypeDot5Points(mode.type,allDotCenters.numbers[centerNum]);
		}else{
			eraseDot5Points(allDotCenters.numbers[centerNum]);
			dot5Points.add(allDotCenters[centerNum],mode.type);
		}
		break;
	case 6:
		if(dot6Points.pointNums[0][allDotCenters.numbers[centerNum]]!=-1){
			setTypeDot6Points(mode.type,allDotCenters.numbers[centerNum]);
		}else{
			eraseDot6Points(allDotCenters.numbers[centerNum]);
			dot6Points.add(allDotCenters[centerNum],mode.type);
		}
		break;
	default:
		break;
	}

	getAllDotCenters();

	drawRun();

}

void DiceDetection::mouseCorrectKind(){

	if(centerNum==-1) return;
	if(allDotCenters.kinds[centerNum] == mode.kind) return;
	switch (allDotCenters.kinds[centerNum])
	{
	case 1:
		eraseDot1Points(allDotCenters.numbers[centerNum]);
		break;
	case 2:		
		eraseDot2Points(allDotCenters.numbers[centerNum]);
		break;
	case 3:
		eraseDot3Points(allDotCenters.numbers[centerNum]);
		break;
	case 4:
		eraseDot4Points(allDotCenters.numbers[centerNum]);
		break;
	case 5:
		eraseDot5Points(allDotCenters.numbers[centerNum]);
		break;
	case 6:
		eraseDot6Points(allDotCenters.numbers[centerNum]);
		break;
	default:
		break;
	}

	switch (mode.kind)
	{	
	case 1:
		dot1Points.add(allDotCenters[centerNum],allDotCenters.types[centerNum]);
		break;
	case 2:		
		dot2Points.add(allDotCenters[centerNum],allDotCenters.types[centerNum]);
		break;
	case 3:
		dot3Points.add(allDotCenters[centerNum],allDotCenters.types[centerNum]);
		break;
	case 4:
		dot4Points.add(allDotCenters[centerNum],allDotCenters.types[centerNum]);
		break;
	case 5:
		dot5Points.add(allDotCenters[centerNum],allDotCenters.types[centerNum]);
		break;
	case 6:
		dot6Points.add(allDotCenters[centerNum],allDotCenters.types[centerNum]);
		break;
	default:
		break;
	}

	getAllDotCenters();

	drawRun();

}

void DiceDetection::mouseCreateKind(){
	if(centerNum != -1){
		int kind = mode.kind;
		mode.kind=0;
		mouseCorrectKind();
		mode.kind=kind;
	}

	DotPoint center;
	center.init(cv::Point2f(x,y),0);

	switch (mode.kind)
	{	
	case 1:
		dot1Points.add(center,mode.type);
		break;
	case 2:		
		dot2Points.add(center,mode.type);
		break;
	case 3:
		dot3Points.add(center,mode.type);
		break;
	case 4:
		dot4Points.add(center,mode.type);
		break;
	case 5:
		dot5Points.add(center,mode.type);
		break;
	case 6:
		dot6Points.add(center,mode.type);
		break;
	default:
		break;
	}

	getAllDotCenters();

	drawRun();
}

//void DiceDetection::setMousePointDot(int x,int y){
//	bool flag = true;
//	for(int i=0;i<allPoints.size();i++){
//		if(!allPoints.flags[i]) continue;
//		if(Calc::getDistance2(cv::Point2f(x,y),allPoints[i]) < allPoints.points[i].size*6){
//			this->x = allDotCenters.centers[i].pt.x;
//			this->y = allDotCenters.centers[i].pt.y;
//			flag = false;
//			break;
//		}
//	}
//	if(flag){
//		this->x=x;
//		this->y=y;
//	}
//}

/******************
 *   回転処理
 */

void DiceDetection::rotationImage(){
	rotatoAngle = 0;
	rCenter = cv::Point2f(src.size().width/2,src.size().height/2);
	while(rotatoKeyEvent(cv::waitKey(30))){
		rotato.rotation(src,rCenter,rotatoAngle);
		rotato.circle(rCenter,30,cv::Scalar(0,255,255));
		rotato.imshow("rotato");

		cv::setMouseCallback("rotato", onMouse, this);

	}
}

int DiceDetection::rotatoKeyEvent(int key){
	switch(key){
	case 2424832: // [←]
		rotatoAngle -= 1;
		break;
	case 2555904: // [→]
		rotatoAngle += 1;
		break;
	case 13:
		src.rotation(src,rCenter,rotatoAngle);
		clearAll();
		run();
		cv::destroyWindow("rotato");
		modeFlag = 2;
		return 0;
		break;
	case ' ':
		cv::destroyWindow("rotato");
		modeFlag = 2;
		return 0;
		break;
	}
	return 1;
}

void DiceDetection::mouseRotatoCenterPoint(){
	rCenter.x = this->x;
	rCenter.y = this->y;
}

/******************
 *   パラメータ関連
 */

void DiceDetection::setDefaultParam(){

	// ファイル関連
	dir = Dir();
	this->name = "img.jpg";

	// サイコロのサイズ判別に使用する定数群
	dotSmallMinSize				= default_dotSmallMinSize			;
	dotSmallMaxSize				= default_dotSmallMaxSize			;		
	dotMiddleMinSize			= default_dotMiddleMinSize			;
	dotMiddleMaxSize			= default_dotMiddleMaxSize			;	
	dotLargeMinSize				= default_dotLargeMinSize			;
	dotLargeMaxSize				= default_dotLargeMaxSize			;
	dotNoneMinSize				= default_dotNoneMinSize			;
	dotNoneMaxSize				= default_dotNoneMaxSize			;
	dot1MinSize					= default_dot1MinSize				;
	dot1MaxSize					= default_dot1MaxSize				;
	dotCircleFilterPer			= default_dotCircleFilterPer		;
	dotCircleFilterRadiusPer	= default_dotCircleFilterRadiusPer	;

	// 1の目の抽出
	dot1CircleFilterPer			= default_dot1CircleFilterPer		;
	dot1CircleFilterRadiusPer	= default_dot1CircleFilterRadiusPer	;
	dot1LMDetectRadius			= default_dot1LMDetectRadius		;
	dot1LMCorrectRadius			= default_dot1LMCorrectRadius		;

	// 大中サイコロに誤判定した中サイコロの点修正のための半径
	correctMiddleRadius		= default_correctMiddleRadius	;
	correctLargeRadius		= default_correctLargeRadius	;
	correctMiddleMaxSize	= default_correctMiddleMaxSize	;
	correctLargeMinSize		= default_correctLargeMinSize	;

	// 線分検出半径
	lineSmallRadius			= default_lineSmallRadius	;
	lineMiddleRadius		= default_lineMiddleRadius	;
	lineLargeRadius			= default_lineLargeRadius	;

	// ２の目検出の半径
	dot2SmallMinDistance	= default_dot2SmallMinDistance	;
	dot2MiddleMinDistance	= default_dot2MiddleMinDistance	;
	dot2LargeMinDistance	= default_dot2LargeMinDistance	;
	dot2SmallMaxDistance	= default_dot2SmallMaxDistance	;
	dot2MiddleMaxDistance	= default_dot2MiddleMaxDistance	;
	dot2LargeMaxDistance	= default_dot2LargeMaxDistance	;
	dot2SmallDistance		= default_dot2SmallDistance		;
	dot2MiddleDistance		= default_dot2MiddleDistance	;
	dot2LargeDistance		= default_dot2LargeDistance		;
	dot2MinAngle			= default_dot2MinAngle			;
	dot2MaxAngle			= default_dot2MaxAngle			;

	// ４の目検出
	dot4SmallMinDistance		= default_dot4SmallMinDistance		;
	dot4MiddleMinDistance		= default_dot4MiddleMinDistance		;
	dot4LargeMinDistance		= default_dot4LargeMinDistance		;
	dot4SmallMaxDistance		= default_dot4SmallMaxDistance		;
	dot4MiddleMaxDistance		= default_dot4MiddleMaxDistance		;
	dot4LargeMaxDistance		= default_dot4LargeMaxDistance		;
	dot4SmallDistance			= default_dot4SmallDistance			;
	dot4MiddleDistance			= default_dot4MiddleDistance		;
	dot4LargeDistance			= default_dot4LargeDistance			;
	dot4MinAngle				= default_dot4MinAngle				;
	dot4MaxAngle				= default_dot4MaxAngle				;
	dot4CorrectMiddleDistance	= default_dot4CorrectMiddleDistance	;
	dot4CorrectMiddleLoopCount	= default_dot4CorrectMiddleLoopCount;

	// 全3点
	allDot3Angle				= default_allDot3Angle				;
	allDot3SmallMinDistance		= default_allDot3SmallMinDistance	;
	allDot3MiddleMinDistance	= default_allDot3MiddleMinDistance	;
	allDot3LargeMinDistance		= default_allDot3LargeMinDistance	;
	allDot3SmallMaxDistance		= default_allDot3SmallMaxDistance	;
	allDot3MiddleMaxDistance	= default_allDot3MiddleMaxDistance	;
	allDot3LargeMaxDistance		= default_allDot3LargeMaxDistance	;

	// 6の目
	dot6SmallDistance	= default_dot6SmallDistance	;
	dot6MiddleDistance	= default_dot6MiddleDistance;
	dot6LargeDistance	= default_dot6LargeDistance	;
	dot6SmallRadius		= default_dot6SmallRadius	;
	dot6MiddleRadius	= default_dot6MiddleRadius	;
	dot6LargeRadius		= default_dot6LargeRadius	;

	// 色
}

/******************
 *   設定ファイル関連
 */

void DiceDetection::defaultIniFileCreate(){
	ptree pt;
	string name = "default_" + this->iniFileName;
	string brank = "";
	
	// コメント書き込める。
	//pt.put(";ppp",brank);

	// ファイル関連
	pt.put("file.dir",dir.pwd());
	pt.put("file.name",this->name);

	// 全点処理のパラメータ群
	//pt.put("allDot.", 1);
	pt.put("allDot.SmallMinSize", default_dotSmallMinSize			);
	pt.put("allDot.SmallMaxSize", default_dotSmallMaxSize			);
	pt.put("allDot.MiddleMinSize", default_dotMiddleMinSize			);
	pt.put("allDot.MiddleMaxSize", default_dotMiddleMaxSize			);
	pt.put("allDot.LargeMinSize", default_dotLargeMinSize			);
	pt.put("allDot.LargeMaxSize", default_dotLargeMaxSize			);
	pt.put("allDot.NoneMinSize", default_dotNoneMinSize			);
	pt.put("allDot.NoneMaxSize", default_dotNoneMaxSize			);
	pt.put("allDot.dot1MinSize", default_dot1MinSize				);
	pt.put("allDot.dot1MaxSize", default_dot1MaxSize				);
	pt.put("allDot.CircleFilterPer", default_dotCircleFilterPer		);
	pt.put("allDot.CircleFilterRadiusPer", default_dotCircleFilterRadiusPer);
	
	// タイプ修正のパラメータ群
	//pt.put("correct.", 1);
	pt.put("correct.MiddleRadius",	default_correctMiddleRadius	);
	pt.put("correct.LargeRadius",	default_correctLargeRadius	);
	pt.put("correct.MiddleMaxSize", default_correctMiddleMaxSize	);
	pt.put("correct.LargeMinSize",	default_correctLargeMinSize	);

	// 全線分処理のパラメータ群
	pt.put("allLine.SmallRadius",	default_lineSmallRadius	);
	pt.put("allLine.MiddleRadius",	default_lineMiddleRadius	);
	pt.put("allLine.LargeRadius",	default_lineLargeRadius	);
	
	// 全3点処理のパラメータ群
	//pt.put("allDot3.", 1);
	pt.put("allDot3.Angle",				default_allDot3Angle				);
	pt.put("allDot3.SmallMinDistance",	default_allDot3SmallMinDistance	);
	pt.put("allDot3.MiddleMinDistance",	default_allDot3MiddleMinDistance	);
	pt.put("allDot3.LargeMinDistance",	default_allDot3LargeMinDistance	);
	pt.put("allDot3.SmallMaxDistance",	default_allDot3SmallMaxDistance	);
	pt.put("allDot3.MiddleMaxDistance",	default_allDot3MiddleMaxDistance	);
	pt.put("allDot3.LargeMaxDistance",	default_allDot3LargeMaxDistance	);

	// １の目処理のパラメータ群
	//pt.put("dot1.", 1);
	pt.put("dot1.CircleFilterPer",		default_dot1CircleFilterPer		);
	pt.put("dot1.CircleFilterRadiusPer",default_dot1CircleFilterRadiusPer	);
	pt.put("dot1.LMDetectRadius",		default_dot1LMDetectRadius		);
	pt.put("dot1.LMCorrectRadius",		default_dot1LMCorrectRadius		);

	// ２の目処理のパラメータ群
	//pt.put("dot2.", 1);
	pt.put("dot2.SmallMinDistance",		default_dot2SmallMinDistance	);
	pt.put("dot2.MiddleMinDistance",	default_dot2MiddleMinDistance	);
	pt.put("dot2.LargeMinDistance",		default_dot2LargeMinDistance	);
	pt.put("dot2.SmallMaxDistance",		default_dot2SmallMaxDistance	);
	pt.put("dot2.MiddleMaxDistance",	default_dot2MiddleMaxDistance	);
	pt.put("dot2.LargeMaxDistance",		default_dot2LargeMaxDistance	);
	pt.put("dot2.SmallDistance",		default_dot2SmallDistance		);
	pt.put("dot2.MiddleDistance",		default_dot2MiddleDistance		);
	pt.put("dot2.LargeDistance",		default_dot2LargeDistance		);
	pt.put("dot2.MinAngle",				default_dot2MinAngle			);
	pt.put("dot2.MaxAngle",				default_dot2MaxAngle			);

	// ３の目処理のパラメータ群
	//pt.put("dot3.", 1);

	// ４の目処理のパラメータ群
	//pt.put("dot4.",1);
	pt.put("dot4.SmallMinDistance",			default_dot4SmallMinDistance		);
	pt.put("dot4.MiddleMinDistance",		default_dot4MiddleMinDistance		);
	pt.put("dot4.LargeMinDistance",			default_dot4LargeMinDistance		);
	pt.put("dot4.SmallMaxDistance",			default_dot4SmallMaxDistance		);
	pt.put("dot4.MiddleMaxDistance",		default_dot4MiddleMaxDistance		);
	pt.put("dot4.LargeMaxDistance",			default_dot4LargeMaxDistance		);
	pt.put("dot4.SmallDistance",			default_dot4SmallDistance			);
	pt.put("dot4.MiddleDistance",			default_dot4MiddleDistance		);
	pt.put("dot4.LargeDistance",			default_dot4LargeDistance			);
	pt.put("dot4.MinAngle",					default_dot4MinAngle				);
	pt.put("dot4.MaxAngle",					default_dot4MaxAngle				);
	pt.put("dot4.CorrectMiddleDistance",	default_dot4CorrectMiddleDistance	);
	pt.put("dot4.CorrectMiddleLoopCount",	default_dot4CorrectMiddleLoopCount);

	// ５の目処理のパラメータ群
	//pt.put("dot5.", 1);

	// ６の目処理のパラメータ群
	//pt.put("dot6.",1);
	pt.put("dot6.SmallDistance",	default_dot6SmallDistance	);
	pt.put("dot6.MiddleDistance",	default_dot6MiddleDistance);
	pt.put("dot6.LargeDistance",	default_dot6LargeDistance	);
	pt.put("dot6.SmallRadius",		default_dot6SmallRadius	);
	pt.put("dot6.MiddleRadius",		default_dot6MiddleRadius	);
	pt.put("dot6.LargeRadius",		default_dot6LargeRadius	);

	write_ini(name,pt);

}

void DiceDetection::readIniFile(){

	Dir path = Dir();

	// DiceDetection.iniの存在確認
	if(!path.isExist(iniFileName)){
		std::cout << "default_DiceDetection.iniを作成します。" << std::endl;
		std::cout << "DiceDetection.iniを作成してください。" << std::endl;
		defaultIniFileCreate();
		setDefaultParam();
		return;
	}

	//std::cout << iniFileName << std::endl;

	ptree pt;
	read_ini(iniFileName,pt);


	// ファイル関連
	if (boost::optional<string> value = pt.get_optional<string>("file.dir")) {
		dir.cd(value.get());
		//std::cout << "file.dir : " << dir.pwd() << std::endl;
    }
	if (boost::optional<string> value = pt.get_optional<string>("file.name")) {
		name = value.get();
		//std::cout << "file.name : " << name << std::endl;
    }

	
	
	// 全点処理のパラメータ群
	if (boost::optional<int> value = pt.get_optional<int>("allDot.SmallMinSize")) {
		dotSmallMinSize = value.get();
		//std::cout << "allDot.SmallMinSize : " << dotSmallMinSize << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("allDot.SmallMaxSize")) {
		dotSmallMaxSize = value.get();
		//std::cout << "allDot.SmallMaxSize : " << dotSmallMaxSize << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("allDot.MiddleMinSize")) {
		dotMiddleMinSize = value.get();
		//std::cout << "allDot.MiddleMinSize : " << dotMiddleMinSize << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("allDot.MiddleMaxSize")) {
		dotMiddleMaxSize = value.get();
		//std::cout << "allDot.MiddleMaxSize : " << dotMiddleMaxSize << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("allDot.LargeMinSize")) {
		dotLargeMinSize = value.get();
		//std::cout << "allDot.LargeMinSize : " << dotLargeMinSize << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("allDot.LargeMaxSize")) {
		dotLargeMaxSize = value.get();
		//std::cout << "allDot.LargeMaxSize : " << dotLargeMaxSize << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("allDot.NoneMinSize")) {
		dotNoneMinSize = value.get();
		//std::cout << "allDot.NoneMinSize : " << dotNoneMinSize << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("allDot.NoneMaxSize")) {
		dotNoneMaxSize = value.get();
		//std::cout << "allDot.NoneMaxSize : " << dotNoneMaxSize << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("allDot.dot1MinSize")) {
		dot1MinSize = value.get();
		//std::cout << "allDot.dot1MinSize : " << dot1MinSize << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("allDot.dot1MaxSize")) {
		dot1MaxSize = value.get();
		//std::cout << "allDot.dot1MaxSize : " << dot1MaxSize << std::endl;
    }
	if (boost::optional<double> value = pt.get_optional<double>("allDot.CircleFilterPer")) {
		dotCircleFilterPer = value.get();
		//std::cout << "allDot.dotCircleFilterPer : " << dotCircleFilterPer << std::endl;
    }
	if (boost::optional<double> value = pt.get_optional<double>("allDot.CircleFilterRadiusPer")) {
		dotCircleFilterRadiusPer = value.get();
		//std::cout << "allDot.CircleFilterRadiusPer : " << dotCircleFilterRadiusPer << std::endl;
    }

	
	
	// タイプ修正のパラメータ群
	if (boost::optional<double> value = pt.get_optional<double>("correct.MiddleRadius")) {
		correctMiddleRadius = value.get();
		//std::cout << "correct.MiddleRadius : " << correctMiddleRadius << std::endl;
    }
	if (boost::optional<double> value = pt.get_optional<double>("correct.LargeRadius")) {
		correctLargeRadius = value.get();
		//std::cout << "correct.LargeRadius : " << correctLargeRadius << std::endl;
    }
	if (boost::optional<double> value = pt.get_optional<double>("correct.MiddleMaxSize")) {
		correctMiddleMaxSize = value.get();
		//std::cout << "correct.MiddleMaxSize : " << correctMiddleMaxSize << std::endl;
    }
	if (boost::optional<double> value = pt.get_optional<double>("correct.LargeMinSize")) {
		correctLargeMinSize = value.get();
		//std::cout << "correct.LargeMinSize : " << correctLargeMinSize << std::endl;
    }
	
	// 全線分処理のパラメータ群
	if (boost::optional<double> value = pt.get_optional<double>("allLine.SmallRadius")) {
		lineSmallRadius = value.get();
		//std::cout << "allLine.SmallRadius : " << lineSmallRadius << std::endl;
    }
	if (boost::optional<double> value = pt.get_optional<double>("allLine.MiddleRadius")) {
		lineMiddleRadius = value.get();
		//std::cout << "allLine.MiddleRadius : " << lineMiddleRadius << std::endl;
    }
	if (boost::optional<double> value = pt.get_optional<double>("allLine.LargeRadius")) {
		lineLargeRadius = value.get();
		//std::cout << "allLine.LargeRadius : " << lineLargeRadius << std::endl;
    }
	
	
	
	// 全3点処理のパラメータ群
	if (boost::optional<double> value = pt.get_optional<double>("allDot3.Angle")) {
		allDot3Angle = value.get();
		//std::cout << "allDot3.Angle : " << allDot3Angle << std::endl;
    }
	if (boost::optional<double> value = pt.get_optional<double>("allDot3.SmallMinDistance")) {
		allDot3SmallMinDistance = value.get();
		//std::cout << "allDot3.SmallMinDistance : " << allDot3SmallMinDistance << std::endl;
    }
	if (boost::optional<double> value = pt.get_optional<double>("allDot3.MiddleMinDistance")) {
		allDot3MiddleMinDistance = value.get();
		//std::cout << "allDot3.MiddleMinDistance : " << allDot3MiddleMinDistance << std::endl;
    }
	if (boost::optional<double> value = pt.get_optional<double>("allDot3.LargeMinDistance")) {
		allDot3LargeMinDistance = value.get();
		//std::cout << "allDot3.LargeMinDistance : " << allDot3LargeMinDistance << std::endl;
    }
	if (boost::optional<double> value = pt.get_optional<double>("allDot3.SmallMaxDistance")) {
		allDot3SmallMaxDistance = value.get();
		//std::cout << "allDot3.SmallMaxDistance : " << allDot3SmallMaxDistance << std::endl;
    }
	if (boost::optional<double> value = pt.get_optional<double>("allDot3.MiddleMaxDistance")) {
		allDot3MiddleMaxDistance = value.get();
		//std::cout << "allDot3.MiddleMaxDistance : " << allDot3MiddleMaxDistance << std::endl;
    }
	if (boost::optional<double> value = pt.get_optional<double>("allDot3.LargeMaxDistance")) {
		allDot3LargeMaxDistance = value.get();
		//std::cout << "allDot3.LargeMaxDistance : " << allDot3LargeMaxDistance << std::endl;
    }
	
	
	// １の目処理のパラメータ群
	if (boost::optional<double> value = pt.get_optional<double>("dot1.CircleFilterPer")) {
		dot1CircleFilterPer = value.get();
		//std::cout << "dot1.dotCircleFilterPer : " << dot1CircleFilterPer << std::endl;
    }
	if (boost::optional<double> value = pt.get_optional<double>("dot1.CircleFilterRadiusPer")) {
		dot1CircleFilterRadiusPer = value.get();
		//std::cout << "dot1.CircleFilterRadiusPer : " << dot1CircleFilterRadiusPer << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("dot1.LMDetectRadius")) {
		dot1LMDetectRadius = value.get();
		//std::cout << "dot1.LMDetectRadius : " << dot1LMDetectRadius << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("dot1.LMCorrectRadius")) {
		dot1LMCorrectRadius = value.get();
		//std::cout << "dot1.LMCorrectRadius : " << dot1LMCorrectRadius << std::endl;
    }



	// ２の目処理のパラメータ群
	if (boost::optional<int> value = pt.get_optional<int>("dot2.SmallMinDistance")) {
		dot2SmallMinDistance = value.get();
		//std::cout << "dot2.SmallMinDistance : " << dot2SmallMinDistance << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("dot2.MiddleMinDistance")) {
		dot2MiddleMinDistance = value.get();
		//std::cout << "dot2.MiddleMinDistance : " << dot2MiddleMinDistance << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("dot2.LargeMinDistance")) {
		dot2LargeMinDistance = value.get();
		//std::cout << "dot2.LargeMinDistance : " << dot2LargeMinDistance << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("dot2.SmallMaxDistance")) {
		dot2SmallMaxDistance = value.get();
		//std::cout << "dot2.SmallMaxDistance : " << dot2SmallMaxDistance << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("dot2.MiddleMaxDistance")) {
		dot2MiddleMaxDistance = value.get();
		//std::cout << "dot2.MiddleMaxDistance : " << dot2MiddleMaxDistance << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("dot2.LargeMaxDistance")) {
		dot2LargeMaxDistance = value.get();
		//std::cout << "dot2.LargeMaxDistance : " << dot2LargeMaxDistance << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("dot2.SmallDistance")) {
		dot2SmallDistance = value.get();
		//std::cout << "dot2.SmallDistance : " << dot2SmallDistance << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("dot2.MiddleDistance")) {
		dot2MiddleDistance = value.get();
		//std::cout << "dot2.MiddleDistance : " << dot2MiddleDistance << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("dot2.LargeDistance")) {
		dot2LargeDistance = value.get();
		//std::cout << "dot2.LargeDistance : " << dot2LargeDistance << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("dot2.MinAngle")) {
		dot2MinAngle = value.get();
		//std::cout << "dot2.MinAngle : " << dot2MinAngle << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("dot2.MaxAngle")) {
		dot2MaxAngle = value.get();
		//std::cout << "dot2.MaxAngle : " << dot2MaxAngle << std::endl;
    }



	// ４の目処理のパラメータ群
	if (boost::optional<int> value = pt.get_optional<int>("dot4.SmallMinDistance")) {
		dot4SmallMinDistance = value.get();
		//std::cout << "dot4.SmallMinDistance : " << dot4SmallMinDistance << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("dot4.MiddleMinDistance")) {
		dot4MiddleMinDistance = value.get();
		//std::cout << "dot4.MiddleMinDistance : " << dot4MiddleMinDistance << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("dot4.LargeMinDistance")) {
		dot4LargeMinDistance = value.get();
		//std::cout << "dot4.LargeMinDistance : " << dot4LargeMinDistance << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("dot4.SmallMaxDistance")) {
		dot4SmallMaxDistance = value.get();
		//std::cout << "dot4.SmallMaxDistance : " << dot4SmallMaxDistance << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("dot4.MiddleMaxDistance")) {
		dot4MiddleMaxDistance = value.get();
		//std::cout << "dot4.MiddleMaxDistance : " << dot4MiddleMaxDistance << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("dot4.LargeMaxDistance")) {
		dot4LargeMaxDistance = value.get();
		//std::cout << "dot4.LargeMaxDistance : " << dot4LargeMaxDistance << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("dot4.SmallDistance")) {
		dot4SmallDistance = value.get();
		//std::cout << "dot4.SmallDistance : " << dot4SmallDistance << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("dot4.MiddleDistance")) {
		dot4MiddleDistance = value.get();
		//std::cout << "dot4.MiddleDistance : " << dot4MiddleDistance << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("dot4.LargeDistance")) {
		dot4LargeDistance = value.get();
		//std::cout << "dot4.LargeDistance : " << dot4LargeDistance << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("dot4.MinAngle")) {
		dot4MinAngle = value.get();
		//std::cout << "dot4.MinAngle : " << dot4MinAngle << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("dot4.MaxAngle")) {
		dot4MaxAngle = value.get();
		//std::cout << "dot4.MaxAngle : " << dot4MaxAngle << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("dot4.CorrectMiddleDistance")) {
		dot4CorrectMiddleDistance = value.get();
		//std::cout << "dot4.CorrectMiddleDistance : " << dot4CorrectMiddleDistance << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("dot4.CorrectMiddleLoopCount")) {
		dot4CorrectMiddleLoopCount = value.get();
		//std::cout << "dot4.CorrectMiddleLoopCount : " << dot4CorrectMiddleLoopCount << std::endl;
    }

	
	
	// ６の目処理のパラメータ群
	if (boost::optional<int> value = pt.get_optional<int>("dot6.SmallDistance")) {
		dot6SmallDistance = value.get();
		//std::cout << "dot6.SmallDistance : " << dot6SmallDistance << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("dot6.MiddleDistance")) {
		dot6MiddleDistance = value.get();
		//std::cout << "dot6.MiddleDistance : " << dot6MiddleDistance << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("dot6.LargeDistance")) {
		dot6LargeDistance = value.get();
		//std::cout << "dot6.LargeDistance : " << dot6LargeDistance << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("dot6.SmallRadius")) {
		dot6SmallRadius = value.get();
		//std::cout << "dot6.SmallRadius : " << dot6SmallRadius << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("dot6.MiddleRadius")) {
		dot6MiddleRadius = value.get();
		//std::cout << "dot6.MiddleRadius : " << dot6MiddleRadius << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("dot6.LargeRadius")) {
		dot6LargeRadius = value.get();
		//std::cout << "dot6.LargeRadius : " << dot6LargeRadius << std::endl;
    }


}

/******************
 *   実行処理関連
 */

void DiceDetection::run(){
	
	// 検出処理

	std::cout << "点検出" << std::endl;
	getAllPoints();

	std::cout << "1の目検出" << std::endl;
	getDot1Points();

	std::cout << "サイズ修正" << std::endl;
	correctPointType();

	std::cout << "線分検出" << std::endl;
	getAllLines();

	std::cout << "2の目検出" << std::endl;
	getDot2Points();
	
	std::cout << "3点検出" << std::endl;
	getAllDot3Points();

	std::cout << "5の目検出" << std::endl;
	getDot5Points();

	std::cout << "3の目検出" << std::endl;
	getDot3Points();
	
	std::cout << "6の目検出" << std::endl;
	getDot6Points();

	std::cout << "4の目検出" << std::endl;
	_getDot4Points();

	std::cout << "余り点検出" << std::endl;
	//getOddPoints();

	std::cout << "中心点検出" << std::endl;
	getAllDotCenters();


	// 描写と修正処理	
	drawRun();

}

void DiceDetection::drawing(){
	
	while(keyEvent(cv::waitKey(30))){
		// 余り点の描写
		//drawMousePoint(odds,"OddPoint");

		// 目の種類ごとの描写
		drawMousePoint(types,"AllDots");

		// サイコロサイズごとの描写
		drawMousePoint(kinds,"Types");
		
		//cv::setMouseCallback("OddPoint", onMouseOdd, this);
		cv::setMouseCallback("AllDots", onMouse, this);
		cv::setMouseCallback("Types", onMouse, this);

	}
}

void DiceDetection::draw(){
	// 
	drawMousePoint(src,"src");

	// 目の種類ごとの描写
	drawMousePoint(types,"AllDots");

	// サイコロサイズごとの描写
	drawMousePoint(kinds,"Types");
		
	cv::setMouseCallback("src", onMouse, this);
	cv::setMouseCallback("AllDots", onMouse, this);
	cv::setMouseCallback("Types", onMouse, this);
}

void DiceDetection::setMode(int key){
	keyEvent(key);
}

int DiceDetection::getPacket() const{
	return getNumDot1Points(DiceInfo::small);
}

int DiceDetection::getMode() const{
	return modeFlag;
}

int DiceDetection::getModeKind() const{
	return mode.kind;
}

int DiceDetection::getModeType() const{
	return mode.type;
}

void DiceDetection::testRun(){
	
	Image alldot,allline,alldot3,correct;
	Image types,kinds;
	Timer timer;
	Image draw;

	std::cout << "開始 : " << std::flush;
	std::cout << 0 << std::endl;
	
	timer.start();
	
	// 画像初期化
	std::cout << "画像初期化 : " << std::flush;
		alldot.clone(src);
		allline.clone(src);
		alldot3.clone(src);
		correct.clone(src);
		types.clone(src);
		kinds.clone(src);
	std::cout << (double)timer.getDiff()/Timer::PER_SEC << std::endl;
	timer.lap();
	

	std::cout << "点検出 : " << std::flush;
	getAllPoints();
	std::cout << (double)timer.getDiff()/Timer::PER_SEC << std::endl;
	timer.lap();

	
	draw.clone(src);
	drawTypePoints(draw,DiceInfo::none,cv::Scalar(255,0,0));
	drawTypePoints(draw,DiceInfo::small,cv::Scalar(0,0,255));
	drawTypePoints(draw,DiceInfo::middle,cv::Scalar(0,255,0));
	drawTypePoints(draw,DiceInfo::large,cv::Scalar(255,255,255));
	draw.imshow("allDots");
	
	std::cout << "1の目検出 : " << std::flush;
	getDot1Points();
	std::cout << (double)timer.getDiff()/Timer::PER_SEC << std::endl;
	timer.lap();
	
	alldot.clone(src);
	drawDot1Points(alldot,cv::Scalar(0,255,0));
	alldot.imshow("all1dot");


	std::cout << "サイズ修正 : " << std::flush;
	correctPointType();
	std::cout << (double)timer.getDiff()/Timer::PER_SEC << std::endl;
	timer.lap();

	draw.clone(src);
	drawTypePoints(draw,DiceInfo::none,cv::Scalar(255,0,0));
	drawTypePoints(draw,DiceInfo::small,cv::Scalar(0,0,255));
	drawTypePoints(draw,DiceInfo::middle,cv::Scalar(0,255,0));
	drawTypePoints(draw,DiceInfo::large,cv::Scalar(255,255,255));
	draw.imshow("correct");
	
	std::cout << "線分検出 : " << std::flush;
	getAllLines();
	alldot.clone(src);
	drawAllLine(alldot,cv::Scalar(0,255,0),cv::Scalar(255,0,0));
	alldot.imshow("allline");
	std::cout << (double)timer.getDiff()/Timer::PER_SEC << std::endl;
	timer.lap();

	std::cout << "2の目検出 : " << std::flush;
	getDot2Points();
	std::cout << (double)timer.getDiff()/Timer::PER_SEC << std::endl;
	timer.lap();

	draw.clone(src);
	drawDot2Points(draw,cv::Scalar(0,0,255),cv::Scalar(0,0,255));
	drawDot2Center(draw,cv::Scalar(255,0,0));
	draw.imshow("dot2");


	std::cout << "3点検出 : " << std::flush;
	getAllDot3Points();
	std::cout << (double)timer.getDiff()/Timer::PER_SEC << std::endl;
	timer.lap();



	std::cout << "5の目検出 : " << std::flush;
	getDot5Points();
	std::cout << (double)timer.getDiff()/Timer::PER_SEC << std::endl;
	timer.lap();

	std::cout << "3の目検出 : " << std::flush;
	getDot3Points();
	std::cout << (double)timer.getDiff()/Timer::PER_SEC << std::endl;
	timer.lap();

	std::cout << "6の目検出 : " << std::flush;
	getDot6Points();
	std::cout << (double)timer.getDiff()/Timer::PER_SEC << std::endl;
	timer.lap();

	std::cout << "4の目検出 : " << std::flush;
	_getDot4Points();
	std::cout << (double)timer.getDiff()/Timer::PER_SEC << std::endl;
	timer.lap();

	std::cout << "余り点検出 : " << std::flush;
	getOddPoints();
	std::cout << (double)timer.getDiff()/Timer::PER_SEC << std::endl;
	timer.lap();

	std::cout << "中心点検出 : " << std::flush;
	getAllDotCenters();
	std::cout << (double)timer.getDiff()/Timer::PER_SEC << std::endl;
	timer.lap();


	// 描写
	draw.clone(src);

	// 余り点の描写
	drawTruePoints(draw,cv::Scalar(255,0,0));
	drawTypePoints(draw,DiceInfo::none,cv::Scalar(0,0,255));
	draw.imshow("OddPoints");
	draw.clone(src);

	// 目の種類ごとの描写
	drawDot1Points(draw,cv::Scalar(255,255,255));
	drawDot2Points(draw,cv::Scalar(0,0,255),cv::Scalar(0,0,255));
	drawDot2Center(draw,cv::Scalar(255,0,0));
	drawDot3Points(draw,cv::Scalar(0,255,0),cv::Scalar(0,0,255));
	drawDot3Center(draw,cv::Scalar(255,0,0));
	drawDot4Points(draw,cv::Scalar(255,255,0),cv::Scalar(0,0,255));
	drawDot4Center(draw,cv::Scalar(255,0,0));
	drawDot5Points(draw,cv::Scalar(255,0,255),cv::Scalar(0,0,255));
	drawDot5Center(draw,cv::Scalar(255,0,0));
	drawDot6Points(draw,cv::Scalar(0,255,255),cv::Scalar(0,0,255));
	drawDot6Center(draw,cv::Scalar(255,0,0));
	draw.imshow("AllDots");
	draw.clone(src);

	// サイコロサイズごとの描写
	drawTypePoints(draw,DiceInfo::none,cv::Scalar(255,0,0));
	drawTypePoints(draw,DiceInfo::small,cv::Scalar(0,0,255));
	drawTypePoints(draw,DiceInfo::middle,cv::Scalar(0,255,0));
	drawTypePoints(draw,DiceInfo::large,cv::Scalar(255,255,255));
	draw.imshow("Types");
	draw.clone(src);

	cv::waitKey(0);


}

void DiceDetection::drawRun(){
		
	types.clone(src);
	kinds.clone(src);

	drawDot1Points(types,cv::Scalar(255,100,100));
	drawDot2Points(types,cv::Scalar(0,0,255),cv::Scalar(0,0,255));
	drawDot2Center(types,cv::Scalar(255,0,0));
	drawDot3Points(types,cv::Scalar(0,255,0),cv::Scalar(0,0,255));
	drawDot3Center(types,cv::Scalar(255,0,0));
	drawDot4Points(types,cv::Scalar(255,255,0),cv::Scalar(0,0,255));
	drawDot4Center(types,cv::Scalar(255,0,0));
	drawDot5Points(types,cv::Scalar(255,0,255),cv::Scalar(0,0,255));
	drawDot5Center(types,cv::Scalar(255,0,0));
	drawDot6Points(types,cv::Scalar(0,255,255),cv::Scalar(0,0,255));
	drawDot6Center(types,cv::Scalar(255,0,0));
	
	//drawTruePoints(odds,cv::Scalar(255,0,0));
	//drawTypePoints(odds,DiceInfo::none,cv::Scalar(0,0,255));
	
	//drawTypePoints(kinds,DiceInfo::none,cv::Scalar(0,200,200));
	//drawTypePoints(kinds,DiceInfo::small,cv::Scalar(0,0,255));
	//drawTypePoints(kinds,DiceInfo::middle,cv::Scalar(100,200,0));
	//drawTypePoints(kinds,DiceInfo::large,cv::Scalar(255,0,0));

	//drawKindAllDotCenters(kinds,1,cv::Scalar(255,255,255));
	//drawKindAllDotCenters(kinds,2,cv::Scalar(0,0,255));
	//drawKindAllDotCenters(kinds,3,cv::Scalar(0,255,0));
	//drawKindAllDotCenters(kinds,4,cv::Scalar(255,255,0));
	//drawKindAllDotCenters(kinds,5,cv::Scalar(255,0,255));
	//drawKindAllDotCenters(kinds,6,cv::Scalar(0,255,255));

	drawTypeDot1Points(kinds,DiceInfo::none,cv::Scalar(0,200,200));
	drawTypeDot2Points(kinds,DiceInfo::none,cv::Scalar(0,200,200));
	drawTypeDot3Points(kinds,DiceInfo::none,cv::Scalar(0,200,200));
	drawTypeDot4Points(kinds,DiceInfo::none,cv::Scalar(0,200,200));
	drawTypeDot5Points(kinds,DiceInfo::none,cv::Scalar(0,200,200));
	drawTypeDot6Points(kinds,DiceInfo::none,cv::Scalar(0,200,200));
	
	drawTypeDot1Points(kinds,DiceInfo::small,cv::Scalar(0,255,255));
	drawTypeDot2Points(kinds,DiceInfo::small,cv::Scalar(0,255,255));
	drawTypeDot3Points(kinds,DiceInfo::small,cv::Scalar(0,255,255));
	drawTypeDot4Points(kinds,DiceInfo::small,cv::Scalar(0,255,255));
	drawTypeDot5Points(kinds,DiceInfo::small,cv::Scalar(0,255,255));
	drawTypeDot6Points(kinds,DiceInfo::small,cv::Scalar(0,255,255));
	
	drawTypeDot1Points(kinds,DiceInfo::middle,cv::Scalar(100,200,0));
	drawTypeDot2Points(kinds,DiceInfo::middle,cv::Scalar(100,200,0));
	drawTypeDot3Points(kinds,DiceInfo::middle,cv::Scalar(100,200,0));
	drawTypeDot4Points(kinds,DiceInfo::middle,cv::Scalar(100,200,0));
	drawTypeDot5Points(kinds,DiceInfo::middle,cv::Scalar(100,200,0));
	drawTypeDot6Points(kinds,DiceInfo::middle,cv::Scalar(100,200,0));
	
	drawTypeDot1Points(kinds,DiceInfo::large,cv::Scalar(255,0,255));
	drawTypeDot2Points(kinds,DiceInfo::large,cv::Scalar(255,0,255));
	drawTypeDot3Points(kinds,DiceInfo::large,cv::Scalar(255,0,255));
	drawTypeDot4Points(kinds,DiceInfo::large,cv::Scalar(255,0,255));
	drawTypeDot5Points(kinds,DiceInfo::large,cv::Scalar(255,0,255));
	drawTypeDot6Points(kinds,DiceInfo::large,cv::Scalar(255,0,255));


}

void DiceDetection::drawMousePoint(Image& src,string winName){
	Image dst;
	src.imshow(winName);
	dst.clone(src);
	if(modeFlag==0)
		dst.circle(cv::Point(x,y),10,cv::Scalar(0,200,255));
	else if(modeFlag == 1)
		dst.circle(cv::Point(x,y),10,cv::Scalar(0,0,255));
	else if(modeFlag == 2)
		dst.circle(cv::Point(x,y),10,cv::Scalar(100,255,0));
	dst.imshow(winName);
}

void DiceDetection::outRun(){
	std::ofstream ofs;
	ofs.open("DiceDetectionCenters.txt");
	ofs << allDotCenters.size() << std::endl;
	for(int i=0;i<allDotCenters.size();i++){
		if(allDotCenters.types[i] == DiceInfo::none) continue;
		ofs << allDotCenters.centers[i].pt.x << " "
			<< allDotCenters.centers[i].pt.y << " "
			<< allDotCenters.types[i] << " "
			<< allDotCenters.kinds[i] << " "
			<< std::endl;
	}
	ofs.close();
}

void DiceDetection::outEncode(){
	cv::Size size = src.size();
	int dotSize;
	DotPoint leftUpDot;
	DiceInfo::dtype leftUpType;
	DiceInfo::dtype now_type;
	bool flag = false;
	vector<int> nums;

	// ファイル名の決定パケット番号付与
	// 小サイコロの1の目の数を取得
	int packetNum = getNumDot1Points(DiceInfo::small);
	std::ofstream ofs;
	std::stringstream ss;
	ss << "DiceToDecode_" << packetNum << ".txt";
	//std::cout<<dir.pwd(ss.str())<<std::endl;
	ofs.open(dir.pwd(ss.str()));

	// 検索開始枠を決める
	int xmin=size.width,xmax=0,ymin=size.height,ymax=0;
	for(int i=0;i<allDotCenters.size();i++){
		if(allDotCenters.centers[i].pt.x < xmin) xmin = allDotCenters.centers[i].pt.x;
		if(allDotCenters.centers[i].pt.x > xmax) xmax = allDotCenters.centers[i].pt.x;
		if(allDotCenters.centers[i].pt.y < ymin) ymin = allDotCenters.centers[i].pt.y;
		if(allDotCenters.centers[i].pt.y > ymax) ymax = allDotCenters.centers[i].pt.y;
	}
	
	// 左上の最初の点を検出
	for(int x=xmin;x<=xmax;x++){
		for(int y=ymin;y<=ymax;y++){
			for(int i=0;i<allDotCenters.size();i++){
				if(Calc::getDistance2(allDotCenters[i],cv::Point2f(x,y))<allDotCenters.centers[i].size/CV_PI){
					leftUpDot.init(allDotCenters[i],allDotCenters.centers.size());
					leftUpType = allDotCenters.types[i];
					flag = true;
				}
				if(flag) break;
			}
			if(flag) break;
		}
		if(flag) break;
	}

	
	
	// 他の点を順番に並べる
	if(leftUpType == DiceInfo::small){
		// 右上から
		for(int x=xmax;x>=xmin;x--){
			for(int y=ymin;y<=ymax;y++){
				for(int i=0;i<allDotCenters.size();i++){
					flag = true;
					for(int j=0;j<nums.size();j++){
						if(i==nums[j]) flag=false;
					}
					if(!flag) continue;
					if(allDotCenters.types[i]==DiceInfo::small) dotSize = 50;
					else if(allDotCenters.types[i]==DiceInfo::middle) dotSize = 1000;
					else if(allDotCenters.types[i]==DiceInfo::large) dotSize = 3000;
					else dotSize = 0;
					if(Calc::getDistance2(allDotCenters[i],cv::Point2f(x,y))<dotSize/CV_PI){
						if(allDotCenters.types[i] != DiceInfo::small &&
							allDotCenters.types[i] != DiceInfo::none){
							x=allDotCenters.centers[i].pt.x;
							now_type = allDotCenters.types[i];
							for(int y=ymin;y<=ymax;y++){
								for(int i=0;i<allDotCenters.size();i++){
									if(now_type!=allDotCenters.types[i]) continue;
									if(Calc::getDistance2(allDotCenters[i],cv::Point2f(x,y))<dotSize){
										flag = true;
										for(int j=0;j<nums.size();j++){
											if(i==nums[j]) flag=false;
										}
										if(!flag) continue;
										ofs << allDotCenters.kinds[i] << " " << std::flush;
										//std::cout << x << "," << y << "," << allDotCenters.kinds[i] <<"," << allDotCenters.types[i] << std::endl;
										nums.push_back(i);
									}
								}
							}
							ofs<<std::endl;
						}
					}
				}
			}
		}
	}else{
		// 左下から
		for(int x=xmin;x<=xmax;x++){
			for(int y=ymax;y>=ymin;y--){
				for(int i=0;i<allDotCenters.size();i++){
					flag = true;
					for(int j=0;j<nums.size();j++){
						if(i==nums[j]) flag=false;
					}
					if(!flag) continue;
					if(allDotCenters.types[i]==DiceInfo::small) dotSize = 50;
					else if(allDotCenters.types[i]==DiceInfo::middle) dotSize = 1000;
					else if(allDotCenters.types[i]==DiceInfo::large) dotSize = 3000;
					else dotSize = 0;
					if(Calc::getDistance2(allDotCenters[i],cv::Point2f(x,y))<dotSize/CV_PI){
						if(allDotCenters.types[i] != DiceInfo::small &&
							allDotCenters.types[i] != DiceInfo::none){
							x=allDotCenters.centers[i].pt.x;
							now_type = allDotCenters.types[i];
							for(int y=ymax;y>=ymin;y--){
								for(int i=0;i<allDotCenters.size();i++){
									if(now_type!=allDotCenters.types[i]) continue;
									if(Calc::getDistance2(allDotCenters[i],cv::Point2f(x,y))<dotSize){
										flag = true;
										for(int j=0;j<nums.size();j++){
											if(i==nums[j]) flag=false;
										}
										if(!flag) continue;
										ofs << allDotCenters.kinds[i] << " " << std::flush;
										//std::cout << x << "," << y << "," << allDotCenters.kinds[i] <<"," << allDotCenters.types[i] << std::endl;
										nums.push_back(i);
									}
								}
							}
							ofs<<std::endl;
						}
					}
				}
			}
		}
	}

	ofs.close();

}


}