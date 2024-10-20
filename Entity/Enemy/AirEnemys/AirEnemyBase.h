#ifndef AIRENEMYBASE_H
#define AIRENEMYBASE_H

#include "EnemyBase.h"

class AirEnemyBase : public EnemyBase {
public:
	int AnimUpdate(int framecount, int updatecount)override {

		//�A�j���[�V�����ԍ���i�߂�
		if (framecount % updatecount == 0) {

			int StartAnimNum = status.number * A_ENEMY_PIC_LINE;		//_e.enemy(��) * A_ENEMY_PIC_LINE(�s)
			int EndAnimNum = StartAnimNum + status.anim_sum - 1;		//�A�j���[�V�����ԍ� + �����ŃA�j���[�V�����̍ŏI�ԍ�������o�� -1�͕␳�l

			currentanim_number += 1 * direction;

			Clamp(currentanim_number, StartAnimNum, EndAnimNum);


		}

		return 0;
	}


	int Draw()override {

		Vector2 pic = LeftTopPos(position, status.pic_size);
		if (!shootdown) {  // ��e���Ă��Ȃ��ꍇ
			// ImageManager ����G�̉摜���擾���ĕ`��
			int enemyType = status.number;  // �G�̎�ނɊ�Â��ĉ摜��I��
			int animFrame = currentanim_number;    // ���݂̃A�j���[�V�����t���[��

			// �G���Ƃ̉摜�z�񂩂�Y������A�j���[�V�����t���[����`��
			DrawBmp(pic.x, pic.y, ImageManager::air_enemy[enemyType][animFrame]);
		}
		else {
			// ��e���Ă���ꍇ�̓G�t�F�N�g��`��
			DrawBmp(pic.x, pic.y, ImageManager::EnemyBomber[currentanim_number]);
		}
	}

};

#endif // AIRENEMYBASE_H
