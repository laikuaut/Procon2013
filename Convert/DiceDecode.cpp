#include "DiceDecode.h"

namespace pro{

DiceDecode::DiceDecode(void)
{
}


DiceDecode::~DiceDecode(void)
{
}

void DiceDecode::init(){
	num=0;
	now=0;

	// 最大送信数だけパケット数を確保
	outPacketNums.resize(100);
	memset(&outPacketNums[0],0,sizeof(int)*100);
	for(int i=0;i<outPacketNums.size();i++){
		outPacketNums[i]=-1;
	}

	readIni();
	addFile();
}

void DiceDecode::readIni(){
	Dir dir = Dir();
	ptree pt;
	string iniFileName = "DiceDecode.ini";

	if(!dir.isExist(iniFileName)){
		std::cout << iniFileName << "を作成します。" << std::endl;
		pt.put("File.dir",Dir().pwd());
		pt.put("Timer.interval",20);
		write_ini(iniFileName,pt);
		exit(1);
	}
	read_ini(iniFileName,pt);
	// ファイル関連
	if (boost::optional<string> value = pt.get_optional<string>("File.dir")) {
		this->dir.cd(value.get());
		//std::cout << "file.dir : " << dir.pwd() << std::endl;
    }
	if (boost::optional<int> value = pt.get_optional<int>("Timer.interval")) {
		interval=value.get()*1000;
		//std::cout << "file.dir : " << dir.pwd() << std::endl;
    }
}

void DiceDecode::addFile(){
	vector<string> paths;
	paths = dir.getIntoPaths();
	for(int i=0;i<paths.size();i++){
		if(Dir::getExtention(paths[i]) == ".jpg"){
			bool flag = true;
			for(int j=0;j<names.size();j++){
				if(names[j] == Dir::getFileName(paths[i])){
					flag=false;
				}
			}
			if(flag){
				std::cout<<std::endl;
				std::cout<<Dir::getFileName(paths[i])<<std::endl;
				names.push_back(Dir::getFileName(paths[i]));
				DiceDetection dd;
				dd.init(dir,Dir::getFileName(paths[i]));
				diceDetections.push_back(dd);
				num++;
				now=num-1;
				
				// oキー
				diceDetections[now].outEncode();
				packetRegist();
				packetMarge();
				output();
			}
		}
	}
}

int DiceDecode::keyEvent(){
	int key=cv::waitKey(30);
	diceDetections[now].setMode(key);
	switch (key)
	{
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '0':
	case 't':
	case 'k':
	case 'c':
	case 's':
	case 'm':
	case 'l':
		nowDisplay();
		break;
	case 'a':
		addFile();
		break;
	case 2424832: // [←]
		now--;
		if(now<0) now=0;
		nowDisplay();
		break;
	case 2555904: // [→]
		now++;
		if(now==num) now=num-1;
		nowDisplay();
		break;
	case 'r':

		break;
	case 'o':
		packetRegist();
		packetMarge();
		output();
		break;
	case 'd':
		output();
		break;
	case 'q':
		return 0;
		break;
	default:
		//std::cout<<key<<std::endl;
		break;
	}
	return 1;
}

void DiceDecode::packetRegist(){
	outPacketNums[diceDetections[now].getPacket()] = now;
	packetRegistDisplay();
	packetDisplay();
}

void DiceDecode::packetRegistDisplay(){
	const int linemax=50;
	std::ifstream ifs;
	std::stringstream ss;
	ss << "DiceToDecode_" << diceDetections[now].getPacket() << ".txt" << std::flush;
	ifs.open(dir.pwd(ss.str()));
	if(ifs.fail()) return;
	char *str = new char[linemax];
	//std::cout << std::endl;
	std::cout<<"Packet"<< diceDetections[now].getPacket() << std::endl;
	while(1){
		ifs.getline(str,linemax);
		if(ifs.eof()) break;
		std::cout<<str<<std::endl;
	}
}

void DiceDecode::packetDisplay(){
	for(int i=0;i<outPacketNums.size();i++){
		if(outPacketNums[i]!=-1){
			std::cout<<"packet"<<i<<" : now"<<outPacketNums[i]<<std::endl;
		}
	}
}

void DiceDecode::packetMarge(){
	vector<string> files = dir.getIntoPaths();
	vector<string> decodeFiles;
	string str = "DiceToDecode_";
	string excection = ".txt";
	vector<string> sort;
	int num=1;
	// ファイル名取得
	for(int i=0;i<files.size();i++){
		if(excection == Dir::getExtention(files[i]))
			decodeFiles.push_back(Dir::getFileName(files[i]));
	}

	// 並べ直し
	for(int i=0;i<decodeFiles.size();i++){
		for(int j=1;j<100;j++){
			std::stringstream ss;
			ss << str << j << excection << std::flush;
			if(decodeFiles[i]==ss.str()){
				sort.push_back(decodeFiles[i]);
			}
		}
	}

	// ファイルの中身を取得
	vector<int> diceKinds;
	for(int i=0;i<sort.size();i++){
		std::ifstream ifs;
		ifs.open(dir.pwd(sort[i]));
		while(1){
			int kind;
			ifs >> kind;
			if(ifs.eof()) break;
			diceKinds.push_back(kind);			
		}
		ifs.close();
	}

	// ファイルへ出力
	std::ofstream ofs;
	ofs.open(dir.pwd("DiceDecode.txt"));
	for(int i=0;i<diceKinds.size();i++){
		ofs << diceKinds[i] << " " << std::flush;
	}
	ofs.close();

}

void DiceDecode::output(){
	std::cout<<"Decode ..."<<std::endl;
	
	// SenaryDecode
	senaryDecode.init("DiceDecode.txt");
	senaryDecode.output();

	// DiceCodeDecode
	//diceCodeDecode.initRunlength("DiceDecode.txt");
	//diceCodeDecode.outputRunlength();
	
	codeDecode.init("CodeDecode.txt");
	codeDecode.output();
	std::cout<<"End"<<std::endl;
}

void DiceDecode::nowDisplay(){
	std::cout << "now:" << now << std::endl;
	
	switch (diceDetections[now].getMode())
	{
	case 0:
		std::cout << "mode:T " << std::flush;
		break;
	case 1:
		std::cout << "mode:K " << std::flush;
		break;
	case 2:
		std::cout << "mode:C " << std::flush;
		break;
	default:
		break;
	}

	switch (diceDetections[now].getModeType())
	{
	case DiceInfo::small:
		std::cout << "type:S " << std::flush; 
		break;
	case DiceInfo::middle:
		std::cout << "type:M " << std::flush; 
		break;
	case DiceInfo::large:
		std::cout << "type:L " << std::flush; 
		break;
	case DiceInfo::none:
		std::cout << "type:N " << std::flush; 
		break;
	default:
		break;
	}

	std::cout << "kind:" << diceDetections[now].getModeKind() << std::endl;
	std::cout << std::endl;

}

void DiceDecode::drawing(){
//	int interval;
	Timer timer;
	timer.start();
	while (true)
	{
		if(timer.getDiff()>interval){
			timer.lap(interval);
			addFile();
		}
		if(!keyEvent()) break;
		diceDetections[now].draw();
	}

}

}