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

		// êVÇµÇ¢ï∂éöÇÃí«â¡
		flag=true;
		for(int j=0;j<charPositions.size();j++){
			if(str[i]==charPositions[j].getValue())
				flag=false;
		}
		if(flag){
			cp.init(str[i],i);
			charPositions.push_back(cp);
		}else continue;

		// ï∂éöà íuÇÃï€ë∂
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
			// òAë±ÇµÇΩï∂éöóÒç∑ï™
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
					// Ç∑Ç≈Ç…ìoò^Ç≥ÇÍÇƒÇ¢ÇÈï∂éöóÒ
					for(int k=0;k<continuousStrs.size();k++){
						if(continuousStrs[k].equal(str)){
							continuousStrs[k].add(pos);
							str.clear();
							flag=false;
						}
					}
					// èâÇﬂÇƒìoò^Ç≥ÇÍÇÈï∂éöóÒ
					if(flag){
						sp.init(str,pos);
						continuousStrs.push_back(sp);
						str.clear();
						flag=false;
					}
				}
			}
			// ÉãÅ[ÉvÇî≤ÇØÇƒÇµÇ‹Ç¡ÇΩÇ∆Ç´
			if(flag){
				StringPositions sp;
				// Ç∑Ç≈Ç…ìoò^Ç≥ÇÍÇƒÇ¢ÇÈï∂éöóÒ
				for(int k=0;k<continuousStrs.size();k++){
					if(continuousStrs[k].equal(str)){
						continuousStrs[k].add(pos);
						str.clear();
						flag=false;
					}
				}
				// èâÇﬂÇƒìoò^Ç≥ÇÍÇÈï∂éöóÒ
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

//void StringMatching::length2Matching(int minsize){
//	int num;
//	char two;
//	vector<StringPositions> twoStrPositions;
//	for(int i=0;i<str.size()-1;i++){
//		StringPositions sp;
//		vector<char> m_str;
//		num = getCharPositionsNumAtValue(str[i]);
//		if(num==-1) continue;
//		two = str[i+1];
//		m_str.push_back(str[i]);
//		m_str.push_back(str[i+1]);
//		bool flag=false;
//		for(int j=0;j<twoStrPositions.size();j++){
//			if(twoStrPositions[j].equal(m_str))
//				flag = true;
//		}
//		if(flag) continue;
//		sp.init(m_str,i);
//		for(int j=charPositions[num].getNumAtStrNum(i)+1;j<charPositions[num].size();j++){
//			if(str.size()>charPositions[num][j]+1 && two==str[charPositions[num][j]+1]){
//				sp.add(charPositions[num][j]);
//			}
//		}
//		for(int j=0;j<charPositions[num].size();j++){
//			if(0<=charPositions[num][j]-1 && two==str[charPositions[num][j]-1]){
//				sp.add(charPositions[num][j]);
//			}
//		}
//		if(sp.size()>=minsize){
//			twoStrPositions.push_back(sp);
//		}
//	}
//	strPositions.push_back(twoStrPositions);
//}
//
//void StringMatching::lengthMatching(int n,int minsize){
//	vector<StringPositions> nStrPositions;
//	for(int i=0;i<strPositions[n-3].size();i++){
//		vector<char> m_str;
//		m_str = strPositions[n-3][i].getValue();
//		vector<int> registpos;
//		m_str.push_back(-1);
//		for(int j=0;j<strPositions[n-3][i].size();j++){
//			StringPositions sp;	
//			if(strPositions[n-3][i][j]+(n-1)<str.size())
//				m_str[n-1]=str[strPositions[n-3][i][j]+(n-1)];
//			else break;
//			bool flag=false;
//			for(int k=0;k<registpos.size();k++){
//				if(registpos[k]==j) flag=true;
//			}
//			if(flag) continue;
//			sp.init(m_str,strPositions[n-3][i][j]);
//			for(int k=j+1;k<strPositions[n-3][i].size();k++){
//				if(str.size()>strPositions[n-3][i][k]+(n-1)&&m_str[n-1]==str[strPositions[n-3][i][k]+(n-1)]){
//					sp.add(strPositions[n-3][i][k]);
//					registpos.push_back(k);
//				}
//			}
//			if(sp.size()>=minsize){
//				nStrPositions.push_back(sp);
//			}
//		}
//		registpos.clear();
//	}
//	strPositions.push_back(nStrPositions);
//}
//
////void StringMatching::reverseLength2Matching(int minsize){
////	int num;
////	char two;
////	vector<StringReverse> twoStrReverses;
////	for(int i=0;i<str.size()-1;i++){
////		StringReverse sr;
////		vector<char> m_str;
////		num = getCharPositionsNumAtValue(str[i]);
////		if(num==-1) continue;
////		two = str[i+1];
////		m_str.push_back(str[i]);
////		m_str.push_back(str[i+1]);
////		bool flag=false;
////		for(int j=0;j<twoStrReverses.size();j++){
////			if(twoStrReverses[j].equal(m_str))
////				flag = true;
////		}
////		if(flag) continue;
////		sr.init(m_str);
//////		for(int j=charPositions[num].getNumAtStrNum(i);j<charPositions[num].size();j++){
////		for(int j=0;j<charPositions[num].size();j++){
////			if(0<=charPositions[num][j]-1 && two==str[charPositions[num][j]-1]){
////				sr.add(charPositions[num][j]);
////			}
////		}
////		if(sr.size()>=minsize){
////			twoStrReverses.push_back(sr);
////		}
////	}
////	strReverses.push_back(twoStrReverses);
////}
////
////void StringMatching::reverseLengthMatching(int n,int minsize){
////	vector<StringReverse> nStrReverses;
////	for(int i=0;i<strReverses[n-3].size();i++){
////		vector<char> m_str;
////		//for(int k=0;k<n-1;k++){
////		//	m_str.push_back(strReverses[n-3][i].getValue()[k]);
////		//}
////		m_str = strReverses[n-3][i].getValue();
////		vector<int> registpos;
////		m_str.push_back(-1);
////		for(int j=0;j<strReverses[n-3][i].size();j++){
////			StringReverse sr;
////			// Ç±Ç±
////			if(strReverses[n-3][i][j]-(n-1)>=0)
////				m_str[n-1]=str[strReverses[n-3][i][j]-(n-1)];
////			else
////				break;
////			bool flag=false;
////
////			// Ç±Ç±ÅIÅI
////			for(int k=0;k<registpos.size();k++){
////				if(registpos[k]==j) flag=true;
////			}
////			if(flag) continue;
////			// Ç±Ç±ÅIÅI
////
////			//StringReverse::reverse(m_str);
////	
////			sr.init(m_str);//,strReverses[n-3][i][j]);
////			for(int k=0;k<strReverses[n-3][i].size();k++){
////				if(0<=strReverses[n-3][i][k]-(n-1)&&m_str[n-1]==str[strReverses[n-3][i][k]-(n-1)]){
////				//	if(k==j) 
////				//		continue;
////					sr.add(strReverses[n-3][i][k]);
////					registpos.push_back(k);
////				}
////			}
////			if(sr.size()>=minsize){
////				nStrReverses.push_back(sr);
////			}
////		}
////		registpos.clear();
////	}
////	strReverses.push_back(nStrReverses);
////}
//
//void StringMatching::dips(){
//	for(int i=0;i<str.size();i++){
//		std::cout<<str[i]<<std::flush;
//	}
//	
//	Timer timer;
//	timer.start();
//
//	// àÍï∂éöèàóù
//	std::cout<<std::endl;
//	length1Matching();
//	length1SizeErase(2);
//	std::cout<<"length(1):"<<charPositions.size()<<std::endl;
//	std::cout<<(double)timer.getNow()/1000.<<std::endl;
//	//for(int i=0;i<charPositions.size();i++){
//	//	std::cout<<charPositions[i].getValue()<<":"<<charPositions[i].size()<<std::endl;
//	//}
//
//	// 1ï∂éöòAë±
//	continuous1Matching();
//	//continuous1LengthAndSizeErase(2,2);
//	std::cout<<"countinuous(1):"<<continuousStrs.size()<<std::endl;
//	std::cout<<(double)timer.getNow()/1000.<<std::endl;
//	//for(int i=0;i<continuousStrs.size();i++){
//	//	for(int j=0;j<continuousStrs[i].length();j++){
//	//		std::cout<<continuousStrs[i].getValue()[j]<<std::flush;
//	//	}
//	//	std::cout<<":"<<continuousStrs[i].size()<<std::endl;
//	//}
//
//	// 2ï∂éöèàóù
//	length2Matching(2);
//	std::cout<<"length(2):"<<strPositions[0].size()<<std::endl;
//	std::cout<<(double)timer.getNow()/1000.<<std::endl;
//	//for(int i=0;i<strPositions[0].size();i++){
//	//	for(int j=0;j<strPositions[0][i].length();j++){
//	//		std::cout<<strPositions[0][i].getValue()[j]<<std::flush;
//	//	}
//	//	std::cout<<":"<<strPositions[0][i].size()<<std::endl;
//	//}
//
//	for(int k=3;k<4001;k++){
//		// nï∂éöèàóù
//		//lengthMatching(k,2);
//		//if(strPositions[k-2].size())
//		//	std::cout<<"length("<< k <<"):"<<strPositions[k-2].size()<<std::endl;
//		//std::cout<<(double)timer.getNow()/1000.<<std::endl;
//		//for(int i=0;i<strPositions[k-2].size();i++){
//		//	for(int j=0;j<strPositions[k-2][i].length();j++){
//		//		std::cout<<strPositions[k-2][i].getValue()[j]<<std::flush;
//		//	}
//		//	std::cout<<":"<<strPositions[k-2][i].size()<<std::endl;
//		//}
//	}
//	std::cout<<(double)timer.getNow()/1000.<<std::endl;
//
//	// îΩì]2ï∂éö
//	reverseLength2Matching(1);
//	std::cout<<"reverse(2):"<<strReverses[0].size()<<std::endl;
//	std::cout<<(double)timer.getNow()/1000.<<std::endl;
//	for(int i=0;i<strReverses[0].size();i++){
//		for(int j=0;j<strReverses[0][i].length();j++){
//			std::cout<<strReverses[0][i].getValue()[j]<<std::flush;
//		}
//		std::cout<<":"<<strReverses[0][i].size()<<std::endl;
//	}
//
//	// îΩì]nï∂éö
//	for(int k=3;k<4001;k++){
//		// nï∂éöèàóù
//		reverseLengthMatching(k,1);
//		if(strReverses[k-2].size())
//			std::cout<<"reverse("<< k <<"):"<<strReverses[k-2].size()<<std::endl;
//		//std::cout<<(double)timer.getNow()/1000.<<std::endl;
//		for(int i=0;i<strReverses[k-2].size();i++){
//			for(int j=0;j<strReverses[k-2][i].length();j++){
//				std::cout<<strReverses[k-2][i].getValue()[j]<<std::flush;
//			}
//			std::cout<<":"<<strReverses[k-2][i].size()<<std::endl;
//		}
//	}
//	std::cout<<(double)timer.getNow()/1000.<<std::endl;
//
//}
//
//}


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

void StringMatching::dips(){
	for(int i=0;i<str.size();i++){
		std::cout<<str[i]<<std::flush;
	}
	
	Timer timer;
	timer.start();

	// àÍï∂éöèàóù
	std::cout<<std::endl;
	length1Matching();
	length1SizeErase(2);
	std::cout<<"length(1):"<<charPositions.size()<<std::endl;
	std::cout<<(double)timer.getNow()/1000.<<std::endl;
	//for(int i=0;i<charPositions.size();i++){
	//	std::cout<<charPositions[i].getValue()<<":"<<charPositions[i].size()<<std::endl;
	//}

	// 1ï∂éöòAë±
	continuous1Matching();
	//continuous1LengthAndSizeErase(2,2);
	std::cout<<"countinuous(1):"<<continuousStrs.size()<<std::endl;
	std::cout<<(double)timer.getNow()/1000.<<std::endl;
	//for(int i=0;i<continuousStrs.size();i++){
	//	for(int j=0;j<continuousStrs[i].length();j++){
	//		std::cout<<continuousStrs[i].getValue()[j]<<std::flush;
	//	}
	//	std::cout<<":"<<continuousStrs[i].size()<<std::endl;
	//}

	// 2ï∂éöèàóù
	length2Matching(2);
	std::cout<<"length(2):"<<strPositions[0].size()<<std::endl;
	std::cout<<(double)timer.getNow()/1000.<<std::endl;
	for(int i=0;i<strPositions[0].size();i++){
		for(int j=0;j<strPositions[0][i].length();j++){
			std::cout<<strPositions[0][i].getValue()[j]<<std::flush;
		}
		std::cout<<":"<<strPositions[0][i].size()<<std::flush;
		std::cout<<":"<<strPositions[0][i].size(true)<<std::endl;
	}

	for(int k=3;k<4001;k++){
		// nï∂éöèàóù
		lengthMatching(k,2);
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
	std::cout<<(double)timer.getNow()/1000.<<std::endl;

	//// îΩì]2ï∂éö
	//reverseLength2Matching(1);
	//std::cout<<"reverse(2):"<<strReverses[0].size()<<std::endl;
	//std::cout<<(double)timer.getNow()/1000.<<std::endl;
	//for(int i=0;i<strReverses[0].size();i++){
	//	for(int j=0;j<strReverses[0][i].length();j++){
	//		std::cout<<strReverses[0][i].getValue()[j]<<std::flush;
	//	}
	//	std::cout<<":"<<strReverses[0][i].size()<<std::endl;
	//}

	//// îΩì]nï∂éö
	//for(int k=3;k<4001;k++){
	//	// nï∂éöèàóù
	//	reverseLengthMatching(k,1);
	//	if(strReverses[k-2].size())
	//		std::cout<<"reverse("<< k <<"):"<<strReverses[k-2].size()<<std::endl;
	//	//std::cout<<(double)timer.getNow()/1000.<<std::endl;
	//	for(int i=0;i<strReverses[k-2].size();i++){
	//		for(int j=0;j<strReverses[k-2][i].length();j++){
	//			std::cout<<strReverses[k-2][i].getValue()[j]<<std::flush;
	//		}
	//		std::cout<<":"<<strReverses[k-2][i].size()<<std::endl;
	//	}
	//}
	std::cout<<(double)timer.getNow()/1000.<<std::endl;

}

}