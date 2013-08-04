#pragma once

#include "PaiDivide.h"
#include "CharArray.h"

namespace pro{

class PRO_EXPORTS InPaiDivide : PaiDivide
{
private:

	// 現在アクセス中のディレクトリ
	long now_dir;
	// 現在アクセス中のファイル
	int now_file;
	// 現在アクセス中のライン
	int now_line;

	// 取得したライン
	CharArray c_str;

public:

	InPaiDivide(void);
	~InPaiDivide(void);

	long getDirNum() const;
	int getOneLineNum() const;
	int getLineNum() const;
	int getFileNum() const;

	long getNowDir() const;
	int getNowFile() const;
	int getNowLine() const;
	
	// ライン取得
	const CharArray& getLine();
	const CharArray& getLine(int line_num);
	const CharArray& getLine(long dir_num,int file_num,int line_num);

	// ファイルを開く
	void open(long dir_num,int file_num);
	// ファイルを閉じる
	void close();

	//ディレクトリ設定
	void setDir(long dir_num);
	//ファイル設定
	void setFile(int file_num);
	// ライン設定
	void setLine(int line_num);

	// 次のディレクトリへ
	bool nextDir();
	// 次のファイルへ
	bool nextFile();
	// 次のラインへ
	const CharArray& nextLine();


};

}
