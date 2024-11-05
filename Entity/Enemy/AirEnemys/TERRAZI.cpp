#include "AirEnemyBase.h"

#include "Player.h"


namespace {
	constexpr int   ANIM_UPDATE_INTERVAL = 5;
	constexpr float DECELERATION         = 0.2f;
	constexpr float DECELERATION_LINIT   = 0.6f;
	constexpr int   SHOT_INTERVAL        = 40;
	constexpr float SPPED_LIMIT			 = 100;		//出現してから進み続ける時間

}



//========================================================================================
//					コンストラクタ
// 
// インスタンスが作られた時点でステータス、座標などの情報を取得する
//========================================================================================
TERRAZI::TERRAZI(std::weak_ptr<IPlayer> player, int num)
{
	Create(player, num);
}
//========================================================================================
//								初期化
// 
// メンバ変数を全て初期化する
//========================================================================================
void TERRAZI::Init() {
	EnemyBase::Init();
}
//========================================================================================
//							生成(ステータスの取得など)
// 第１引数 : プレイヤーの情報を持ったスマートポインタ
// 第２引数 : 敵の識別番号、及びタイプ。(100の位がタイプを表す [203 なら type 2、number 3となる])
// 
// インスタンス化に必要な情報を取得する
//	1.ステータスの初期値,設定値を取得する。
//	2.出現時の座標を設定する
//  3.activeやtypeなどEnemyBaseの変数で調整が必要なものを調整する
//========================================================================================
int TERRAZI::Create(std::weak_ptr<IPlayer> player, int number)
{
	auto useplayer = player.lock();

	EnemyBase::StatusSetup(EnemyStatusData::TERRAZI);


	AirEnemyBase::InitPostionPattern(useplayer->GetPosition().x);

	AirEnemyBase::Create(useplayer, number);

	return 0;
}
//========================================================================================
//							更新
// 第１引数 : プレイヤーの情報を持ったスマートポインタ
// 
// EnemyManagerに使ってもらうための関数
//  AirEnemyBase::Updateが固有のアクションを設定したUniqueUpdate関数を呼び出す。
//========================================================================================
int TERRAZI::Update(std::weak_ptr<IPlayer> player)
{
	return  AirEnemyBase::Update(player);
}

//========================================================================================
//							固有のアクション
// 第１引数 : プレイヤーの情報を持ったスマートポインタ
// 
//敵の種類によってかわる関数。
// 1.登場数フレームまではプレイヤーの位置を取得し続ける
// 2.アクションパターン番号によって行動が変わる
// 3.一定フレーム毎に弾を打つ
//========================================================================================
int TERRAZI::UniqueUpdate(std::shared_ptr<IPlayer> player)
{
	// 1.登場数フレームまではプレイヤーの位置を取得し続ける
	if (ownframecount < 5) TergetRadian(player->GetPosition());


	// 2.アクションパターン番号によって行動が変わる
	if (actionpattern == 0)
	{
		 ActionPattern01(player);		
	}
	if (actionpattern == 1)
	{
		ActionPattern02(player);
	}
	if (actionpattern == 2)
	{
		ActionPattern03();
	}

	// 3.一定フレーム毎に弾を打つ
	if (ownframecount % SHOT_INTERVAL == 0) {
		return OnBulletShot;
	}
	return 0;
}
//========================================================================================
//								アクションパターン01
// 
// radian方向に向かって進む。
// プレイヤーのx方向の当たり判定のサイズ + 20 を感知範囲とする
//		感知範囲にプレイヤーが入ったら弾をうったらパターンを変更する
//========================================================================================
void TERRAZI::ActionPattern01(std::shared_ptr<IPlayer> player)
{
	Enemy_Patterns(MovePatternID::TowardsTarget);		//行動パターン 0:自機に向かう

	/*Y軸の距離関係なくプレイヤーのの当たり判定とX軸が重なったら*/
	if (player->GetHitbox().left <= position.x &&
		player->GetHitbox().right >= position.x &&
		player->GetPosition().y > position.y) {		//自機とY軸が一致したとき

		actionpattern++;			//減速パターンへ移行する

		direction = position.x > player->GetPosition().x ? -1 : 1;	//プレイヤーとの位置関係によって向きを再設定する
	}


}
//========================================================================================
//								アクションパターン02
// 
// 一定速度まで減速する
//========================================================================================
void TERRAZI::ActionPattern02(std::shared_ptr<IPlayer> player)
{	//一定速度に落ちるまで減速する
	Enemy_Patterns(MovePatternID::TowardsTarget);	   //行動パターン 0:自機に向かう

	status.speed -= DECELERATION;					   //減速
	if (status.speed < DECELERATION_LINIT) {
		actionpattern = 2; 		                      //速度が0.6を下回ったら逃走パターンに移行する
		TergetRadian(player->GetPosition());
	}
}
//========================================================================================
//								アクションパターン03
// 
// プレイヤーとは逆方向に向かって加速しながら後退する
// 一定速度以上は加速しないように制限をかける
//========================================================================================
void TERRAZI::ActionPattern03()
{
	//反対方向に向かって逃走する
	position.x -= cos(radian) * direction;		//X軸の移動
	position.y -= status.speed;		            //Y軸の移動

	// 一定速度以上は加速しないように制限をかける
	if (status.speed < SPPED_LIMIT) {
		status.speed += status.speed * status.acceleration;
	}

}


