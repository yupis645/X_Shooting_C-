#include "EnemyBase.h"

#include "common.h"
#include "IPlayer.h"


namespace {
	constexpr int OWNFRAMECOUNT_LIMIT = 1000;

}

//==========================================================
//				�R���X�g���N�^
//==========================================================
EnemyBase::EnemyBase() :shootdown(false), back_num(0), back_coord(0), type(0), direction(0),
						currentanimnum(0),  ownframecount(0), radian(0), currentspeed(0), moving(Vector2::zero)
{}


//==========================================================
//				������
//==========================================================

void EnemyBase::Init()
{
	status.Init();
	shootdown = false;			//��e����
	back_num = 0;		//�z�u����Ă��闠�}�b�v�̔ԍ�
	back_coord = 0;		//���}�b�v�ɂ�����z�u
	type = 0;		//����̂̈Ⴄ����
	direction = 0;		//����
	currentanimnum = 0;		//�A�j���[�V�����p�^�[���̐؂�ւ��^�C�~���O
	ownframecount = 0;	//���������ꂽ�u�Ԃ���J�E���g���J�n����(�s���p�^�[���Ɏg�p����)
	currentspeed = 0;
	radian = 0;
	moving = 0;
	Vector2::zero;
}


Vector2 EnemyBase::Enemy_Patterns(int movepattrnnumber)
{
	int dir_search = MapConfig::CHIP_SIZE + (MapConfig::CHIP_SIZE - (MapConfig::CHIP_SIZE * currentspeed));

	switch (movepattrnnumber) {
		/*���@�Ɍ������Đi��*/
	case 0:

		position.x += (float)currentspeed * cos(radian);		//X���̈ړ�
		position.y += (float)currentspeed * sin(radian);		//Y���̈ړ�
		break;


		/*Y���̈ʒu�Ɋ֌W�Ȃ����@�̕����Ɍ�����*/
	case 1:
		position.x += (float)currentspeed * cos(radian);		//X���̈ړ�
		position.y += currentspeed;
		break;

		/*��ʂ̉�����o������*/
	case 2:
		if (ownframecount <= 5) {
			position.y = ScreenConfig::SRN_H;
		}
		position.x += (float)currentspeed * cos(radian);		//X���̈ړ�
		position.y -= currentspeed;		//Y���̈ړ�
		break;
		/*���̂܂ܒ��i����*/
	case 3:
		position.y += (float)currentspeed;		//Y���̈ړ�
		break;
		/*�����x�����Z����dir�̕��ֈړ�����*/
	case 4:
		position.x -= (float)1 * cos(radian) * direction;		//X���̈ړ�
		position.y -= (float)currentspeed * status.acceleration;		//Y���̈ړ�

		/*����*/
		currentspeed += currentspeed * status.acceleration;

		break;

		/*�����x�����Z�����������ɓ�����*/
	case 5:
		position.y++;
		position.x -= (float)currentspeed * direction;		//X���̈ړ�
		/*����*/
		currentspeed += currentspeed * status.acceleration;
		break;

	}

	return 0;
}


void EnemyBase::StatusSetup(int number, int typenumber)
{
	type = typenumber;

	//number�̕S�̈ʂ̓G�l�~�[��Type��\��(100 = Type:1 , 200 = Type:2)
	if (number >= 100) {
		type = number / 100;								//�i���o�[��100�Ŋ�����Type�����o��
		number = number - (100 * type);						//100�̈ʂ���菜�����G�̃i���o�[�����o��
	}

	//_e->enemy[EmptyNum] = A_enemyDate[number];
	//��b�X�e�[�^�X���R�s�[ or �e�l�̃Z�b�g
	status = A_ENEMY_DATA_ARRAY[number];

	currentspeed = status.speed;

	/*�����̍s���p�^�[���̂���G�̃X�e�[�^�X�ύX*/
	////�W�\�[
	//if (_e->enemy[EmptyNum].number == 3) {
	//	if (_e->enemy[EmptyNum].type > 0 && _e->enemy[EmptyNum].type < 3) { _e->enemy[EmptyNum].points = 100; }	//Type�ɂ�链�_�̕ϓ�
	//}
	////�U�K�[�g
	//else if (_e->enemy[EmptyNum].number == 7) {
	//	if (_e->enemy[EmptyNum].type == 0) { _e->enemy[EmptyNum].points = 100; }
	//	if (_e->enemy[EmptyNum].type == 1) { _e->enemy[EmptyNum].points = 150;	_e->enemy[EmptyNum].speed = 4.0; }
	//	if (_e->enemy[EmptyNum].type == 2) { _e->enemy[EmptyNum].points = 200; }
	//	if (_e->enemy[EmptyNum].type == 3) { _e->enemy[EmptyNum].points = 300;	_e->enemy[EmptyNum].speed = 4.0; }
	//}

}

void EnemyBase::OwnFrameCountUpdate()
{
	ownframecount++;

	int Limit = OWNFRAMECOUNT_LIMIT;	//Clamp�Ŏg�����߂�int�ɕϊ�
	Clamp(ownframecount, 0, Limit);
}
