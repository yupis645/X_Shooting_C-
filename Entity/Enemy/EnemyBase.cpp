#include "EnemyBase.h"


//==========================================================
//				�R���X�g���N�^
//==========================================================
EnemyBase::EnemyBase() :shootdown(false), back_num(0), back_coord(0), type(0), direction(0),
						currentanim_number(0), actionpattern(0), ownframecount(0), radian(0), currentspeed(0), moving(Vector2::zero)
{}


//==========================================================
//				������
//==========================================================

int EnemyBase::Init()
{
	status.Init();
	shootdown = false;			//��e����
	back_num = 0;		//�z�u����Ă��闠�}�b�v�̔ԍ�
	back_coord = 0;		//���}�b�v�ɂ�����z�u
	type = 0;		//����̂̈Ⴄ����
	direction = 0;		//����
	currentanim_number = 0;		//�A�j���[�V�����p�^�[���̐؂�ւ��^�C�~���O
	actionpattern = 0;		//�s���p�^�[���ԍ�
	ownframecount = 0;	//���������ꂽ�u�Ԃ���J�E���g���J�n����(�s���p�^�[���Ɏg�p����)
	currentspeed = 0;
	radian = 0;
	moving = 0;
	Vector2::zero;

	return 0;
}


Vector2 EnemyBase::Enemy_Patterns(int movepattrnnumber)
{
	int dir_search = CHIP_SIZE + (CHIP_SIZE - (CHIP_SIZE * currentspeed));

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
			position.y = SRN_H;
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
