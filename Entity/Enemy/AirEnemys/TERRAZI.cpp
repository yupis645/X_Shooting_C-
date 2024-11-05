#include "AirEnemyBase.h"

#include "Player.h"


namespace {
	constexpr int   ANIM_UPDATE_INTERVAL = 5;
	constexpr float DECELERATION         = 0.2f;
	constexpr float DECELERATION_LINIT   = 0.6f;
	constexpr int   SHOT_INTERVAL        = 40;
	constexpr float SPPED_LIMIT			 = 100;		//�o�����Ă���i�ݑ����鎞��

}



//========================================================================================
//					�R���X�g���N�^
// 
// �C���X�^���X�����ꂽ���_�ŃX�e�[�^�X�A���W�Ȃǂ̏����擾����
//========================================================================================
TERRAZI::TERRAZI(std::weak_ptr<IPlayer> player, int num)
{
	Create(player, num);
}
//========================================================================================
//								������
// 
// �����o�ϐ���S�ď���������
//========================================================================================
void TERRAZI::Init() {
	EnemyBase::Init();
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
int TERRAZI::Create(std::weak_ptr<IPlayer> player, int number)
{
	auto useplayer = player.lock();

	EnemyBase::StatusSetup(EnemyStatusData::TERRAZI);


	AirEnemyBase::InitPostionPattern(useplayer->GetPosition().x);

	AirEnemyBase::Create(useplayer, number);

	return 0;
}
//========================================================================================
//							�X�V
// ��P���� : �v���C���[�̏����������X�}�[�g�|�C���^
// 
// EnemyManager�Ɏg���Ă��炤���߂̊֐�
//  AirEnemyBase::Update���ŗL�̃A�N�V������ݒ肵��UniqueUpdate�֐����Ăяo���B
//========================================================================================
int TERRAZI::Update(std::weak_ptr<IPlayer> player)
{
	return  AirEnemyBase::Update(player);
}

//========================================================================================
//							�ŗL�̃A�N�V����
// ��P���� : �v���C���[�̏����������X�}�[�g�|�C���^
// 
//�G�̎�ނɂ���Ă����֐��B
// 1.�o�ꐔ�t���[���܂ł̓v���C���[�̈ʒu���擾��������
// 2.�A�N�V�����p�^�[���ԍ��ɂ���čs�����ς��
// 3.���t���[�����ɒe��ł�
//========================================================================================
int TERRAZI::UniqueUpdate(std::shared_ptr<IPlayer> player)
{
	// 1.�o�ꐔ�t���[���܂ł̓v���C���[�̈ʒu���擾��������
	if (ownframecount < 5) TergetRadian(player->GetPosition());


	// 2.�A�N�V�����p�^�[���ԍ��ɂ���čs�����ς��
	if (actionpattern == 0)
	{
		 ActionPattern01(player);		
	}
	if (actionpattern == 1)
	{
		ActionPattern02(player);
	}
	if (actionpattern == 2)
	{
		ActionPattern03();
	}

	// 3.���t���[�����ɒe��ł�
	if (ownframecount % SHOT_INTERVAL == 0) {
		return OnBulletShot;
	}
	return 0;
}
//========================================================================================
//								�A�N�V�����p�^�[��01
// 
// radian�����Ɍ������Đi�ށB
// �v���C���[��x�����̓����蔻��̃T�C�Y + 20 �����m�͈͂Ƃ���
//		���m�͈͂Ƀv���C���[����������e����������p�^�[����ύX����
//========================================================================================
void TERRAZI::ActionPattern01(std::shared_ptr<IPlayer> player)
{
	Enemy_Patterns(MovePatternID::TowardsTarget);		//�s���p�^�[�� 0:���@�Ɍ�����

	/*Y���̋����֌W�Ȃ��v���C���[�̂̓����蔻���X�����d�Ȃ�����*/
	if (player->GetHitbox().left <= position.x &&
		player->GetHitbox().right >= position.x &&
		player->GetPosition().y > position.y) {		//���@��Y������v�����Ƃ�

		actionpattern++;			//�����p�^�[���ֈڍs����

		direction = position.x > player->GetPosition().x ? -1 : 1;	//�v���C���[�Ƃ̈ʒu�֌W�ɂ���Č������Đݒ肷��
	}


}
//========================================================================================
//								�A�N�V�����p�^�[��02
// 
// ��葬�x�܂Ō�������
//========================================================================================
void TERRAZI::ActionPattern02(std::shared_ptr<IPlayer> player)
{	//��葬�x�ɗ�����܂Ō�������
	Enemy_Patterns(MovePatternID::TowardsTarget);	   //�s���p�^�[�� 0:���@�Ɍ�����

	status.speed -= DECELERATION;					   //����
	if (status.speed < DECELERATION_LINIT) {
		actionpattern = 2; 		                      //���x��0.6����������瓦���p�^�[���Ɉڍs����
		TergetRadian(player->GetPosition());
	}
}
//========================================================================================
//								�A�N�V�����p�^�[��03
// 
// �v���C���[�Ƃ͋t�����Ɍ������ĉ������Ȃ����ނ���
// ��葬�x�ȏ�͉������Ȃ��悤�ɐ�����������
//========================================================================================
void TERRAZI::ActionPattern03()
{
	//���Ε����Ɍ������ē�������
	position.x -= cos(radian) * direction;		//X���̈ړ�
	position.y -= status.speed;		            //Y���̈ړ�

	// ��葬�x�ȏ�͉������Ȃ��悤�ɐ�����������
	if (status.speed < SPPED_LIMIT) {
		status.speed += status.speed * status.acceleration;
	}

}


