#include"Procon2013\Procon2013.h"

using namespace pro;
using namespace std;

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/optional.hpp>

int main(){

	string ans,src;
	Dir dir = Dir();
	ptree pt;
	if(!dir.isExist("StringMatching.ini")){
		cout << "StringMatching.ini���쐬���܂��B" << endl;
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
		cout << ans << "������܂���B" <<endl;
	}
	else if(!dir.isExist(src)){
		cout << src << "������܂���B" <<endl;
	}else{
		cout << StringCalc::fileStringMatching(ans,src) << endl;
	}
}