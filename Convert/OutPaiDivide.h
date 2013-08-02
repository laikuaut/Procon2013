#pragma once

#include "PaiDivide.h"

namespace pro{

class PRO_EXPORTS OutPaiDivide : PaiDivide
{
private:
	
	std::ifstream input_file;
	string input_name;
	Dir input_path;

	bool dot_flag;
	
	// 初期化関数
	void init(boost::filesystem::path i_full_path);
	void init(boost::filesystem::path i_path,string i_name);

	/*******************************
	 *  divide()の補助メソッド
	 */

	void createDir(int dir_num);
	void createFile(int dir_num,int file_num,int file_max_num);
	void createLine(int one_line_num);
	void createFirstLine(int one_line_num);
	void createFirstDir();
	void createLastDir();

	// ファイルサイズから桁数
	void setDigits();
	// 少数点のあるなし
	void setDotFlag();
	
public:
	OutPaiDivide(void);
	OutPaiDivide(boost::filesystem::path i_full_path);
	OutPaiDivide(boost::filesystem::path i_path,string i_name);
	~OutPaiDivide(void);

	// デフォルト設定のPaiDivide.iniを作成
	void createIniFileDefault();
	// 任意設定のPaiDivide.iniを作成
	void createIniFile(string path
					,string name
					,boost::uintmax_t digits
					,int file_num
					,int line_num
					,int one_line_num);

	// 分割実行メソッド
	void divide();
};

}