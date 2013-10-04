#include "Dot5Point.h"

namespace pro{

Dot5Point::Dot5Point(void)
{
}


Dot5Point::~Dot5Point(void)
{
}

void Dot5Point::init(Dot3Point dot3p1,Dot3Point dot3p2,DiceInfo::dtype type){
	this->type = type;
	dot3[0].init(dot3p1);
	dot3[1].init(dot3p2);
	center.init(dot3[0].center,dot3[0].center.size);
}

void Dot5Point::draw(Image& img,cv::Scalar dot_col,cv::Scalar line_col,int thickness){

}
void Dot5Point::drawCenter(Image& img,cv::Scalar scal){

}


}