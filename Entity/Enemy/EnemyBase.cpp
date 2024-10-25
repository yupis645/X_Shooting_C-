#include "EnemyBase.h"

#include "common.h"
#include "IPlayer.h"


namespace {
	constexpr int OWNFRAMECOUNT_LIMIT = 1000;

}

//==========================================================
//				�R���X�g���N�^
//==========================================================
EnemyBase::EnemyBase() :status(EnemyStatusData::DUMMY),shootdown(false), back_num(0), back_coord(0), direction(0), actionpattern(0),
						currentanimnum(0),  ownframecount(0), radian(0), moving(Vector2::zero)
{}


//==========================================================
//				������
//==========================================================

void EnemyBase::Init()
{
	EnemyStatus status = EnemyStatusData::DUMMY;
	back_num = 0;		//�z�u����Ă��闠�}�b�v�̔ԍ�
	back_coord = 0;		//���}�b�v�ɂ�����z�u
	direction = 0;		//����
	actionpattern = 0;
	currentanimnum = 0;		//�A�j���[�V�����p�^�[���̐؂�ւ��^�C�~���O
	ownframecount = 0;	//���������ꂽ�u�Ԃ���J�E���g���J�n����(�s���p�^�[���Ɏg�p����)
	radian = 0;
	moving = 0;
	Vector2::zero;
	GameObject::InitClear();
}



Vector2 EnemyBase::Enemy_Patterns(MovePatternID id)
{

	switch (id) {
		/*���@�Ɍ������Đi��*/
	case MovePatternID::TowardsPlayer:
		position.x += status.speed * cos(radian);		    //X���̈ړ�
		position.y += status.speed * sin(radian);		    //Y���̈ړ�
		break;

		/*���@�Ƃ͋t�����ɐi��*/
	case MovePatternID::ReverseTowardsPlayer:
		position.x -= status.speed * cos(radian);		    //X���̈ړ�
		position.y -= status.speed * sin(radian);		    //Y���̈ړ�
		break;

		/*Y���̈ʒu�Ɋ֌W�Ȃ����@�̕����Ɍ�����*/
	case MovePatternID::HorizontalTrack:
		position.x += status.speed * cos(radian);		    //X���̈ړ�
		position.y += status.speed;
		break;

		/*��ʂ̉�����o������*/
	case MovePatternID::AppearFromBottom:
		position.x += status.speed * cos(radian);		    //X���̈ړ�
		position.y -= status.speed;		                    //Y���̈ړ�
		break;
		/*���̂܂ܒ��i����*/
	case MovePatternID::StraightAccelerate:
		position.y += status.speed;		                    //Y���̈ړ�
		break;

		/*�����x�����Z����dir�̕��ֈړ�����*/
	case MovePatternID::AccelerateTowardsDir:
		position.x -= 1.0f * cos(radian) * direction;		//X���̈ړ�
		position.y -= status.speed * status.acceleration;	//Y���̈ړ�

		/*����*/
		status.speed += status.speed * status.acceleration;

		break;


		/*�����x�����Z�����������ɓ�����*/
	case MovePatternID::EscapeX:
		position.y++;
		position.x -= status.speed * direction;		        //X���̈ړ�
		/*����*/
		status.speed += status.speed * status.acceleration;
		break;

	}

	return 0;

}


void EnemyBase::StatusSetup(const EnemyStatus& initstatus)
{
	//��b�X�e�[�^�X���R�s�[ or �e�l�̃Z�b�g
	status = initstatus;


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
