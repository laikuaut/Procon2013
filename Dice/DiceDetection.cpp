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
 *   クラスDot3Points
 */

DiceDetection::Dot3Points::Dot3Points(){
	num = 0;
}

void DiceDetection::Dot3Points::add(Dot3Point dot3,short flag,DiceInfo::dtype type,int kind,int dotNum1,int dotNum2,int dotNum3){
	dot3s.push_back(dot3);
	flags.push_back(flag);
	types.push_back(type);
	kinds.push_back(kind);
	dotNums[0].push_back(dotNum1);
	dotNums[1].push_back(dotNum2);
	dotNums[2].push_back(dotNum3);
	num++;
}

int DiceDetection::Dot3Points::size() const{
	return num;
}

Dot3Point DiceDetection::Dot3Points::operator[](int i){
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
	num=0;
}

void DiceDetection::DotCenters::add(DotPoint center,DiceInfo::dtype type,int kind){
	centers.push_back(center);
	types.push_back(type);
	kinds.push_back(kind);
	num++;
}

int DiceDetection::DotCenters::size() const{
	return num;
}

DotPoint DiceDetection::DotCenters::operator[](int i){
	return centers[i];
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
			//if(Calc::getDistance2(dot2Points[i].dot[0],dot2Points[j].dot[0]) < dot2Points[j].dot[0].size/CV_PI){
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
		allDotCenters.add(dot1Points[i],dot1Points[i].type,1);
	for(int i=0;i<dot2Points.size();i++)
		allDotCenters.add(dot2Points[i].center,dot2Points[i].type,2);
	for(int i=0;i<dot3Points.size();i++)
		allDotCenters.add(dot3Points[i].center,dot3Points[i].type,3);
	for(int i=0;i<dot4Points.size();i++)
		allDotCenters.add(dot4Points[i].center,dot4Points[i].type,4);
	for(int i=0;i<dot5Points.size();i++)
		allDotCenters.add(dot5Points[i].center,dot5Points[i].type,5);
	for(int i=0;i<dot6Points.size();i++)
		allDotCenters.add(dot6Points[i].center,dot6Points[i].type,6);	
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
	lc.circleFilter(dot1CircleFilterPer,dot1CircleFilterRadiusPer);
	lc.sizeFilter(dot1MinSize,dot1MaxSize);

	Dot1Point dot1;
	vector<int> dot1Num;

	// 1の目の点登録
	for(int i=0;i<lc.num;i++){
		if(!lc.flags[i]) continue;
		for(int j=0;j<allPoints.size();j++){
			if(Calc::getDistance2(allPoints[j],lc(i)) < allPoints[j].size/CV_PI){
				dot1.init(lc(i),lc.sizes[i]);
				dot1Points.push_back(dot1);
				allPoints.flags[j] = 0;
				allPoints.kinds[j] = 1;
				dot1Num.push_back(j);
				
			}
		}
	}

	// 点群から1の目の削除
	//eraseDot1Points();

	for(int j=0;j<dot1Points.size();j++){
		if(allPoints.types[dot1Num[j]] == DiceInfo::large){
			allPoints.types[dot1Num[j]] = DiceInfo::small;
			dot1Points[j].type = DiceInfo::small;
		}
	}


	// サイコロの大中判別
	for(int j=0;j<dot1Points.size();j++){
		if(dot1Points[j].type!=DiceInfo::none)	continue;
		//else if(flag) continue;
		for(int i=0;i<allPoints.size();i++){
			//if(!allPoints.flags[i]) continue;
			if(i==dot1Num[j]) continue;

			if(Calc::getDistance2(allPoints[i],dot1Points[j]) < pow(dot1LMDetectRadius,2)){
				if(allPoints.types[i] == DiceInfo::middle || allPoints.kinds[i]==1){
					dot1Points[j].type = DiceInfo::middle;
					allPoints.types[dot1Num[j]] = DiceInfo::middle;
					break;
				}
			}
		}
		if(dot1Points[j].type==DiceInfo::none){
			dot1Points[j].type = DiceInfo::large;
			allPoints.types[dot1Num[j]] = DiceInfo::large;
		}
	}

	// 確認
	//Image draw;
	//draw.clone(src);
	//drawTypePoints(draw,DiceInfo::none,cv::Scalar(255,0,0));
	////drawTypePoints(draw,DiceInfo::small,red);
	////drawTypePoints(draw,DiceInfo::middle,green);
	////drawTypePoints(draw,DiceInfo::large,white);
	//draw.imshow("test");
	//cv::waitKey(0);




	// さらに大サイコロと誤認した中サイコロの修正
	for(int i=0;i<dot1Points.size();i++){
		if(dot1Points[i].type != DiceInfo::large) continue;
		for(int j=0;j<dot1Points.size();j++){
			if(dot1Points[j].type == DiceInfo::middle){
				if(Calc::getDistance2(dot1Points[i],dot1Points[j])<pow(dot1LMCorrectRadius,2)){
					dot1Points[i].type = DiceInfo::middle;
					allPoints.types[dot1Num[i]] = DiceInfo::middle;
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
					dot2Points.push_back(dot2);
					
					allPoints.flags[dot1Nums[i]] = 0;
					allPoints.kinds[dot1Nums[i]] = 2;
					allPoints.flags[dot1Nums[j]] = 0;
					allPoints.kinds[dot1Nums[j]] = 2;
					break;
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
				dot4Points.push_back(dot4);
				lsegs.flags[i] = 0;
				lsegs.flags[j] = 0;
				for(int k=0;k<2;k++){
					allPoints.flags[lsegs.dotNums[k][i]] = 0;
					allPoints.kinds[lsegs.dotNums[k][i]] = 4;
					allPoints.flags[lsegs.dotNums[k][j]] = 0;
					allPoints.kinds[lsegs.dotNums[k][j]] = 4;
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
					
					//for(int l=0;l<missDotCenters.size();l++){
					//	if(dot4.type == DiceInfo::middle && Calc::getDistance2(missDotCenters[l],dot4.center) < dot4.center.size/CV_PI)
					//		flag = false;
					//}
					//if(flag){

					dot4Points.push_back(dot4);
					lsegs.flags[i] = 0;
					lsegs.flags[j] = 0;
					for(int k=0;k<2;k++){
						allPoints.flags[lsegs.dotNums[k][i]] = 0;
						allPoints.kinds[lsegs.dotNums[k][i]] = 4;
						allPoints.flags[lsegs.dotNums[k][j]] = 0;
						allPoints.kinds[lsegs.dotNums[k][j]] = 4;
					//	}
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
		for(int j=i+1;j<allDot3Points.size();j++){
			if(i==j) continue;
			if(allDot3Points.types[i] != allDot3Points.types[i]) continue;
			if(Calc::getDistance2(allDot3Points[i].center,allDot3Points[j].center) < allDot3Points[i].center.size/CV_PI){
				dot5.init(allDot3Points[i],allDot3Points[j],allDot3Points.types[i]);
				dot5Points.push_back(dot5);
				
				allDot3Points.flags[i] = 0;
				allDot3Points.flags[j] = 0;
				
				for(int k=0;k<3;k++){
					allPoints.flags[allDot3Points.dotNums[k][i]] = 0;
					allPoints.kinds[allDot3Points.dotNums[k][i]] = 5;
					allPoints.flags[allDot3Points.dotNums[k][j]] = 0;
					allPoints.kinds[allDot3Points.dotNums[k][j]] = 5;
				}
				break;
			}
		}
	}
}

void DiceDetection::getDot3Points(){
	Dot3Point dot3;
	for(int i=0;i<allDot3Points.size();i++){
		if(!allDot3Points.flags[i]) continue;
		if(35<allDot3Points[i].angle && allDot3Points[i].angle<55){
			dot3Points.push_back(allDot3Points[i]);
			allDot3Points.flags[i]=0;
			for(int k=0;k<3;k++){
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
				dot6Points.push_back(dot6);
				allDot3Points.flags[i] = 0;
				allDot3Points.flags[j] = 0;
				for(int k=0;k<3;k++){
					allPoints.flags[allDot3Points.dotNums[k][i]] = 0;
					allPoints.kinds[allDot3Points.dotNums[k][i]] = 6;
					allPoints.flags[allDot3Points.dotNums[k][j]] = 0;
					allPoints.kinds[allDot3Points.dotNums[k][j]] = 6;
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
 *   サイコロの目厳選削除
 */

void DiceDetection::eraseDot1Points(){
	
	vector<int> dot1Num;
	//vector<int> dot1FlaseNum;
	//bool flag;
	// 点群から１の目削除
	for(int j=0;j<dot1Points.size();j++){
		//flag = true;
		for(int i=0;i<allPoints.size();i++){
			//int radius = allPoints[i].size;
			//if(radius<dot1Points[j].size) radius = dot1Points[j].size;
			//if(Calc::getDistance2(allPoints[i],dot1Points[j]) < radius/CV_PI){
			if(allPoints.kinds[i] == 1){
				dot1Num.push_back(i);
				//flag = false;
				if(allPoints.types[i] == DiceInfo::large){
					allPoints.types[i] = DiceInfo::small;
					dot1Points[j].type = DiceInfo::small;
				}
				break;
			}
		}
	}

	// サイコロの大中判別
	for(int j=0;j<dot1Points.size();j++){
		if(dot1Points[j].type!=DiceInfo::none)	continue;
		//else if(flag) continue;
		for(int i=0;i<allPoints.size();i++){
			//if(!allPoints.flags[i]) continue;
			if(i==dot1Num[j]) continue;
			if(Calc::getDistance2(allPoints[i],dot1Points[j]) < pow(dot1LMDetectRadius,2)){
				if(allPoints.types[i] == DiceInfo::middle || allPoints.kinds[i]==1){
					dot1Points[j].type = DiceInfo::middle;
					allPoints.types[dot1Num[j]] = DiceInfo::middle;
					break;
				}
			}
		}
		if(dot1Points[j].type==DiceInfo::none){
			dot1Points[j].type = DiceInfo::large;
			allPoints.types[dot1Num[j]] = DiceInfo::large;
		}
	}

	// 確認
	//Image draw;
	//draw.clone(src);
	//drawTypePoints(draw,DiceInfo::none,cv::Scalar(255,0,0));
	////drawTypePoints(draw,DiceInfo::small,red);
	////drawTypePoints(draw,DiceInfo::middle,green);
	////drawTypePoints(draw,DiceInfo::large,white);
	//draw.imshow("test");
	//cv::waitKey(0);




	// さらに大サイコロと誤認した中サイコロの修正
	for(int i=0;i<dot1Points.size();i++){
		if(dot1Points[i].type != DiceInfo::large) continue;
		for(int j=0;j<dot1Points.size();j++){
			if(dot1Points[j].type == DiceInfo::middle){
				if(Calc::getDistance2(dot1Points[i],dot1Points[j])<pow(dot1LMCorrectRadius,2)){
					dot1Points[i].type = DiceInfo::middle;
					allPoints.types[dot1Num[i]] = DiceInfo::middle;
					break;
				}
			}
		}
	}
}

void DiceDetection::clearAllLines(){
	allLines.clear();
}

void DiceDetection::clearAllDotCenters(){
	allDotCenters.clear();
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

	std::cout<<"missNum:"<<missNum<<std::endl;
	std::cout<<"missDotCenters Num:"<<missDotCenters.size()<<std::endl;

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
				missDotCenters.add(allDotCenters[i],DiceInfo::middle,4);
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
			dot1Points[i].draw(img,scal);
	}
}

void DiceDetection::drawTypeDot1Points(Image& img,DiceInfo::dtype type,cv::Scalar scal){
	for(int i=0;i<dot1Points.size();i++){	
		if(dot1Points[i].type == type)
			dot1Points[i].draw(img,scal);
	}
}

void DiceDetection::drawDot2Points(Image& img,cv::Scalar dot_col,cv::Scalar line_col,int thickness){
	for(int i=0;i<dot2Points.size();i++){
		dot2Points[i].draw(img,dot_col,line_col,thickness);
	}
}

void DiceDetection::drawTypeDot2Points(Image& img,DiceInfo::dtype type,cv::Scalar dot_col,cv::Scalar line_col,int thickness){
	for(int i=0;i<dot2Points.size();i++){
		if(dot2Points[i].type == type)
			dot2Points[i].draw(img,dot_col,line_col,thickness);
	}
}

void DiceDetection::drawDot2Center(Image& img,cv::Scalar scal){
	for(int i=0;i<dot2Points.size();i++){
		dot2Points[i].drawCenter(img,scal);
	}
}

void DiceDetection::drawDot4Points(Image& img,cv::Scalar dot_col,cv::Scalar line_col,int thickness){
	for(int i=0;i<dot4Points.size();i++){
		dot4Points[i].draw(img,dot_col,line_col,thickness);
	}
}

void DiceDetection::drawTypeDot4Points(Image& img,DiceInfo::dtype type,cv::Scalar dot_col,cv::Scalar line_col,int thickness){
	for(int i=0;i<dot4Points.size();i++){
		if(dot4Points[i].type == type)
			dot4Points[i].draw(img,dot_col,line_col,thickness);
	}
}

void DiceDetection::drawDot4Center(Image& img,cv::Scalar scal){
	for(int i=0;i<dot4Points.size();i++){
		dot4Points[i].drawCenter(img,scal);
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
		dot5Points[i].draw(img,dot_col,line_col,thickness);
	}
}

void DiceDetection::drawTypeDot5Points(Image& img,DiceInfo::dtype type,cv::Scalar dot_col,cv::Scalar line_col,int thickness){
	for(int i=0;i<dot5Points.size();i++){
		if(dot5Points[i].type == type)
			dot5Points[i].draw(img,dot_col,line_col,thickness);
	}
}

void DiceDetection::drawDot5Center(Image& img,cv::Scalar scal){
	for(int i=0;i<dot5Points.size();i++){
		dot5Points[i].drawCenter(img,scal);
	}
}

void DiceDetection::drawDot3Points(Image& img,cv::Scalar dot_col,cv::Scalar line_col,int thickness){
	for(int i=0;i<dot3Points.size();i++){
		dot3Points[i].draw(img,dot_col,line_col,thickness);
	}
}

void DiceDetection::drawTypeDot3Points(Image& img,DiceInfo::dtype type,cv::Scalar dot_col,cv::Scalar line_col,int thickness){
	for(int i=0;i<dot3Points.size();i++){
		if(dot3Points[i].type == type)
			dot3Points[i].draw(img,dot_col,line_col,thickness);
	}
}

void DiceDetection::drawDot3Center(Image& img,cv::Scalar scal){
	for(int i=0;i<dot3Points.size();i++){
		dot3Points[i].drawCenter(img,scal);
	}
}

void DiceDetection::drawDot6Points(Image& img,cv::Scalar dot_col,cv::Scalar line_col,int thickness){
	for(int i=0;i<dot6Points.size();i++){
		dot6Points[i].draw(img,dot_col,line_col,thickness);
	}
}

void DiceDetection::drawTypeDot6Points(Image& img,DiceInfo::dtype type,cv::Scalar dot_col,cv::Scalar line_col,int thickness){
	for(int i=0;i<dot6Points.size();i++){
		if(dot6Points[i].type == type)
			dot6Points[i].draw(img,dot_col,line_col,thickness);
	}
}

void DiceDetection::drawDot6Center(Image& img,cv::Scalar scal){
	for(int i=0;i<dot6Points.size();i++){
		dot6Points[i].drawCenter(img,scal);
	}
}

void DiceDetection::drawAllDotCenters(Image& img,cv::Scalar scal){
	for(int i=0;i<allDotCenters.size();i++){
		allDotCenters[i].draw(img,scal);
	}
}

void DiceDetection::drawTypeAllDotCenters(Image& img,DiceInfo::dtype type,cv::Scalar scal){
	for(int i=0;i<allDotCenters.size();i++){
		if(allDotCenters.types[i] == type)
			allDotCenters[i].draw(img,scal);
	}
}

void DiceDetection::drawKindAllDotCenters(Image& img,int kind,cv::Scalar scal){
	for(int i=0;i<allDotCenters.size();i++){
		if(allDotCenters.kinds[i] == kind)
			allDotCenters[i].draw(img,scal);
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
		if(dot1Points[i].type == type) count++;
	}
	return count;
}

int DiceDetection::getNumDot2Points(DiceInfo::dtype type) const{
	int count = 0;
	if(type == DiceInfo::none) 
		return dot2Points.size();
	for(int i=0;i<dot2Points.size();i++){
		if(dot2Points[i].type == type) count++;
	}
	return count;
}

int DiceDetection::getNumDot3Points(DiceInfo::dtype type) const{
	int count = 0;
	if(type == DiceInfo::none) 
		return dot3Points.size();
	for(int i=0;i<dot3Points.size();i++){
		if(dot3Points[i].type == type) count++;
	}
	return count;
}

int DiceDetection::getNumDot4Points(DiceInfo::dtype type) const{
	int count = 0;
	if(type == DiceInfo::none) 
		return dot4Points.size();
	for(int i=0;i<dot4Points.size();i++){
		if(dot4Points[i].type == type) count++;
	}
	return count;
}

int DiceDetection::getNumDot5Points(DiceInfo::dtype type) const{
	int count = 0;
	if(type == DiceInfo::none) 
		return dot5Points.size();
	for(int i=0;i<dot5Points.size();i++){
		if(dot5Points[i].type == type) count++;
	}
	return count;
}

int DiceDetection::getNumDot6Points(DiceInfo::dtype type) const{
	int count = 0;
	if(type == DiceInfo::none) 
		return dot6Points.size();
	for(int i=0;i<dot6Points.size();i++){
		if(dot6Points[i].type == type) count++;
	}
	return count;
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
	
	
	std::cout << "点検出" << std::endl;
	getAllPoints();

	std::cout << "1の目検出" << std::endl;
	getDot1Points();

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
	getOddPoints();

	std::cout << "中心点検出" << std::endl;
	getAllDotCenters();

	// 描写
	Image draw;
	draw.clone(src);

	// 余り点の描写
	drawTruePoints(draw,cv::Scalar(255,0,0));
	drawTypePoints(draw,DiceInfo::none,cv::Scalar(0,0,255));
	cv::namedWindow("OddPoints",0);
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
	cv::namedWindow("AllDots",0);
	draw.imshow("AllDots");
	draw.clone(src);

	// サイコロサイズごとの描写
	drawTypePoints(draw,DiceInfo::none,cv::Scalar(255,0,0));
	drawTypePoints(draw,DiceInfo::small,cv::Scalar(0,0,255));
	drawTypePoints(draw,DiceInfo::middle,cv::Scalar(0,255,0));
	drawTypePoints(draw,DiceInfo::large,cv::Scalar(255,255,255));
	cv::namedWindow("Types",0);
	draw.imshow("Types");
	draw.clone(src);

	cv::waitKey(0);
}






}