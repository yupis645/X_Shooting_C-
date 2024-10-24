#include "AirEnemyBase.h"


namespace {
	constexpr int PLAYER_X_DISTANCE = 250;
	constexpr int POS_X_RANDOM_VALUE = 200;
	constexpr int ONE_OFFSET = 1;
	constexpr int OWNFRAMECOUNT_LIMIT = 1000;
	constexpr int BOMBERUPDATEINTERVAL = 18;

	// ランダムなX座標を生成する関数
	int GenerateRandomX() {
		return rand() % POS_X_RANDOM_VALUE;
	}
}

int AirEnemyBase::AnimUpdate(int UpdateInterval) {
	//アニメーション番号を進める
	if (!shootdown) {
		if (ownframecount % UpdateInterval == 0) {
			currentanimnum += 1 * direction;

			int EndAnimNum = status.anim_sum - 1;		//アニメーション番号 + 枚数でアニメーションの最終番号を割り出す -1は補正値
			Clamp(currentanimnum, 0, EndAnimNum);
		}
		
	}
	else {
		if (ownframecount % BOMBERUPDATEINTERVAL == 0) {
			currentanimnum++;
			if (currentanimnum > TextureConfigs::COMMON_BOMBER.indexcount) {				//anim変数が 11よりも大きくなったら
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
	//出現位置の設定
	position.x = x_pos + PLAYER_X_DISTANCE + GenerateRandomX();		//player_から 250 離れた位置から更に 0～200 の乱数を加算したX座標を指定 

	//もし乱数で取得したX座標が画面の横サイズを超えていたら
	if (position.x >= ScreenConfig::SRN_W) { position.x = x_pos - PLAYER_X_DISTANCE + GenerateRandomX(); }

}
