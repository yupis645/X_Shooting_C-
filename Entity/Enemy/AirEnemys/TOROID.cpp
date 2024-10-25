#include "AirEnemyBase.h"

#include "common.h"
#include "Player.h"


namespace {
	constexpr int   ANIM_UPDATE_INTERVAL = 5;
	constexpr float DECELERATION       = 5;
	constexpr int   DECELERATION_LINIT   = 5;
}


TOROID::TOROID(std::weak_ptr<IPlayer> player, int num)
{
	Create(player, num);
}

void TOROID::Init(){
	EnemyBase::Init();
}

int TOROID::Create( std::weak_ptr<IPlayer> player,int number)
{
	auto useplayer = player.lock();

	EnemyBase::StatusSetup(EnemyStatusData::TOROID);


	AirEnemyBase::InitPostionPattern(useplayer->GetPosition().x);

	AirEnemyBase::Create(useplayer, number);

	return 0;
}

int TOROID::Update(std::weak_ptr<IPlayer> player)
{
	return  AirEnemyBase::Update(player);
}


int TOROID::UniqueUpdate(std::weak_ptr<IPlayer> player)
{
	auto useplayer = player.lock();

	if(ownframecount < 5) TergetRadian(useplayer->GetPosition());

	//��e���肪true�̏ꍇ
	AirEnemyBase::AnimUpdate(ANIM_UPDATE_INTERVAL);

	/*�e�����O�̓���*/
	if (actionpattern == 0)
	{
		return ActionPattern01(useplayer->GetHitbox(), useplayer->GetPosition());
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

int TOROID::ActionPattern01(const Boxcollider& playerhitbox, const Vector2& playerpos)
{
	//�o�����Ƀv���C���[���������W�Ɍ������Đi��

		Enemy_Patterns(MovePatternID::TowardsPlayer);		//�s���p�^�[�� 0:���@�Ɍ�����

		/*Y���̋����֌W�Ȃ��v���C���[�̂̓����蔻���X�����d�Ȃ�����*/
		if (playerhitbox.left <= position.x  &&
			playerhitbox.right >= position.x &&
			playerpos.y > position.y) {		//���@��Y������v�����Ƃ�


			actionpattern++;			//�����p�^�[���ֈڍs����

			direction = position.x > playerpos.x ? -1 : 1;	//�v���C���[�Ƃ̈ʒu�֌W�ɂ���Č������Đݒ肷��

			return OnBulletShot;

		}
	return 0;
}

void TOROID::ActionPattern02()
{	//��葬�x�ɗ�����܂Ō�������
	Enemy_Patterns(MovePatternID::TowardsPlayer);		//�s���p�^�[�� 0:���@�Ɍ�����

	status.speed -= 0.2f;					            //����
	if (status.speed < 0.6)  actionpattern = 2; 		//���x��0.6����������瓦���p�^�[���Ɉڍs����
}

void TOROID::ActionPattern03()
{
	//���Ε����Ɍ������ē�������
	Enemy_Patterns(MovePatternID::EscapeX);		//�s���p�^�[�� 5:�����x�����Z�����������ɓ�����


}


