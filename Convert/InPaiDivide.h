#pragma once

#include "PaiDivide.h"
#include "CharArray.h"

namespace pro{

class PRO_EXPORTS InPaiDivide : PaiDivide
{
private:

	// ���݃A�N�Z�X���̃f�B���N�g��
	long now_dir;
	// ���݃A�N�Z�X���̃t�@�C��
	int now_file;
	// ���݃A�N�Z�X���̃��C��
	int now_line;

	// �擾�������C��
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
	
	// ���C���擾
	const CharArray& getLine();
	const CharArray& getLine(int line_num);
	const CharArray& getLine(long dir_num,int file_num,int line_num);

	// �t�@�C�����J��
	void open(long dir_num,int file_num);
	// �t�@�C�������
	void close();

	//�f�B���N�g���ݒ�
	void setDir(long dir_num);
	//�t�@�C���ݒ�
	void setFile(int file_num);
	// ���C���ݒ�
	void setLine(int line_num);

	// ���̃f�B���N�g����
	bool nextDir();
	// ���̃t�@�C����
	bool nextFile();
	// ���̃��C����
	const CharArray& nextLine();


};

}
