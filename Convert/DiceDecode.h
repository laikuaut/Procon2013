#pragma once

#include"Procon2013\Core\Core.h"
#include"Procon2013\Dice\DiceDetection.h"

namespace pro{

class DiceDecode
{
private:

	vector<DiceDetection> diceDetections;
	vector<string> names;
	Dir dir;
	int now;
	int num;
	vector<int> outPacketNums;

	void readIni();
	void addFile();

	void keyEvent();

	// Encode�o�͂̃p�P�b�g�o�^
	void packetRegist();
	void packetRegistDisplay();
	void packetDisplay();

	// �f�R�[�h�}�[�W
	void packetMarge();

	// ���[�h�⌻�݂̔ԍ��\��
	void nowDisplay();

public:
	DiceDecode(void);
	~DiceDecode(void);

	void init();

	void drawing();
	void draw();

};

// �p�P�b�g�e�L�X�g���R���\�[���ɕ\������B


}