#pragma once

#include"Procon2013/Core/Core.h"
#include<iostream>

namespace pro{

	
/**
   円周率ファイルの分割と読み込みクラス
 */
class PRO_EXPORTS PaiFileDivide
{
private:

//	Dir out_path;			// 出力ディレクトリ
//	std::ifstream in_file;	// 円周率の元ファイルストリーム
//	std::ofstream out_file; // アウトプットストリーム
//
//	/*******************************
//	 *  計算から求めるメンバ
//	 */
//
//	long dir_num;			// 作成ディレクトリ数
//	int last_file_num;		// ラストディレクトリ内のファイル数
//	int last_line_num;		// ラストファイル内のライン数
//	int last_digits;		// ラストラインの桁数
//	boost::uintmax_t digits;// 桁数
//	long all_line_num;		// 全ライン数
//	long all_file_num;		// 全ファイル数
//	bool setting_flag;		// データ取得後かの判定フラグ
//	
//	/*******************************
//	 *   設定メンバ
//	 */
//
//	Dir in_path;			// 入力ファイルディレクトリ
//	Dir out_base_path;		// 出力ベースディレクトリ
//	
//	string in_name;			// 入力ファイル名
//	string out_name;		// 出力ファイル名
//
//	int one_line_num;		// 1ラインの桁数
//	int line_num;			// 1ファイルのライン数
//	int file_num;			// 1ディレクトリのファイル数
//
//	// 初期化関数
//	void init(boost::filesystem::path path,string name);
//
//	/*******************************
//	 *  divide()の補助メソッド
//	 */
//
//	void createDir(int dir_num);
//	void createFile(int dir_num,int file_num,int file_max_num);
//	void createLine(int one_line_num);
//
//
//public:
//	
//	PaiFileDivide(void);
//	PaiFileDivide(string name);
//	PaiFileDivide(boost::filesystem::path path,string name);
//	~PaiFileDivide(void);
//
//	/*******************************
//	 *  プロパティ群
//	 */
//
//	long getDirNum() const;
//	int getOneLineNum() const;
//	int getLineNum() const;
//	int getFileNum() const;
//	const string getOutFileName() const;
//	const string getOutPath() const;
//
//	// ファイルサイズからデータ計算
//	void fileSizeCalc();
//	// 桁数からデータ計算
//	void fileSizeCalc(boost::uintmax_t digits);
//
//	// 分割実行メソッド
//	void divide();
//
//	// PaiDivide.iniからデータ取得
//	void getIniSetting();
//	// データからPaiDivide.iniの作成
//	void createIniFile();
//
//	//void setNums(int file_num,int line_num,int one_line_num);
//
//	// ライン取得
//	const char* getLine(long dir_num,int file_num,int line_num);
//
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
	//bool setting_flag;	// データ取得後かの判定フラグ

	// 初期化関数
	//void init();

public:
	
	PaiFileDivide(void);
	~PaiFileDivide(void);
	
	// PaiDivide.iniからデータ取得
	void getIniSetting();
	
	// 桁数からデータ計算
	void fileSizeCalc(boost::uintmax_t digits);

};

class PRO_EXPORTS PaiFileDivideOut : PaiFileDivide
{
private:
	
	std::ifstream input_file;
	string input_name;
	Dir input_path;

	bool setting_flag;		// データ取得後かの判定フラグ
	
	// 初期化関数
	void init(boost::filesystem::path path,string name);

	/*******************************
	 *  divide()の補助メソッド
	 */

	void createDir(int dir_num);
	void createFile(int dir_num,int file_num,int file_max_num);
	void createLine(int one_line_num);

public:
	
	PaiFileDivideOut(void);
	~PaiFileDivideOut(void);

	// ファイルサイズからデータ計算
	void fileSizeCalc();
	// 分割実行メソッド
	void divide();
	// データからPaiDivide.iniの作成
	void createIniFile();
	
};

class PRO_EXPORTS PaiFileDivideIn : PaiFileDivide
{

};

class PRO_EXPORTS PaiMatch
{
private:



public:
	PaiMatch(void);
	~PaiMatch(void);
};

}
