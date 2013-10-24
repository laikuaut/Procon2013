#include"Procon2013\Procon2013.h"
using namespace pro;
using namespace std;

int main(int argc, char* argv[]){

	int interval;
	int time;

	cout << "ŽŽ‡ŽžŠÔ > " << flush;
	cin >> time;
	cout << "ŠÔŠu > " << flush;
	cin >> interval;

	try{
		Camera camera;
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