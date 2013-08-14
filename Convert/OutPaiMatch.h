#pragma once

#include"PaiMatch.h"

namespace pro{

class OutPaiMatch : public PaiMatch
{
private:
	int length;			// マッチングするときの文字列長さ
	int line_length;	// 文字列が跨ぐラインの長さ
	
	InPaiDivide ipd;	// 円周率分割ファイルデータ取得クラス
	
	CharArray c_str;	// マッチ保存文字列	

	bool load_flag;		// ロードフラグ


	// 文字列を更新
	void setStr();		
	// 文字列一致
	bool match();		
	// 一列文字列一致
	void matchOneLine();
	// 一致座標出力
	void output();		

	/*****************************
	 *  途中経過
	 */
	// 途中経過保存
	void save();		
	// 最後まで一致した時の保存
	void last_save();	
	// 途中経過ロード
	void load();		
	// 次の数値にアクセス
	bool next();

	/*****************************
	 *  オーバーライド関数
	 */
	// 初期化関数
	void init();		
	// 開く
	void open();		
	// 現在状況の表示
	void nowDisplay();	
	// キーイベント関数
	void keyEvent();	

public:

	OutPaiMatch(int digits=1,CharArrayNumeric::NumKind kind=CharArrayNumeric::HEX);
	~OutPaiMatch(void);
	
	void matching();

};

}
