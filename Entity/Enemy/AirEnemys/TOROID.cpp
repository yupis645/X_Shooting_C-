//----------------------------------------------------------------------------------------------------------------------------------------
//													�g�[���C�h
// 
// �~�Ղ̓G
// 1.�v���C���[�����m�͈͂ɓ���܂œo�ꎞ�ɋL�������v���C���[�̈ʒu�Ɍ������Đi��
// 2.�v���C���[�����m�͈͂ɓ���Βe�𔭎˂��ċt�����ɓ����o��
//----------------------------------------------------------------------------------------------------------------------------------------

#include "AirEnemyBase.h"

#include "common.h"
#include "Player.h"


namespace {
	constexpr int   ANIM_UPDATE_INTERVAL = 5;
	constexpr float DECELERATION       = 5;
	constexpr int   DECELERATION_LINIT   = 5;
}


//========================================================================================
//					�R���X�g���N�^
// 
// �C���X�^���X�����ꂽ���_�ŃX�e�[�^�X�A���W�Ȃǂ̏����擾����
//========================================================================================
TOROID::TOROID(std::weak_ptr<IPlayer> player, int num)
{
	Create(player, num);
}
//========================================================================================
//								������
// 
// �����o�ϐ���S�ď���������
//========================================================================================
void TOROID::Init(){
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
int TOROID::Create( std::weak_ptr<IPlayer> player,int number)
{
	auto useplayer = player.lock();

	EnemyBase::StatusSetup(EnemyStatusData::TOROID);


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
int TOROID::Update(std::weak_ptr<IPlayer> player)
{
	return  AirEnemyBase::Update(player);
}

//========================================================================================
//							�ŗL�̃A�N�V����
// ��P���� : �v���C���[�̏����������X�}�[�g�|�C���^
// 
//�G�̎�ނɂ���Ă����֐��B
// 1.�o�ꐔ�t���[���܂ł̓v���C���[�̈ʒu���擾��������
// 2.�ŗL��Update���s��
// 3.�A�N�V�����p�^�[���ԍ��ɂ���čs����ς���
//========================================================================================
int TOROID::UniqueUpdate(std::shared_ptr<IPlayer> player)
{

	if(ownframecount < 5) TergetRadian(player->GetPosition());

	//��e���肪true�̏ꍇ
	AirEnemyBase::AnimUpdate(ANIM_UPDATE_INTERVAL);

	/*�e�����O�̓���*/
	if (actionpattern == 0)
	{
		return ActionPattern01(player->GetHitbox(), player->GetPosition());
	}

	if (actionpattern == 1) 
	{
		ActionPattern02();
	}
	if (actionpattern == 2) 
	{
		ActionPattern03();
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
int TOROID::ActionPattern01(const Boxcollider& playerhitbox, const Vector2& playerpos)
{
	//�o�����Ƀv���C���[���������W�Ɍ������Đi��

		Enemy_Patterns(MovePatternID::TowardsTarget);		//�s���p�^�[�� 0:���@�Ɍ�����

		/*Y���̋����֌W�Ȃ��v���C���[�̂̓����蔻���X�����d�Ȃ�����*/
		if (playerhitbox.left <= position.x  &&
			playerhitbox.right >= position.x &&
			playerpos.y > position.y) {		//���@��Y������v�����Ƃ�


			actionpattern++;			//�����p�^�[���ֈڍs����

			direction = position.x > playerpos.x ? -1 : 1;	//�v���C���[�Ƃ̈ʒu�֌W�ɂ���Č������Đݒ肷��

			if (status.type == 1) {
				return OnBulletShot;
			}
		}
	return 0;
}
//========================================================================================
//								�A�N�V�����p�^�[��02
// 
// ��葬�x�܂Ō�������B
// ���x�����ȉ��ɂȂ�����p�^�[���ԍ����J��グ��
//========================================================================================
void TOROID::ActionPattern02()
{	//��葬�x�ɗ�����܂Ō�������
	Enemy_Patterns(MovePatternID::TowardsTarget);		//�s���p�^�[�� 0:���@�Ɍ�����

	status.speed -= 0.2f;					            //����
	if (status.speed < 0.6)  actionpattern = 2; 		//���x��0.6����������瓦���p�^�[���Ɉڍs����
}
//========================================================================================
//								�A�N�V�����p�^�[��03
// 
// �t�����ɓ�������
//========================================================================================
void TOROID::ActionPattern03()
{
	//���Ε����Ɍ������ē�������
	Enemy_Patterns(MovePatternID::EscapeX);		//�s���p�^�[�� 5:�����x�����Z�����������ɓ�����


}


