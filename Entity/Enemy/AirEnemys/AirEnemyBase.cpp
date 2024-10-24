#include "AirEnemyBase.h"


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

void AirEnemyBase::AppearPattern(float x_pos)
{
	if (x_pos == -1) {
		position.x = (float)(rand() % ScreenConfig::SRN_W + ONE_OFFSET);
	}
	//�o���ʒu�̐ݒ�
	position.x = x_pos + PLAYER_X_DISTANCE + GenerateRandomX();		//player_���� 250 ���ꂽ�ʒu����X�� 0�`200 �̗��������Z����X���W���w�� 

	//���������Ŏ擾����X���W����ʂ̉��T�C�Y�𒴂��Ă�����
	if (position.x >= ScreenConfig::SRN_W) { position.x = x_pos - PLAYER_X_DISTANCE + GenerateRandomX(); }

}
