#include"Procon2013\Procon2013.h"

using namespace pro;
using namespace std;

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/optional.hpp>

int main(){

	string ans,src;
	Dir dir = Dir();
	boost::posix_time::ptime ptime;
	ptree pt;
	if(!dir.isExist("StringMatching.ini")){
		cout << "StringMatching.ini‚ðì¬‚µ‚Ü‚·B" << endl;
		pt.put("File.ans","");
		pt.put("File.src","");
		write_ini("StringMatching.ini",pt);
		exit(EXIT_SUCCESS);
	}

	read_ini("StringMatching.ini",pt);
	if (boost::optional<string> value = pt.get_optional<string>("File.ans")) {
		ans = value.get();
	}
	if (boost::optional<string> value = pt.get_optional<string>("File.src")) {
		src = value.get();
	}

	if(!dir.isExist(ans)){
		cout << ans << "‚ª‚ ‚è‚Ü‚¹‚ñB" <<endl;
	}
	else if(!dir.isExist(src)){
		cout << src << "‚ª‚ ‚è‚Ü‚¹‚ñB" <<endl;
	}else{
		cv::namedWindow("stringmatchi");
		ptime = dir.getLastWriteTime(src);
		StringCalc::fileStringMatching(ans,src,true);
		while(cv::waitKey(30)!='q'){
			if(dir.getLastWriteTime(src)!=ptime){
				system("cls");
				ptime = dir.getLastWriteTime(src);
				StringCalc::fileStringMatching(ans,src,true);
			}
		}
	}
}