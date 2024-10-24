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

	/*画面の中心を軸に左右どちらに寄っているかによって最初の進行方向をさだめる*/
	direction = position.x < ScreenConfig::CENTER_X ? -1 : 1;

	return 0;
}

int TOROID::Update(std::shared_ptr<IPlayer> player)
{
	ownframecount++;				//敵一体についている個別のタイマーを進める(行動処理に使う)

	//被弾判定がtrueの場合
	AirEnemyBase::AnimUpdate(ANIM_UPDATE_INTERVAL);

	//以下は被弾判定が出ていない場合に処理に進む
	int UpdateReturn  = UniqueUpdate(player);		//敵の行動(numberによって異なる挙動をする)

	hitbox.CenterPositionSync(position, status.hitbox_size);


	//座標が画面外に出た場合の座標の初期化
	if (ownframecount > 50) {				//出現してから50フレーム立ってから判定に入る(出現してしばらくは画面端に当たっていても消去しない)
		if (hitbox.BoxCollision( winView) == false)		//当たり判定とウィンドウサイズのRECTと重なっていない = 画面外 なら
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

	/*弾を撃つ前の動き*/
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
	//出現時にプレイヤーがいた座標に向かって進む

		Enemy_Patterns(0);		//行動パターン 0:自機に向かう

		/*Y軸の距離関係なくプレイヤーのの当たり判定とX軸が重なったら*/
		if (playerhitbox.left <= position.x  &&
			playerhitbox.right >= position.x &&
			playerpos.y > position.y) {		//自機とY軸が一致したとき


			actionpattern++;			//減速パターンへ移行する

			direction = position.x > playerpos.x ? -1 : 1;	//プレイヤーとの位置関係によって向きを再設定する

			return  OnBulletShot;

		}
	return 0;
}

void TOROID::ActionPattern02()
{	//一定速度に落ちるまで減速する
	Enemy_Patterns(0);		//行動パターン 0:自機に向かう

	currentspeed -= 0.1f;					//減速
	if (currentspeed < 0.6)  actionpattern = 2; 		//速度が0.6を下回ったら逃走パターンに移行する
}

void TOROID::ActionPattern03()
{
	//反対方向に向かって逃走する
	Enemy_Patterns(5);		//行動パターン 5:加速度を加算しつつｘ軸方向に逃げる


}


