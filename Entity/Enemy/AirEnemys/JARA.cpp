//----------------------------------------------------------------------------------------------------------------------------------------
//													�W�A��
// 
// ����]���Ȃ�����ł���G
// �����̓g�[���C�h�Ɠ����B�v���C���[�����m����͈͂��L��
//----------------------------------------------------------------------------------------------------------------------------------------

#include "AirEnemyBase.h"

#include "Player.h"


namespace {
	constexpr int   ANIM_UPDATE_INTERVAL = 5;
	constexpr float DECELERATION         = 0.2f;		//���t���[����������l
	constexpr float DECELERATION_LINIT   = 0.6f;		//�ő匸���l
	constexpr int   SENSOR_RANGE_OFFSET  = 10;
}


//========================================================================================
//					�R���X�g���N�^
// 
// �C���X�^���X�����ꂽ���_�ŃX�e�[�^�X�A���W�Ȃǂ̏����擾����
//========================================================================================
JARA::JARA(std::weak_ptr<IPlayer> player, int num)
{
	Create(player, num);
}

//========================================================================================
//								������
// 
// �����o�ϐ���S�ď���������
//========================================================================================
void JARA::Init() {
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
int JARA::Create(std::weak_ptr<IPlayer> player, int number)
{
	auto useplayer = player.lock();		//�X�}�[�g�|�C���^���ꎞshared_ptr�ɕϊ�����

	//	1.�X�e�[�^�X�̏����l,�ݒ�l���擾����B
	EnemyBase::StatusSetup(EnemyStatusData::JARA);

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
//========================================================================================
int JARA::Update(std::weak_ptr<IPlayer> player)
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
int JARA::UniqueUpdate(std::shared_ptr<IPlayer> player)
{
	// 1.�o�ꐔ�t���[���܂ł̓v���C���[�̈ʒu���擾��������
	if (ownframecount < 5) TergetRadian(player->GetPosition());

	// 2.�ŗL��Update���s��
	AirEnemyBase::AnimUpdate(ANIM_UPDATE_INTERVAL);

	// 3.�A�N�V�����p�^�[���ԍ��ɂ���čs����ς���
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
int JARA::ActionPattern01(const Boxcollider& playerhitbox, const Vector2& playerpos)
{
	//�o�����Ƀv���C���[���������W�Ɍ������Đi��

	Enemy_Patterns(MovePatternID::TowardsTarget);		//�s���p�^�[�� 0:���@�Ɍ�����

	/*Y���̋����֌W�Ȃ��v���C���[�̂̓����蔻���X�����d�Ȃ�����*/
	if (playerhitbox.left  - SENSOR_RANGE_OFFSET <= position.x &&
		playerhitbox.right + SENSOR_RANGE_OFFSET >= position.x &&
		playerpos.y > position.y) {		                //���@��Y������v�����Ƃ�


		actionpattern++;			                    //�����p�^�[���ֈڍs����

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
void JARA::ActionPattern02()
{	//��葬�x�ɗ�����܂Ō�������
	Enemy_Patterns(MovePatternID::TowardsTarget);		        //�s���p�^�[�� 0:���@�Ɍ�����

	status.speed -= DECELERATION;			                    //����
	if (status.speed < DECELERATION_LINIT)  actionpattern = 2; 	//���x��0.6����������瓦���p�^�[���Ɉڍs����
}

//========================================================================================
//								������
// 
// �v���C���[���甽�Ε����Ɍ�����
//========================================================================================
void JARA::ActionPattern03()
{
	//���Ε����Ɍ������ē�������
	Enemy_Patterns(MovePatternID::EscapeX);		//�s���p�^�[�� 5:�����x�����Z�����������ɓ�����


}


