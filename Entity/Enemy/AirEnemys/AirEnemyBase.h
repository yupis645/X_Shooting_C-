#ifndef AIRENEMYBASE_H
#define AIRENEMYBASE_H

#include "EnemyBase.h"

class AirEnemyBase : public EnemyBase {
public:
	int AnimUpdate(int framecount, int updatecount)override {

		//アニメーション番号を進める
		if (framecount % updatecount == 0) {

			int StartAnimNum = status.number * A_ENEMY_PIC_LINE;		//_e.enemy(列) * A_ENEMY_PIC_LINE(行)
			int EndAnimNum = StartAnimNum + status.anim_sum - 1;		//アニメーション番号 + 枚数でアニメーションの最終番号を割り出す -1は補正値

			currentanim_number += 1 * direction;

			Clamp(currentanim_number, StartAnimNum, EndAnimNum);


		}

		return 0;
	}


	int Draw()override {

		Vector2 pic = LeftTopPos(position, status.pic_size);
		if (!shootdown) {  // 被弾していない場合
			// ImageManager から敵の画像を取得して描画
			int enemyType = status.number;  // 敵の種類に基づいて画像を選択
			int animFrame = currentanim_number;    // 現在のアニメーションフレーム

			// 敵ごとの画像配列から該当するアニメーションフレームを描画
			DrawBmp(pic.x, pic.y, ImageManager::air_enemy[enemyType][animFrame]);
		}
		else {
			// 被弾している場合はエフェクトを描画
			DrawBmp(pic.x, pic.y, ImageManager::EnemyBomber[currentanim_number]);
		}
	}

};

#endif // AIRENEMYBASE_H
