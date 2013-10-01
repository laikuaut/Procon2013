#include "DiceInfo.h"

namespace pro{

DiceInfo::DiceInfo(void)
{
}


DiceInfo::~DiceInfo(void)
{
}

void DiceInfo::init(cv::Point center,int angle,DiceInfo::dtype type,int kind){
	this->center = center;
	this->angle = angle;
	this->type = type;
	this->kind = kind;
}

int DiceInfo::getDiceSize(DiceInfo::dtype type){
	int size;
	switch (type)
	{
	case DiceInfo::small:
		size = DiceInfo::DISE_S;
		break;
	case DiceInfo::middle:
		size = DiceInfo::DISE_M;
		break;
	case DiceInfo::large:
		size = DiceInfo::DISE_L;
		break;
	default:
		break;
	}
	return size;
}

int DiceInfo::getMToLWNum(int Lnum){
	switch (Lnum)
	{
	case 1:
		return 13;
	case 2:
		return 11;
	case 3:
		return 10;
	case 4:
		return 8;
	case 5:
		return 6;
	case 6:
		return 5;
	case 7:
		return 3;
	case 8:
		return 2;
	default:
		break;
	}
}

int DiceInfo::getSToMWNum(int Mnum){
	switch (Mnum)
	{
	case 1:
		return 23;
	case 2:
		return 21;
	case 3:
		return 20;
	case 4:
		return 18;
	case 5:
		return 16;
	case 6:
		return 15;
	case 7:
		return 13;
	case 8:
		return 11;
	case 9:
		return 10;
	case 10:
		return 8;
	case 11:
		return 6;
	case 12:
		return 5;
	case 13:
		return 3;
	case 14:
		return 1;
	default:
		break;
	}
}

int DiceInfo::getMToLHNum(int Lnum){
	switch (Lnum)
	{
	case 1:
		return 8;
	case 2:
		return 7;
	case 3:
		return 5;
	case 4:
		return 3;
	case 5:
		return 2;
	default:
		break;
	}
}

int DiceInfo::getSToMHNum(int Mnum){
	switch (Mnum)
	{
	case 1:
		return 15;
	case 2:
		return 13;
	case 3:
		return 12;
	case 4:
		return 10;
	case 5:
		return 8;
	case 6:
		return 7;
	case 7:
		return 5;
	case 8:
		return 3;
	case 9:
		return 2;
	default:
		break;
	}
}


bool DiceInfo::equal(DiceInfo di){
	return	(angle == di.angle) &&
			(center == di.center) &&
			(type == di.type) &&
			(kind == di.kind);
}

bool DiceInfo::operator()(DiceInfo di,DiceInfo n_di) const{
	return di.equal(n_di);
}


}