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
	lc.circleFilter(1,2);
	lc.sizeFilter(dotSmallMinSize,dotSmallMaxSize);
	for(int i=0;i<lc.num;i++){
		if(lc.flags[i]){
			dot.init(lc(i),lc.sizes[i]);
			allPoints.add(dot,1,DiceInfo::small,0);
		}
	}
	lc.filterReset();

	// 中サイコロ
	lc.circleFilter(1,2);
	lc.sizeFilter(dotMiddleMinSize,dotMiddleMaxSize);
	for(int i=0;i<lc.num;i++){
		if(lc.flags[i]){
			dot.init(lc(i),lc.sizes[i]);
			allPoints.add(dot,1,DiceInfo::middle,0);
		}
	}
	lc.filterReset();

	// 大サイコロ
	lc.circleFilter(1,2);
	lc.sizeFilter(dotLargeMinSize,dotLargeMaxSize);
	for(int i=0;i<lc.num;i++){
		if(lc.flags[i]){
			dot.init(lc(i),lc.sizes[i]);
			allPoints.add(dot,1,DiceInfo::large,0);
		}
	}
	lc.filterReset();

	// １の目大中サイコロ
	lc.circleFilter(1,2);
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
	lc.sizeFilter(dot1MinSize,dot1MaxSize);

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
	//	if(dot1s[i].type == DiceInfo::small)
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
				if(sita>35 && sita<55){
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
	vector<Dot1Point> dot1s;
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
				dot1s.push_back(dot1);
				dot1Nums.push_back(i);
			}
		}
	}

	// テスト表示
	//Image draw;
	//draw.clone(src);
	//cv::namedWindow("test",0);
	//for(int i=0;i<dot1s.size();i++){
	//	if(dot1s[i].type == DiceInfo::large)
	//		dot1s[i].draw(draw,cv::Scalar(255,0,0));
	//}
	//draw.imshow("test");
	//cv::waitKey(0);

	// 4の目の点から2の目のアルゴリズム適応
	Dot2Point dot2;
	vector<Dot2Point> dot2s;
	vector<int> dot2Num[2];
	for(int i=0;i<dot1s.size();i++){

		// 距離指定
		if(dot1s[i].type == DiceInfo::small){
			distance = dot4SmallDistance;
		}else if(dot1s[i].type == DiceInfo::middle){
			distance = dot4MiddleDistance;
		}else if(dot1s[i].type == DiceInfo::large){
			distance = dot4LargeDistance;
		}

		for(int j=i+1;j<dot1s.size();j++){
			//if(i==j) continue;
			if(dot1s[i].type != dot1s[j].type) continue;
			if(Calc::getDistance2(dot1s[i],dot1s[j]) < pow(distance,2) ){
				// 角度フィルター
				//double tan = abs(dot1s[i].pt.y - dot1s[j].pt.y)/abs(dot1s[i].pt.x - dot1s[j].pt.x);
				//double sita = atan(tan)*180/CV_PI;
				double sita = Calc::getAngle(dot1s[i],dot1s[j]);
				if(sita>35 && sita<55){
					dot2.init(dot1s[i],dot1s[j],dot1s[i].type);
					dot2s.push_back(dot2);
					
					dot2Num[0].push_back(dot1Nums[i]);
					dot2Num[1].push_back(dot1Nums[j]);
					break;
				}
			}
		}
	}

	//Image draw;
	//draw.clone(src);
	//cv::namedWindow("test",0);
	//for(int i=0;i<dot2s.size();i++){
	//	dot2s[i].draw(draw,cv::Scalar(255,0,0),cv::Scalar(255,255,0));
	//}
	//draw.imshow("test");
	//cv::waitKey(0);

	// 4の目の決定
	Dot4Point dot4;
	for(int i=0;i<dot2s.size();i++){
		for(int j=0;j<dot2s.size();j++){
			if(j==i) continue;
			if(dot2s[i].type != dot2s[j].type) continue;
			if(Calc::getDistance2(dot2s[i].center,dot2s[j].center) < dot2s[i].center.size/CV_PI){
				dot4.init(dot2s[i],dot2s[j],dot2s[i].center,dot2s[i].type);
				dot4Points.push_back(dot4);


				for(int k=0;k<2;k++){
					allPoints.flags[dot2Num[k][i]] = 0;
					allPoints.kinds[dot2Num[k][i]] = 4;
					allPoints.flags[dot2Num[k][j]] = 0;
					allPoints.kinds[dot2Num[k][j]] = 4;
				}
			}
		}
	}

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
	for(int i=0;i<allDot3Points.size();i++){
		if(!allDot3Points.flags[i]) continue;
		if(allDot3Points.types[i] == DiceInfo::small)
			radius = dot6SmallRasius;
		else if(allDot3Points.types[i] == DiceInfo::middle)
			radius = dot6MiddleRasius;
		else if(allDot3Points.types[i] == DiceInfo::large)
			radius = dot6LargeRasius;

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

/******************
 *   サイコロの目厳選削除
 */

void DiceDetection::eraseDot1Points(){
	
	vector<int> dot1Num;
	
	// 点群から１の目削除
	for(int j=0;j<dot1Points.size();j++){
		for(int i=0;i<allPoints.size();i++){
			int radius = allPoints[i].size;
			if(radius<dot1Points[j].size) radius = dot1Points[j].size;
			if(Calc::getDistance2(allPoints[i],dot1Points[j]) < radius/CV_PI){
				allPoints.flags[i] = 0;
				allPoints.kinds[i] = 1;
				dot1Num.push_back(i);
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
		if(dot1Points[j].type!=DiceInfo::none)
			continue;
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
					Mmatch++;
				}
			}
		}
		if(Mmatch>=Lmatch)
			if(allPoints[i].size<correctMiddleMaxSize)
				allPoints.types[i] = DiceInfo::middle;
	}
	
	Lmatch = Mmatch = 0;
	// 大サイコロを中サイコロに誤判した修正 
	for(int i=0;i<allPoints.size();i++){
		Lmatch=0,Mmatch=0;
		if(allPoints.types[i] != DiceInfo::middle) continue;
		if(allPoints.kinds[i] == 1) continue;
		for(int j=0;j<allPoints.size();j++){
			if(allPoints.types[j]==DiceInfo::large){
				if(Calc::getDistance2(allPoints[i],allPoints[j]) < pow(correctLargeRadius,2)){
					Lmatch++;
				}
			}else if(allPoints.types[j]==DiceInfo::middle){
				if(Calc::getDistance2(allPoints[i],allPoints[j]) < pow(correctMiddleRadius,2)){
					Mmatch++;
				}
			}
		}
		if(Mmatch<=Lmatch){
			if(allPoints[i].size>correctLargeMinSize)
				allPoints.types[i] = DiceInfo::large;
		}
	}
}

void DiceDetection::clearAllLines(){
	allLines.clear();
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

}