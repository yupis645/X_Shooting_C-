#include "AirEnemyBase.h"
#include "Player.h"


namespace {
	constexpr int PLAYER_X_DISTANCE = 250;
	constexpr int POS_X_RANDOM_VALUE = 200;
	constexpr int ONE_OFFSET = 1;
	constexpr int OWNFRAMECOUNT_LIMIT = 1000;
	constexpr int BOMBERUPDATEINTERVAL = 18;

	// �����_����X���W�𐶐�����֐�
	int GenerateRandomX() {
		return rand() % POS_X_RANDOM_VALUE;
	}
}


int AirEnemyBase::Create(std::weak_ptr<IPlayer> pl, int number)
{
	auto useplayer = pl.lock();

	active = true;


	//number�̕S�̈ʂ̓G�l�~�[��Type��\��(100 = Type:1 , 200 = Type:2)
	if (number >= 100) {
		status.type = number / 100;								//�i���o�[��100�Ŋ�����Type�����o��
	}

	hitbox.CenterPositionSync(position, status.hitbox_size);

	TergetRadian(useplayer->GetPosition());

	/*��ʂ̒��S�����ɍ��E�ǂ���Ɋ���Ă��邩�ɂ���čŏ��̐i�s�����������߂�*/
	direction = position.x < ScreenConfig::CENTER_X ? 1 : -1;

	return 0;
}

int AirEnemyBase::Update(std::weak_ptr<IPlayer> player)
{
	auto useplayer = player.lock();

	ownframecount++;				//�G��̂ɂ��Ă���ʂ̃^�C�}�[��i�߂�(�s�������Ɏg��)

	//�ȉ��͔�e���肪�o�Ă��Ȃ��ꍇ�ɏ����ɐi��
	int UpdateReturn = UniqueUpdate(useplayer);		//�G�̍s��(number�ɂ���ĈقȂ鋓��������)

	hitbox.CenterPositionSync(position, status.hitbox_size);


	//���W����ʊO�ɏo���ꍇ�̍��W�̏�����
	if (ownframecount > 50) {				//�o�����Ă���50�t���[�������Ă��画��ɓ���(�o�����Ă��΂炭�͉�ʒ[�ɓ������Ă��Ă��������Ȃ�)
		if (hitbox.BoxCollision(winView) == false)		//�����蔻��ƃE�B���h�E�T�C�Y��RECT�Əd�Ȃ��Ă��Ȃ� = ��ʊO �Ȃ�
		{
			InitClear();
		}
	}

	if (UpdateReturn == OnBulletShot) {
		return OnBulletShot;
	}

	return 0;
}

int AirEnemyBase::AnimUpdate(int UpdateInterval) {
	//�A�j���[�V�����ԍ���i�߂�
	if (!shootdown) {
		if (ownframecount % UpdateInterval == 0) {
			currentanimnum += 1 * direction;

			int EndAnimNum = status.anim_sum - 1;		//�A�j���[�V�����ԍ� + �����ŃA�j���[�V�����̍ŏI�ԍ�������o�� -1�͕␳�l
			Clamp(currentanimnum, 0, EndAnimNum);
		}
		
	}
	else {
		if (ownframecount % BOMBERUPDATEINTERVAL == 0) {
			currentanimnum++;
			if (currentanimnum > TextureConfigs::COMMON_BOMBER.indexcount) {				//anim�ϐ��� 11�����傫���Ȃ�����
				InitClear();
			}
		}
	}
	return 0;
}

void AirEnemyBase::CreateSetup()
{
}

void AirEnemyBase::InitPostionPattern(float x_pos)
{
	if (x_pos == -1.0f) {
		position.x = (float)(rand() % ScreenConfig::SRN_W + ONE_OFFSET);
	}
	//�o���ʒu�̐ݒ�
	position.x = x_pos + PLAYER_X_DISTANCE + GenerateRandomX();		//player_���� 250 ���ꂽ�ʒu����X�� 0�`200 �̗��������Z����X���W���w�� 

	//���������Ŏ擾����X���W����ʂ̉��T�C�Y�𒴂��Ă�����
	if (position.x >= ScreenConfig::SRN_W) { position.x = x_pos - PLAYER_X_DISTANCE + GenerateRandomX(); }

}

void AirEnemyBase::TergetRadian(const Vector2& targetpos)
{
	radian = atan2(targetpos.y - position.y, targetpos.x - position.x);		//�O�p�`�̊p�x���Z�o����
}
