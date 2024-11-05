#include "AirEnemyBase.h"

#include "common.h"
#include "Player.h"


namespace {
	constexpr int   ANIM_UPDATE_INTERVAL  = 5;		//�A�j���[�V�����摜�����ւ���t���[����
	constexpr int   PLAYER_TRACKING_FRAME = 5;		//��ʂɓo�ꂵ�Ă��̒l�����̊Ԃ̓v���C���[�̈ʒu��ߑ���������B
	constexpr int   MOVING_FRAME_TIME	  = 100;	//�o�����Ă���i�ݑ����鎞��
}


//========================================================================================
//					�R���X�g���N�^
// 
// �C���X�^���X�����ꂽ���_�ŃX�e�[�^�X�A���W�Ȃǂ̏����擾����
//========================================================================================
TORKAN::TORKAN(std::weak_ptr<IPlayer> player, int num)
{
	Create(player, num);		//�C���X�^���X�������ɕK�v�ȃX�e�[�^�X��ݒ肷��
}

//========================================================================================
//								������
// 
// �����o�ϐ���S�ď���������
//========================================================================================
void TORKAN::Init() {
	EnemyBase::Init();		//�����o�ϐ�������������
}


//========================================================================================
//							����(�X�e�[�^�X�̎擾�Ȃ�)
// ��P���� : �v���C���[�̏����������X�}�[�g�|�C���^
// ��Q���� : �G�̎��ʔԍ��A�y�у^�C�v�B(100�̈ʂ��^�C�v��\�� [203 �Ȃ� type 2�Anumber 3�ƂȂ�])
// 
// �C���X�^���X���ɕK�v�ȏ����擾����
//	1.�X�e�[�^�X�̏����l,�ݒ�l���擾����B
//	2.�o�����̍��W��ݒ肷��
//  3.active��type�Ȃ�EnemyBase�̕ϐ��Œ������K�v�Ȃ��̂𒲐�����
//========================================================================================
int TORKAN::Create(std::weak_ptr<IPlayer> player, int number)
{
	auto useplayer = player.lock();		//�X�}�[�g�|�C���^���ꎞshared_ptr�ɕϊ�����

	//	1.�X�e�[�^�X�̏����l,�ݒ�l���擾����B
	EnemyBase::StatusSetup(EnemyStatusData::TORKAN);

	//	2.�o�����̍��W��ݒ肷��
	AirEnemyBase::InitPostionPattern();

	//  3.active��type�Ȃ�EnemyBase�̕ϐ��Œ������K�v�Ȃ��̂𒲐�����
	AirEnemyBase::Create(useplayer, number);

	return 0;
}


//========================================================================================
//							�X�V
// ��P���� : �v���C���[�̏����������X�}�[�g�|�C���^
// 
// EnemyManager�Ɏg���Ă��炤���߂̊֐�
//  AirEnemyBase::Update���ŗL�̃A�N�V������ݒ肵��UniqueUpdate�֐����Ăяo���B
// �Ԃ�l�� "OnBulletShot" �Ȃ�EnemyManager����G�̃V���b�g�����悤�ɖ��߂���
//========================================================================================
int TORKAN::Update(std::weak_ptr<IPlayer> player)
{
	return  AirEnemyBase::Update(player);
}

//========================================================================================
//							�ŗL�̃A�N�V����
// ��P���� : �v���C���[�̏����������X�}�[�g�|�C���^
// 
//�G�̎�ނɂ���Ă����֐��B
// �A�j���[�V�����̍X�V����W�̍X�V�Ȃǂ��s��
// 1.�o�ꂩ��K��t���[���ȓ��܂ł�player�̍��W�ɑ΂���p�x���擾��������
// 2.�A�j���[�V�����̍X�V
// 3.�A�N�V�����p�^�[���ɂ���ē�����ւ���
//========================================================================================
int TORKAN::UniqueUpdate(std::shared_ptr<IPlayer> player)
{

	// 1.���̃t���[���l���Ⴂ�Ɠ��������ɂȂ�₷��
	if (ownframecount < PLAYER_TRACKING_FRAME) TergetRadian(player->GetPosition());

	// 2.TORKEN�̓A�j���[�V�����͓���̏�ʂł����������Ȃ��̂ŁA���j���̂ݎ����X�V����
	if (shootdown) {
		AirEnemyBase::AnimUpdate(ANIM_UPDATE_INTERVAL);
	}
	
	// 3.�e�A�N�V�����p�^�[��

	if (actionpattern == 0)	return ActionPattern01();	//pattern0 : ��苗���܂Ői�񂾌�A�ˌ�������

	if (actionpattern == 1)	ActionPattern02(player);			//pattern1 : �A�j���[�V�����I���܂ł������Ȃ�
	
	if (actionpattern == 2)	ActionPattern03();			//pattern0 : �v���C���[�Ƃ͋t�̂ق��ɓ�����
	
	return 0;
}


//========================================================================================
//							�A�N�V�����p�^�[���O
// 
// �o�����ɂ����v���C���[�̈ʒu�Ɍ������đO�i����
// ��莞�Ԍ�A�ˌ������Ă��玟�̃p�^�[�����ڍs����
//========================================================================================
int TORKAN::ActionPattern01()
{
	//�o�����Ƀv���C���[���������W�Ɍ������Đi��
	Enemy_Patterns(MovePatternID::TowardsTarget);

	//��莞�Ԃ���������ˌ������ăp�^�[����i�߂�
	if (ownframecount >= MOVING_FRAME_TIME) {

		actionpattern++;			//�p�^�[����i�߂�
		return OnBulletShot;		//�ˌ���EnemyManager�ɓ`����
	}
	return 0;
}

//========================================================================================
//							�A�N�V�����p�^�[�� 1
// 
// �A�j���[�V�����𓮂����B���̊Ԃ͈ړ��͂��Ȃ�
// �A�j���[�V����������̓v���C���[�̈ʒu���ēx�擾����
//========================================================================================
void TORKAN::ActionPattern02(std::shared_ptr<IPlayer> player) {

	if (ownframecount % ANIM_UPDATE_INTERVAL == 0) {	        //���t���[���̂��тɓ���
		if (currentanimnum < status.anim_sum) {				    //�A�j���[�V�����ԍ����A�j���[�V�������̍ő��菭�Ȃ���Ώ����ɓ���
			currentanimnum++;									//�A�j���[�V�����ԍ���i�߂�
								
		}
		else {                                                  //�A�j���[�V�������ő吔�𒴂�����
			TergetRadian(player->GetPosition());				//�v���C���[�̈ʒu���擾����
			actionpattern++;									//�p�^�[����i�߂�
		}
	}
}
//========================================================================================
//							�A�N�V�����p�^�[�� 2
// 
// �擾�����ʒu�̋t�����ɓ�����
//========================================================================================
void TORKAN::ActionPattern03()
{
	//���Ε����Ɍ������ē�������
	Enemy_Patterns(MovePatternID::ReverseTowardsTarget);		//�s���p�^�[�� 5:�����x�����Z�����������ɓ�����


}
