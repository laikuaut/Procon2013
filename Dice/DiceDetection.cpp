#include "DiceDetection.h"

namespace pro{

DiceDetection::DiceDetection(void)
{
}


DiceDetection::~DiceDetection(void)
{
}

/******************
 *   ������
 */
void DiceDetection::init(Image src){
	this->src.clone(src);
}

/******************
 *   �N���XDotPoints
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
 *   �N���XLineSegments
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

LineSegment DiceDetection::LineSegments::operator[](int i) const{
	return lines[i];
}

/******************
 *   �K�v�v�f�̎擾
 */
void DiceDetection::getAllPoints(){

	// 2�l��
	Image bin;
	bin.grayeScale(src);
	bin.binarization(bin);

	// �_���o
	LabelingCenter lc;
	lc.init(bin);
	lc.setCenter(bin);
	
	DotPoint dot;

	// ���_
	// ���T�C�R���̓_�𒊏o
	lc.circleFilter(1,2);
	lc.sizeFilter(dotSmallMinSize,dotSmallMaxSize);
	for(int i=0;i<lc.num;i++){
		if(lc.flags[i]){
			dot.init(lc(i),lc.sizes[i]);
			allPoints.add(dot,1,DiceInfo::small,0);
		}
	}
	lc.filterReset();

	// ���T�C�R��
	lc.circleFilter(1,2);
	lc.sizeFilter(dotMiddleMinSize,dotMiddleMaxSize);
	for(int i=0;i<lc.num;i++){
		if(lc.flags[i]){
			dot.init(lc(i),lc.sizes[i]);
			allPoints.add(dot,1,DiceInfo::middle,0);
		}
	}
	lc.filterReset();

	// ��T�C�R��
	lc.circleFilter(1,2);
	lc.sizeFilter(dotLargeMinSize,dotLargeMaxSize);
	for(int i=0;i<lc.num;i++){
		if(lc.flags[i]){
			dot.init(lc(i),lc.sizes[i]);
			allPoints.add(dot,1,DiceInfo::large,0);
		}
	}
	lc.filterReset();

	// �P�̖ڑ咆�T�C�R��
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

	// �Ɨ������_�̍폜�p
	vector<short> flags;
	for(int i=0;i<allPoints.size();i++){
		flags.push_back(allPoints.flags[i]);
	}

	for(int i=0;i<allPoints.size();i++){
		if(!allPoints.flags[i]) continue;
		
		// �T�C�R���̃T�C�Y���Ƃɔ��a�ύX 
		if(allPoints.types[i]== DiceInfo::small)
			radius = lineSmallRadius;
		else if(allPoints.types[i] == DiceInfo::middle)
			radius = lineMiddleRadius;
		else if(allPoints.types[i] == DiceInfo::large)
			radius = lineLargeRadius;

		// �������o
		for(int j=0;j<allPoints.size();j++){
			if(i==j) continue;
			if(allPoints.types[i] != allPoints.types[j]) continue;
			if(!allPoints.flags[j]) continue;
			if(Calc::getDistance2(allPoints[i],allPoints[j]) < pow(radius,2)){
				ls.init(allPoints[i],allPoints[j]);
				allLines.add(ls,1,allPoints.types[i],0,i,j);
				flags[i] = flags[j] = 0; // �Ɨ����Ă��Ȃ��_
			}
		}
	}

	// �Ɨ������_�̍폜
	for(int i=0;i<allPoints.size();i++){
		if(flags[i]){
			allPoints.flags[i] = 0;
			allPoints.types[i] = DiceInfo::none;
		}
	}

}

/******************
 *   �T�C�R���̖ڔ���
 */
void DiceDetection::getDot1Points(){
	Image hue1,hue2,dst;
	
	// �Ԃ̓_���o
	hue1.hsvColorExtraction(src,0,60,100,100);
	hue2.hsvColorExtraction(src,120,180,100,100);
	dst.bitwiseOr(hue1,hue2);

	// �d�S�����_���o
	LabelingCenter lc;
	lc.init(dst);
	lc.setCenter(dst);
	lc.circleFilter(1,2);
	lc.sizeFilter(dot1MinSize,dot1MaxSize);

	Dot1Point dot1;

	// 1�̖ڂ̓_�o�^
	for(int i=0;i<lc.num;i++){
		if(lc.flags[i]){
			dot1.init(lc(i),lc.sizes[i]);
			dot1Points.push_back(dot1);
		}
	}

	// �_�Q����1�̖ڂ̍폜
	eraseDot1Points();

}

/******************
 *   �T�C�R���̖ڌ��I�폜
 */

void DiceDetection::eraseDot1Points(){
	
	vector<int> dot1Num;
	
	// �_�Q����P�̖ڍ폜
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

	// �T�C�R���̑咆����
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

	// ����ɑ�T�C�R���ƌ�F�������T�C�R���̏C��
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

	// 2�̖ڂ̓_���܂܂Ȃ������𒊏o
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

	// 2�̖ڂ̓_�𒊏o
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

	// 2�̖ڂ�����
	for(int i=0;i<dot1s.size();i++){

		// �����w��
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
				// �p�x�t�B���^�[
				double tan = abs(dot1s[i].pt.y - dot1s[j].pt.y)/abs(dot1s[i].pt.x - dot1s[j].pt.x);
				double sita = atan(tan)*180/CV_PI;
				if(sita>35 && sita<55){
					dot2.init(dot1s[i],dot1s[j],dot1s[i].type);
					dot2Points.push_back(dot2);
					
					allPoints.flags[dot1Nums[i]] = false;
					allPoints.kinds[dot1Nums[i]] = 2;
					break;
				}
			}
		}
	}

}

void DiceDetection::getDot4Points(){

	int minDistance,maxDistance,distance;
	vector<int> dot4Nums;


	//for(int i=0;i<allLines.size();i++){
	//	if(allLines.types[i] == DiceInfo::small){
	//		minDistance = dot2SmallMinDistance;
	//		maxDistance = dot2SmallMaxDistance;
	//	}else if(allLines.types[i] == DiceInfo::middle){
	//		minDistance = dot2MiddleMinDistance;
	//		maxDistance = dot2MiddleMaxDistance;
	//	}else if(allLines.types[i] == DiceInfo::large){
	//		minDistance = dot2LargeMinDistance;
	//		maxDistance = dot2LargeMaxDistance;
	//	}

	//	if(pow(minDistance,2) < pow(allLines[i].distance,2) && pow(allLines[i].distance,2) < pow(maxDistance,2)){
	//		allLines.flags[i] = 1;
	//		dot4Nums.push_back(allLines.dotNums[0][i]);
	//		dot4Nums.push_back(allLines.dotNums[1][i]);
	//	}else{
	//		allLines.flags[i] = 0;
	//	}
	//}
}

/******************
 *   �C������
 */

void DiceDetection::correctPointType(){

	int Lmatch=0,Mmatch=0;
	// ���T�C�R�����T�C�R���Ɍ딻�����C��
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
	// ��T�C�R���𒆃T�C�R���Ɍ딻�����C�� 
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

/******************
 *   �`�ʏ���
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

}