#include"Procon2013\Procon2013.h"
using namespace pro;
using namespace std;

int main(int argc, char* argv[]){

	int interval;
	int time;
	string path;

	//string ans,src;
	
	try{

		Dir dir = Dir();
		ptree pt;
		
		// �ݒ�t�@�C���쐬
		if(!dir.isExist("AutoCam.ini")){
			cout << "AutoCam.ini.ini���쐬���܂��B" << endl;
			pt.put("Timer.allTime","600");
			pt.put("Timer.interval","10");
			pt.put("File.path",dir.pwd());
			write_ini("AutoCam.ini",pt);
			exit(EXIT_SUCCESS);
		}

		// �ݒ�ǂݍ���
		read_ini("AutoCam.ini",pt);
		if (boost::optional<int> value = pt.get_optional<int>("Timer.allTime")) {
			time = value.get();
		}
		if (boost::optional<int> value = pt.get_optional<int>("Timer.interval")) {
			interval = value.get();
		}
		if (boost::optional<string> value = pt.get_optional<string>("File.path")){
			path = value.get();
		}
		
		Camera camera;

		// �f�B���N�g���ݒ�
		camera.setAutoDirectoryPath(path);
		camera.setDirCreateFlag(Dir::NONE);
		camera.createAutoDirectory();

		// �B�e
		camera.autoCapture(interval,time);
	}catch(const OutOfRangeException<long>& e){
		e.showError();
	}catch(const OutOfRangeException<int>& e){
		e.showError();
	}catch(const DirException& e){
		e.showError();
	}catch(const boost::filesystem::filesystem_error& e){
		cout << e.what() <<endl;
	}catch(const CameraException& e){
		e.showError();
	}

	return 0;
}