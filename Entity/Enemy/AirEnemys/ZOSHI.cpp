
//----------------------------------------------------------------------------------------------------------------------------------------
//													�]�V�[
// 
// ��]����e�̂悤�ȓG
// �^�C�v�ɂ���ċ������Ⴂ
//	type 0:	��ʂɓo�ꎞ�̓v���C���[�Ɍ������Đi�ނ��A��莞�Ԍ�Ƀ����_���ɕ����]������
//	type 1: �o�ꎞ������Ԋu�Ńv���C���[�̈ʒu���T�[�`���ĕ����]������
//	type 2: ��ʂ̉�����o�ꂵ�ď�Ɍ������Đi�݁A���Ԋu��̓v���C���[���T�[�`���ĕ����]������
//----------------------------------------------------------------------------------------------------------------------------------------

#include "AirEnemyBase.h"

#include "common.h"
#include "Player.h"

constexpr int   ANIM_UPDATE_INTERVAL = 5;		//�A�j���[�V�����摜�����ւ���t���[����
constexpr int   ACTION_UPDATE_INTERVAL = 120;	//�����]��������̃^�C�~���O

namespace {

	Vector2 GetRandomTargetPositon(const Vector2& pos ) {

		// �����_����X���W
		float targetX = static_cast<float>(std::rand()) / RAND_MAX * ScreenConfig::SRN_W ;

		// �����_����Y���W(����:��ʂ̉���������)
		float targetY = pos.y + static_cast<float>(std::rand()) / RAND_MAX * (ScreenConfig::SRN_H - pos.y);

		return Vector2(targetX, targetY);

 }
}


//========================================================================================
//					�R���X�g���N�^
// 
// �C���X�^���X�����ꂽ���_�ŃX�e�[�^�X�A���W�Ȃǂ̏����擾����
//========================================================================================
ZOSHI::ZOSHI(std::weak_ptr<IPlayer> player, int num)
{
	Create(player, num);		//�C���X�^���X�������ɕK�v�ȃX�e�[�^�X��ݒ肷��
}

//========================================================================================
//								������
// 
// �����o�ϐ���S�ď���������
//========================================================================================
void ZOSHI::Init() {
	EnemyBase::Init();		//�����o�ϐ�������������
}


//========================================================================================
//							����(�X�e�[�^�X�̎擾�Ȃ�)
// ��P���� : �v���C���[�̏����������X�}�[�g�|�C���^
// ��Q���� : �G�̎��ʔԍ��A�y�у^�C�v�B(100�̈ʂ��^�C�v��\�� [203 �Ȃ� type 2�Anumber 3�ƂȂ�])
// 
// �C���X�^���X���ɕK�v�ȏ����擾����
//	1.�X�e�[�^�X�̏����l,�ݒ�l���擾����B
//	2_1.type�� 2 �̎���x���W��player�����苗���b���Đݒ肵�Ay���W����ʂ̈�ԉ��ɐݒ肷��
//  2_2. type 2�ȊO�̎���x���W�̓����_����y���W��0����͂��߂�
//  3.active��type�Ȃ�EnemyBase�̕ϐ��Œ������K�v�Ȃ��̂𒲐�����

//========================================================================================
int ZOSHI::Create(std::weak_ptr<IPlayer> player, int number)
{
	auto useplayer = player.lock();		//�X�}�[�g�|�C���^���ꎞshared_ptr�ɕϊ�����

	//	1.�X�e�[�^�X�̏����l,�ݒ�l���擾����B
	EnemyBase::StatusSetup(EnemyStatusData::ZOSHI);

	
	//  2.active��type�Ȃ�EnemyBase�̕ϐ��Œ������K�v�Ȃ��̂𒲐�����
	AirEnemyBase::Create(useplayer, number);

	//	3_1.��ʉ�����o�ꂷ�����ȃ^�C�v
	if (status.type == 2) {
		position.y = ScreenConfig::SRN_H;
		AirEnemyBase::InitPostionPattern(useplayer->GetPosition().x);
		TergetRadian(useplayer->GetPosition());
	}

	//  3_2. ���̃L�����ƕς��Ȃ��o��
	else {
		AirEnemyBase::InitPostionPattern();

	}


	return 0;
}


//========================================================================================
//							�X�V
// ��P���� : �v���C���[�̏����������X�}�[�g�|�C���^
// 
// EnemyManager�Ɏg���Ă��炤���߂̊֐�
//  AirEnemyBase::Update���ŗL�̃A�N�V������ݒ肵��UniqueUpdate�֐����Ăяo���B
//========================================================================================
int ZOSHI::Update(std::weak_ptr<IPlayer> player)
{
	return  AirEnemyBase::Update(player);
}

//========================================================================================
//							�ŗL�̃A�N�V����
// ��P���� : �v���C���[�̏����������X�}�[�g�|�C���^
// 
//�G�̎�ނɂ���Ă����֐��B
// 1.�A�j���[�V�����̍X�V
// 2.�ݒ肳�ꂽ���W�Ɍ������Ă�����
//========================================================================================
int ZOSHI::UniqueUpdate(std::shared_ptr<IPlayer> player)
{

	// 1.�A�j���[�V�����̍X�V
	AirEnemyBase::AnimUpdate(ANIM_UPDATE_INTERVAL);


	// 2.�ݒ肳�ꂽ���W�Ɍ�������
	Enemy_Patterns(MovePatternID::TowardsTarget);


	return ActionPattern01(player);
	
}


//========================================================================================
//							�A�N�V�����p�^�[��
// ��P���� : �v���C���[�̏����������X�}�[�g�|�C���^
// 
// ���̃t���[���ɓ���A�����]�����e�𔭎˂���
//		type 0:���t���[�����Ƀ����_���̍��W�ɕ����]������
//		type 1:���t���[�����Ƀv���C���[�̍��W�ɕ����]������
//		type 2:����
//========================================================================================
int ZOSHI::ActionPattern01(std::shared_ptr<IPlayer> player_)
{

	// 1.���t���[�����ɓ���
	if (ownframecount % ACTION_UPDATE_INTERVAL == 0)
	{
		Vector2 randomtarget = GetRandomTargetPositon(position);		//�����_���̍��W���擾

		//�^�C�v�ʂ̃A�N�V����
		switch (status.type) {
		case 0:										//type 0:���t���[�����Ƀ����_���̍��W�ɕ����]������
			TergetRadian(randomtarget);		
			break;
		case 1:										//type 1:���t���[�����Ƀv���C���[�̍��W�ɕ����]������
		case 2:										//type 2:����
			TergetRadian(player_->GetPosition());
			break;
		default :
			break;
		}
		
		return OnBulletShot;			//�e������
		
	}
	return 0;
}

