#include "AirEnemyBase.h"
#include "Player.h"


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


int AirEnemyBase::Create(std::weak_ptr<IPlayer> pl, int number)
{
	auto useplayer = pl.lock();

	active = true;


	//numberの百の位はエネミーのTypeを表す(100 = Type:1 , 200 = Type:2)
	if (number >= 100) {
		status.type = number / 100;								//ナンバーを100で割ってTypeを取り出す
	}

	hitbox.CenterPositionSync(position, status.hitbox_size);

	TergetRadian(useplayer->GetPosition());

	/*画面の中心を軸に左右どちらに寄っているかによって最初の進行方向をさだめる*/
	direction = position.x < ScreenConfig::CENTER_X ? 1 : -1;

	return 0;
}

int AirEnemyBase::Update(std::weak_ptr<IPlayer> player)
{
	auto useplayer = player.lock();

	ownframecount++;				//敵一体についている個別のタイマーを進める(行動処理に使う)

	//以下は被弾判定が出ていない場合に処理に進む
	int UpdateReturn = UniqueUpdate(useplayer);		//敵の行動(numberによって異なる挙動をする)

	hitbox.CenterPositionSync(position, status.hitbox_size);


	//座標が画面外に出た場合の座標の初期化
	if (ownframecount > 50) {				//出現してから50フレーム立ってから判定に入る(出現してしばらくは画面端に当たっていても消去しない)
		if (hitbox.BoxCollision(winView) == false)		//当たり判定とウィンドウサイズのRECTと重なっていない = 画面外 なら
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

void AirEnemyBase::CreateSetup()
{
}

void AirEnemyBase::InitPostionPattern(float x_pos)
{
	if (x_pos == -1.0f) {
		position.x = (float)(rand() % ScreenConfig::SRN_W + ONE_OFFSET);
	}
	//出現位置の設定
	position.x = x_pos + PLAYER_X_DISTANCE + GenerateRandomX();		//player_から 250 離れた位置から更に 0～200 の乱数を加算したX座標を指定 

	//もし乱数で取得したX座標が画面の横サイズを超えていたら
	if (position.x >= ScreenConfig::SRN_W) { position.x = x_pos - PLAYER_X_DISTANCE + GenerateRandomX(); }

}

void AirEnemyBase::TergetRadian(const Vector2& targetpos)
{
	radian = atan2(targetpos.y - position.y, targetpos.x - position.x);		//三角形の角度を算出する
}
