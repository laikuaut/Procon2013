#include"Procon2013\Procon2013.h"
using namespace std;
using namespace pro;

int main(){

	int mode;
	int num;

	// 乱数初期化
	StringCalc::randomInit();

	// 表示
	cout<<"文字数:mode"<<endl;
	cout<<"exit：0"<<endl;
	cout<<"10～100：1"<<endl;
	cout<<"101～300：2"<<endl;
	cout<<"301～500：3"<<endl;
	cout<<"501～1000：4"<<endl;
	cout<<"1001～2000：5"<<endl;
	cout<<"2001～4001：6"<<endl;
	cout<<"original:7"<<endl;

	// 入力
	cout<<"mode > "<<flush;
	cin >> mode;
	if(mode==0) exit(EXIT_SUCCESS);
	cout<<"作成数 > "<<flush;
	cin >> num;


	// ディレクトリ作成
	Dir dir = Dir();
	string name = "RandomString";
	int number=0;
	while(1){
		stringstream ss;
		ss << name << mode << number;
		if(dir.isExist(ss.str()))
			number++;
		else{
			cout << ss.str() << "作成" << endl;
			dir.create(ss.str());
			dir.cd(ss.str());
			break;
		}
	}
	
	// originalの時の範囲設定
	int min,max;
	if(mode==7){
		cout << "min > " << flush;
		cin >> min;
		cout << "max > " << flush;
		cin >> max;
	}

	// 生成
	name = "randStr";
	int random_num;
	for(int i=0;i<num;i++){
		
		stringstream _ss;
		_ss << name << mode << i << ".txt";
		
		switch (mode)
		{
		case 1:
			random_num = 10+rand()%91;
			break;
		case 2:
			random_num = 100+rand()%201;
			break;
		case 3:
			random_num = 300+rand()%201;
			break;
		case 4:
			random_num = 500+rand()%501;
			break;
		case 5:
			random_num = 1000+rand()%1001;
			break;
		case 6:
			random_num = 2000+rand()%2001;
			break;
		case 7:
			random_num = min+rand()%(max-min);
		default:
			break;
		}
		cout << dir.pwd(_ss.str()) << " : " << random_num << endl;
		StringCalc::randomStringOutput(random_num,dir.pwd(_ss.str()));
	}

}
