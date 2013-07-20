#pragma once

#include"Core.h"

#include<string>
#include<boost/filesystem.hpp>

// ディレクトリにあってはいけない文字を探索する正規表現
#define DIR_REGEX_STR "[:*?\"<>|]"

namespace pro{

// error C2061: 構文エラー : 識別子 'DirException'
class DirException;

class PRO_EXPORTS Dir
{
public:

	typedef enum CreateOption{
		NONE = 0,					// 設定なし
		ANOTHER_CREATE = 1,			// 存在した場合ほかに作る
		OVER_WRITE_REMOVE_ALL = 2,	// 存在した場合すべて消して作り直す
		OVER_WRITE = 4,				// 存在し空の場合消して作り直す
		CREATE_DIRS = 8				// 中間ディレクトリを作成する
	}CreateOption;

private:

	boost::filesystem::path path;

	bool ErrorShow;

//#pragma warning(push)
//#pragma warning(disable:4251) // 解決できない警告を抑制
//	boost::regex const regex;
//#pragma warning(pop)

public:
	Dir(bool errorShow = false);
	Dir(std::string path,bool errorShow = false);
	~Dir(void);
	
	const std::string pwd() const;
	void cd(std::string path);
	void cd(std::string path,DirException e);

	bool create(int option = NONE);
	bool create(std::string path,int option = NONE);
	bool remove();
	bool remove(std::string path);
	boost::uintmax_t remove_all();
	boost::uintmax_t remove_all(std::string path);

	static const char* test();
	
	static bool isPath(string path);
	static bool isPath(boost::filesystem::path path);
	

};

}