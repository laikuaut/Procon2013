#include"Procon2013\Procon2013.h"
using namespace pro;
using namespace std;

int main(int argc, char* argv[]){
	try{
		Camera camera;
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