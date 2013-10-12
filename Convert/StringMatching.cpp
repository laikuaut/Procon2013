#include "StringMatching.h"

namespace pro{

StringMatching::StringMatching(void)
{
}


StringMatching::~StringMatching(void)
{
}

void StringMatching::init(string name){
	std::ifstream ifs;
	ifs.open(name);
	char *c_str = new char[4001];
	ifs.getline(c_str,4000);
	c_str[4000] = '\0';
	for(int i=0;c_str[i]!='\0';i++)
		str.push_back(c_str[i]);
}

int StringMatching::getCharPositionsNumAtValue(char value){
	for(int i=0;i<charPositions.size();i++){
		if(charPositions[i].getValue() == value)
			return i;
	}
	return -1;
}


void StringMatching::length1Matching(){

	bool flag;
	for(int i=0;i<str.size();i++){
		CharPositions cp;

		// 新しい文字の追加
		flag=true;
		for(int j=0;j<charPositions.size();j++){
			if(str[i]==charPositions[j].getValue())
				flag=false;
		}
		if(flag){
			cp.init(str[i],i);
			charPositions.push_back(cp);
		}else continue;

		// 文字位置の保存
		for(int j=i+1;j<str.size();j++){
			if(charPositions[charPositions.size()-1].getValue() == str[j])
				charPositions[charPositions.size()-1].add(j);
		}
	}
}

void StringMatching::length1SizeErase(int minSize){
	for(int i=0;i<charPositions.size();i++){
		if(charPositions[i].size() < minSize){
			vector<CharPositions>::iterator it = charPositions.begin();
			charPositions.erase(it+i);
			i--;
		}
	}
}

void StringMatching::continuous1Matching(){
	bool flag=false;
	int pos;
	vector<char> str;
	for(int i=0;i<charPositions.size();i++){
		for(int j=0;j<charPositions[i].size()-1;j++){
			// 連続した文字列差分
			if(charPositions[i][j+1]-charPositions[i][j]==1){
				if(!flag){
					pos = j;
					str.push_back(charPositions[i].getValue());
					str.push_back(charPositions[i].getValue());
				}else{
					str.push_back(charPositions[i].getValue());
				}
				flag=true;
			}else{
				if(flag){
					StringPositions sp;
					// すでに登録されている文字列
					for(int k=0;k<continuousStrs.size();k++){
						if(continuousStrs[k].equal(str)){
							continuousStrs[k].add(pos);
							str.clear();
							flag=false;
						}
					}
					// 初めて登録される文字列
					if(flag){
						sp.init(str,pos);
						continuousStrs.push_back(sp);
						str.clear();
						flag=false;
					}
				}
			}
			// ループを抜けてしまったとき
			if(flag){
				StringPositions sp;
				// すでに登録されている文字列
				for(int k=0;k<continuousStrs.size();k++){
					if(continuousStrs[k].equal(str)){
						continuousStrs[k].add(pos);
						str.clear();
						flag=false;
					}
				}
				// 初めて登録される文字列
				if(flag){
					sp.init(str,pos);
					continuousStrs.push_back(sp);
					str.clear();
					flag=false;
				}
			}
		}
	}
}

void StringMatching::continuous1LengthAndSizeErase(int length,int minSize){
	for(int i=0;i<continuousStrs.size();i++){
		if(continuousStrs[i].length() == length && continuousStrs[i].size() < minSize){
			vector<StringPositions>::iterator it = continuousStrs.begin();
			continuousStrs.erase(it+i);
			i--;
		}
	}
}


void StringMatching::length2Matching(int minsize){
	int num;
	char two;
	vector<StringPositions> twoStrPositions;
	for(int i=0;i<str.size()-1;i++){
		StringPositions sp;
		vector<char> m_str;
		num = getCharPositionsNumAtValue(str[i]);
		if(num==-1) continue;
		two = str[i+1];
		m_str.push_back(str[i]);
		m_str.push_back(str[i+1]);
		bool flag=false;
		for(int j=0;j<twoStrPositions.size();j++){
			if(twoStrPositions[j].equal(m_str))
				flag = true;
		}
		if(flag) continue;
		sp.init(m_str,i);
		for(int j=charPositions[num].getNumAtStrNum(i)+1;j<charPositions[num].size();j++){
			if(str.size()>charPositions[num][j]+1 && two==str[charPositions[num][j]+1]){
				sp.add(charPositions[num][j]);
			}
		}
		for(int j=0;j<charPositions[num].size();j++){
			if(0<=charPositions[num][j]-1 && two==str[charPositions[num][j]-1]){
				sp.add(charPositions[num][j],true);
			}
		}
		if(sp.size()>=minsize || sp.size(true)>=1){
			twoStrPositions.push_back(sp);
		}
	}
	strPositions.push_back(twoStrPositions);
}



void StringMatching::lengthMatching(int n,int minsize){
	vector<StringPositions> nStrPositions;
	for(int i=0;i<strPositions[n-3].size();i++){
		vector<char> m_str;
		m_str = strPositions[n-3][i].getValue();
		vector<int> registpos;
		m_str.push_back(-1);
		for(int j=0;j<strPositions[n-3][i].size();j++){
			StringPositions sp;	
			if(strPositions[n-3][i][j]+(n-1)<str.size())
				m_str[n-1]=str[strPositions[n-3][i][j]+(n-1)];
			else break;
			bool flag=false;
			for(int k=0;k<registpos.size();k++){
				if(registpos[k]==j) flag=true;
			}
			if(flag) continue;
			sp.init(m_str,strPositions[n-3][i][j]);
			for(int k=j+1;k<strPositions[n-3][i].size();k++){
				if(str.size()>strPositions[n-3][i][k]+(n-1)&&m_str[n-1]==str[strPositions[n-3][i][k]+(n-1)]){
					sp.add(strPositions[n-3][i][k]);
					registpos.push_back(k);
				}
			}
			for(int k=0;k<strPositions[n-3][i].size(true);k++){
				//if(0<=strPositions[n-3][i][-(k+1)]-(n-1))
					//std::cout<<strPositions[n-3][i][-(k+1)]-(n-1)<<":"<<m_str[n-1]<<"=="<<str[strPositions[n-3][i][-(k+1)]-(n-1)]<<std::endl;
				if(0<=strPositions[n-3][i][-(k+1)]-(n-1)&&m_str[n-1]==str[strPositions[n-3][i][-(k+1)]-(n-1)]){
					//if(j==k) continue;
					sp.add(strPositions[n-3][i][-(k+1)],true);
					//registpos.push_back(k);
				}
			}
			if(sp.size()>=minsize || sp.size(true)>=1){
				nStrPositions.push_back(sp);
			}
		}
		registpos.clear();
	}
	strPositions.push_back(nStrPositions);
}

void StringMatching::matching(int n){
	length1Matching();
	length1SizeErase(2);
	continuous1Matching();
	length2Matching(2);
	for(int k=3;k<n;k++){
		lengthMatching(k,2);
	}
}

void StringMatching::dips(int n){
	for(int i=0;i<str.size();i++){
		std::cout<<str[i]<<std::flush;
	}
	
	Timer timer;
	timer.start();

	matching(n);

	// 一文字処理
	std::cout<<std::endl;
	//length1Matching();
	//length1SizeErase(2);
	std::cout<<"length(1):"<<charPositions.size()<<std::endl;
	//std::cout<<(double)timer.getNow()/1000.<<std::endl;
	//for(int i=0;i<charPositions.size();i++){
	//	std::cout<<charPositions[i].getValue()<<":"<<charPositions[i].size()<<std::endl;
	//}

	// 1文字連続
	//continuous1Matching();
	//continuous1LengthAndSizeErase(2,2);
	std::cout<<"countinuous(1):"<<continuousStrs.size()<<std::endl;


	// 2文字処理
	//length2Matching(2);
	std::cout<<"length(2):"<<strPositions[0].size()<<std::endl;
	//std::cout<<(double)timer.getNow()/1000.<<std::endl;
	for(int i=0;i<strPositions[0].size();i++){
		for(int j=0;j<strPositions[0][i].length();j++){
			std::cout<<strPositions[0][i].getValue()[j]<<std::flush;
		}
		std::cout<<":"<<strPositions[0][i].size()<<std::flush;
		std::cout<<":"<<strPositions[0][i].size(true)<<std::endl;
	}

	for(int k=3;k<n;k++){
		// n文字処理
		//lengthMatching(k,2);
		if(strPositions[k-2].size())
			std::cout<<"length("<< k <<"):"<<strPositions[k-2].size()<<std::endl;
		//std::cout<<(double)timer.getNow()/1000.<<std::endl;
		for(int i=0;i<strPositions[k-2].size();i++){
			for(int j=0;j<strPositions[k-2][i].length();j++){
				std::cout<<strPositions[k-2][i].getValue()[j]<<std::flush;
			}
			std::cout<<":"<<strPositions[k-2][i].size()<<std::flush;
			std::cout<<":"<<strPositions[k-2][i].size(true)<<std::endl;
		}
	}


}

}