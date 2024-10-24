#include "TOROID.h"

#include "common.h"
#include "Player.h"


namespace {
	constexpr int ANIM_UPDATE_INTERVAL = 5;
}


void TOROID::Init(){
	EnemyBase::Init();
}

int TOROID::Create( std::shared_ptr<IPlayer> player,int number, int typenumber)
{
	EnemyBase::StatusSetup(number,typenumber);

	AppearPattern(player->GetPosition().x);

	hitbox.CenterPositionSync(position, status.hitbox_size);

	/*��ʂ̒��S�����ɍ��E�ǂ���Ɋ���Ă��邩�ɂ���čŏ��̐i�s�����������߂�*/
	direction = position.x < ScreenConfig::CENTER_X ? -1 : 1;

	return 0;
}

int TOROID::Update(std::shared_ptr<IPlayer> player)
{
	ownframecount++;				//�G��̂ɂ��Ă���ʂ̃^�C�}�[��i�߂�(�s�������Ɏg��)

	//��e���肪true�̏ꍇ
	AirEnemyBase::AnimUpdate(ANIM_UPDATE_INTERVAL);

	//�ȉ��͔�e���肪�o�Ă��Ȃ��ꍇ�ɏ����ɐi��
	int UpdateReturn  = UniqueUpdate(player);		//�G�̍s��(number�ɂ���ĈقȂ鋓��������)

	hitbox.CenterPositionSync(position, status.hitbox_size);


	//���W����ʊO�ɏo���ꍇ�̍��W�̏�����
	if (ownframecount > 50) {				//�o�����Ă���50�t���[�������Ă��画��ɓ���(�o�����Ă��΂炭�͉�ʒ[�ɓ������Ă��Ă��������Ȃ�)
		if (hitbox.BoxCollision( winView) == false)		//�����蔻��ƃE�B���h�E�T�C�Y��RECT�Əd�Ȃ��Ă��Ȃ� = ��ʊO �Ȃ�
		{
			InitClear();
		}
	}

	if (UpdateReturn == OnBulletShot) {
		return OnBulletShot;
	}

	return 0;
}


int TOROID::UniqueUpdate(std::shared_ptr<IPlayer> player)
{

	/*�e�����O�̓���*/
	if (actionpattern == 0)
	{
		return ActionPattern01(player->GetHitbox(), player->GetPosition()) != 0;
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

		Enemy_Patterns(0);		//�s���p�^�[�� 0:���@�Ɍ�����

		/*Y���̋����֌W�Ȃ��v���C���[�̂̓����蔻���X�����d�Ȃ�����*/
		if (playerhitbox.left <= position.x  &&
			playerhitbox.right >= position.x &&
			playerpos.y > position.y) {		//���@��Y������v�����Ƃ�


			actionpattern++;			//�����p�^�[���ֈڍs����

			direction = position.x > playerpos.x ? -1 : 1;	//�v���C���[�Ƃ̈ʒu�֌W�ɂ���Č������Đݒ肷��

			return  OnBulletShot;

		}
	return 0;
}

void TOROID::ActionPattern02()
{	//��葬�x�ɗ�����܂Ō�������
	Enemy_Patterns(0);		//�s���p�^�[�� 0:���@�Ɍ�����

	currentspeed -= 0.1f;					//����
	if (currentspeed < 0.6)  actionpattern = 2; 		//���x��0.6����������瓦���p�^�[���Ɉڍs����
}

void TOROID::ActionPattern03()
{
	//���Ε����Ɍ������ē�������
	Enemy_Patterns(5);		//�s���p�^�[�� 5:�����x�����Z�����������ɓ�����


}


