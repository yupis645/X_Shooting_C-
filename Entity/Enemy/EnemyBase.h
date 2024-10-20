#pragma once
#include "Game.h"
#include "IPlayer.h"

class EnemyBase:public GameObject {
public:
	EnemyBase();
	~EnemyBase(){}

	virtual int Init() = 0;
	virtual Vector2 Enemy_Patterns( int movepattrnnumber);

	virtual int Create(int number,int typenumber) = 0;
	virtual int AnimUpdate(int framecount, int updatecount) = 0;
	virtual int ActionUpdate(int framecount) = 0;
	virtual int UniqueUpdate(int framecount) = 0;
	virtual int Draw() = 0;


	virtual void Setshootdown(bool value) { shootdown = value; }

protected:
	EnemyStatusData status;
	bool shootdown;			//��e����
	int back_num;		//�z�u����Ă��闠�}�b�v�̔ԍ�
	int back_coord;		//���}�b�v�ɂ�����z�u
	int type;		//����̂̈Ⴄ����
	int direction;		//����
	int currentanim_number;		//�A�j���[�V�����p�^�[���̐؂�ւ��^�C�~���O
	int actionpattern;		//�s���p�^�[���ԍ�
	int ownframecount;	//���������ꂽ�u�Ԃ���J�E���g���J�n����(�s���p�^�[���Ɏg�p����)
	int currentspeed;
	float radian;
	Vector2 moving;
};