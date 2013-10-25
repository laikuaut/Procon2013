#include"Procon2013\Procon2013.h"
using namespace pro;
using namespace std;

int main(int argc, char* argv[]){
	string path;

	try{
		
		Dir dir = Dir();
		ptree pt;
		
		// 設定ファイル作成
		if(!dir.isExist("ManualCam.ini")){
			cout << "ManualCam.ini.iniを作成します。" << endl;
			pt.put("File.path",dir.pwd());
			write_ini("ManualCam.ini",pt);
			exit(EXIT_SUCCESS);
		}

		// 設定読み込み
		read_ini("ManualCam.ini",pt);
		if (boost::optional<string> value = pt.get_optional<string>("File.path")){
			path = value.get();
		}
		
		Camera camera;

		// ディレクトリ設定
		camera.setManualDirectoryPath(path);
		camera.setDirCreateFlag(Dir::NONE);
		camera.createManualDirectory();
		camera.manualCapture();

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