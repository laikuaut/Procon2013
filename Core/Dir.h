#pragma once

#include"Core.h"

#include<string>
#include<boost/filesystem.hpp>

// ディレクトリにあってはいけない文字を探索する正規表現
#define DIR_REGEX_STR "[:*?\"<>|]"

namespace pro{

// error C2061: 構文エラー : 識別子 'DirException'
class DirException;

/**               メモ 
 * boost::filesystem::path と std::string は
 * オーバーロード時あいまいな型となるため
 * boost:filesystem::path に引数を統一する。 
 **/

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

	Dir();
	Dir(const boost::filesystem::path& path);

	~Dir(void);
	
	static bool isPath(const boost::filesystem::path& path);
	
	const std::string pwd() const;
	
	void cd(const boost::filesystem::path& path);
	void cd(const boost::filesystem::path& path,const DirException& e);

	bool create(int option = NONE);
	bool create(const boost::filesystem::path& path,int option = NONE);
	bool remove() const;
	bool remove(const boost::filesystem::path& path) const;
	boost::uintmax_t remove_all() const;
	boost::uintmax_t remove_all(const boost::filesystem::path& path) const;

	static const char* test();

	void setErrorShow(bool errorShow);

};

}