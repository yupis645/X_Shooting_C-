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
		Error= 99,				//�����G���[���o�����������炱����g��
		OnBulletShot = 2,		//�e�𔭎˂���
	};
	enum class MovePatternID {
		TowardsPlayer,          // ���@�Ɍ������Đi��
		ReverseTowardsPlayer,   // ���@�Ƃ͋t�����ɐi��
		HorizontalTrack,        // Y���̈ʒu�Ɋ֌W�Ȃ����@�̕����Ɍ�����
		AppearFromBottom,       // ��ʂ̉������Ɍ�����
		StraightAccelerate,     //���i���Ȃ����������
		AccelerateTowardsDir,   // �����x�����Z����dir�̕��ֈړ�����
		EscapeX                 // �����x�����Z����x�������ɓ�����
	};

	virtual void Init() ;
	
	void Setshootdown(bool value) { shootdown = value; }
	int GetNumber() { return status.number; }
	int GetAnimNum() { return currentanimnum; }
	int GetPicSize() { return status.pic_size; }

protected:
	EnemyStatus status;
	bool shootdown;		//��e����
	int back_num;		//�z�u����Ă��闠�}�b�v�̔ԍ�
	int back_coord;		//���}�b�v�ɂ�����z�u
	int currentanimnum;	//�A�j���[�V�����p�^�[���̐؂�ւ��^�C�~���O
	int actionpattern;	//�s���p�^�[���ԍ�
	int ownframecount;	//���������ꂽ�u�Ԃ���J�E���g���J�n����(�s���p�^�[���Ɏg�p����)
	float radian;		//�e�̔��ˊp�x
	int direction;		//����
	Vector2 moving;		//�ړ����W

	Vector2 Enemy_Patterns(MovePatternID id);
	void StatusSetup(const EnemyStatus& initstatus);
	void OwnFrameCountUpdate();

};

#endif //ENEMYBASE_H