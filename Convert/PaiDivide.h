#pragma once

#include"Procon2013/Core/Core.h"
#include<iostream>

namespace pro{

class PRO_EXPORTS PaiDivide
{
protected:

	std::fstream fs;

	/*******************************
	 *   設定メンバ
	 */

	Dir path;				// アクセス用ファイルディレクトリ
	Dir base_path;			// ベースディレクトリ
		
	string name;			// ファイル名

	int one_line_num;		// 1ラインの桁数
	int line_num;			// 1ファイルのライン数
	int file_num;			// 1ディレクトリのファイル数

	/*******************************
	 *  計算から求めるメンバ
	 */

	long dir_num;			// 作成ディレクトリ数
	int last_file_num;		// ラストディレクトリ内のファイル数
	int last_line_num;		// ラストファイル内のライン数
	int last_digits;		// ラストラインの桁数
	boost::uintmax_t digits;// 桁数
	long all_line_num;		// 全ライン数
	long all_file_num;		// 全ファイル数

public:
	PaiDivide(void);
	~PaiDivide(void);
	
	// PaiDivide.iniからデータ取得
	bool getIniSetting();
	
	// 桁数からデータ計算
	void fileSizeCalc(boost::uintmax_t digits);
};

}