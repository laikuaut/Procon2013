#include"Procon2013\Procon2013.h"
using namespace pro;

int main(int argc,char** argv){
	Encode encode;
	encode.init(argv[1]);
	//encode.init("test.txt");
	encode.run();
}