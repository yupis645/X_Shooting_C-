#ifndef ENEMYBASE_H
#define ENEMYBASE_H

class IPlayer;
class Vector2;

#include "Game.h"

class EnemyBase:public GameObject {
public:
	EnemyBase();
	~EnemyBase(){}
	enum UpdateReturnID {
		Error= 99,
		OnBulletShot = 2,
	};

	virtual void Init() ;

	virtual int Create(std::shared_ptr<IPlayer> pl,int number,int typenumber = 0) = 0;

	virtual int Update(std::shared_ptr<IPlayer> pl) = 0;
	virtual int UniqueUpdate(std::shared_ptr<IPlayer> pl) = 0;

	virtual int AnimUpdate(int UpdateInterval) = 0;


	virtual void Setshootdown(bool value) { shootdown = value; }

protected:
	EnemyStatusData status;
	bool shootdown;			//��e����
	int back_num;		//�z�u����Ă��闠�}�b�v�̔ԍ�
	int back_coord;		//���}�b�v�ɂ�����z�u
	int type;		//����̂̈Ⴄ����
	int direction;		//����
	int currentanimnum;		//�A�j���[�V�����p�^�[���̐؂�ւ��^�C�~���O
	int actionpattern;		//�s���p�^�[���ԍ�
	int ownframecount;	//���������ꂽ�u�Ԃ���J�E���g���J�n����(�s���p�^�[���Ɏg�p����)
	float currentspeed;
	float radian;
	Vector2 moving;

	Vector2 Enemy_Patterns(int movepattrnnumber);
	void StatusSetup(int number, int typenumber = 0);
	void OwnFrameCountUpdate();

};

#endif //ENEMYBASE_H