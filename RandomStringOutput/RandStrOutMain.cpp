#include"Procon2013\Procon2013.h"
using namespace std;
using namespace pro;

int main(){

	int mode;
	int num;

	// ����������
	StringCalc::randomInit();

	// �\��
	cout<<"������:mode"<<endl;
	cout<<"exit�F0"<<endl;
	cout<<"10�`100�F1"<<endl;
	cout<<"101�`300�F2"<<endl;
	cout<<"301�`500�F3"<<endl;
	cout<<"501�`1000�F4"<<endl;
	cout<<"1001�`2000�F5"<<endl;
	cout<<"2001�`4001�F6"<<endl;
	cout<<"original:7"<<endl;

	// ����
	cout<<"mode > "<<flush;
	cin >> mode;
	if(mode==0) exit(EXIT_SUCCESS);
	cout<<"�쐬�� > "<<flush;
	cin >> num;


	// �f�B���N�g���쐬
	Dir dir = Dir();
	string name = "RandomString";
	int number=0;
	while(1){
		stringstream ss;
		ss << name << mode << number;
		if(dir.isExist(ss.str()))
			number++;
		else{
			cout << ss.str() << "�쐬" << endl;
			dir.create(ss.str());
			dir.cd(ss.str());
			break;
		}
	}
	
	// original�̎��͈̔͐ݒ�
	int min,max;
	if(mode==7){
		cout << "min > " << flush;
		cin >> min;
		cout << "max > " << flush;
		cin >> max;
	}

	// ����
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
