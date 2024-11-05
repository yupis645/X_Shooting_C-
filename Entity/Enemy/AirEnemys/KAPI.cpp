#include "AirEnemyBase.h"

#include "Player.h"


namespace {
	constexpr int   ANIM_UPDATE_INTERVAL  = 5;		//アニメーション画像を入れ替えるフレーム数
	constexpr int   PLAYER_TRACKING_FRAME = 5;		//画面に登場してこの値未満の間はプレイヤーの位置を捕捉し続ける。
	constexpr int   MOVING_FRAME_TIME     = 100;	//出現してから進み続ける時間
	constexpr float DECELERATION          = 0.2f;	//毎フレーム減速する値
	constexpr float DECELERATION_LINIT    = 0.6f;	//最大減速値
	constexpr float SPPED_LIMIT		      = 100;	//出現してから進み続ける時間
}


//========================================================================================
//					コンストラクタ
// 
// インスタンスが作られた時点でステータス、座標などの情報を取得する
//========================================================================================
KAPI::KAPI(std::weak_ptr<IPlayer> player, int num)
{
	Create(player, num);		//インスタンス生成時に必要なステータスを設定する
}

//========================================================================================
//								初期化
// 
// メンバ変数を全て初期化する
//========================================================================================
void KAPI::Init() {
	EnemyBase::Init();		//メンバ変数を初期化する
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
int KAPI::Create(std::weak_ptr<IPlayer> player, int number)
{
	auto useplayer = player.lock();		//スマートポインタを一時shared_ptrに変換する

	//	1.ステータスの初期値,設定値を取得する。
	EnemyBase::StatusSetup(EnemyStatusData::KAPI);

	//	2.出現時の座標を設定する
	AirEnemyBase::InitPostionPattern();

	//  3.activeやtypeなどEnemyBaseの変数で調整が必要なものを調整する
	AirEnemyBase::Create(useplayer, number);

	return 0;
}


//========================================================================================
//							更新
// 第１引数 : プレイヤーの情報を持ったスマートポインタ
// 
// EnemyManagerに使ってもらうための関数
//  AirEnemyBase::Updateが固有のアクションを設定したUniqueUpdate関数を呼び出す。
// 返り値が "OnBulletShot" ならEnemyManagerから敵のショットを作るように命令する
//========================================================================================
int KAPI::Update(std::weak_ptr<IPlayer> player)
{
	return  AirEnemyBase::Update(player);
}

//========================================================================================
//							固有のアクション
// 第１引数 : プレイヤーの情報を持ったスマートポインタ
// 
//敵の種類によってかわる関数。
// アニメーションの更新や座標の更新などを行う
// 1.登場から規定フレーム以内まではplayerの座標に対する角度を取得し続ける
// 2.アニメーションの更新
// 3.アクションパターンによって動きを替える
//========================================================================================
int KAPI::UniqueUpdate(std::shared_ptr<IPlayer> player)
{

	// 1.このフレーム値が低いと動きが一定になりやすい
	if (ownframecount < PLAYER_TRACKING_FRAME) TergetRadian(player->GetPosition());

	// 2.TORKENはアニメーションは特定の場面でしか動かさないので、撃破時のみ自動更新する
	if (shootdown) {
		AirEnemyBase::AnimUpdate(ANIM_UPDATE_INTERVAL);
	}

	// 3.各アクションパターン

	if (actionpattern == 0)	return ActionPattern01();	        //pattern0 : 一定距離まで進んだ後、射撃をする

	if (actionpattern == 1)	ActionPattern02(player);			//pattern1 : アニメーション終了までうごかない

	if (actionpattern == 2)	ActionPattern03();			        //pattern0 : プレイヤーとは逆のほうに逃げる

	return 0;
}


//========================================================================================
//							アクションパターン０
// 
// 出現時にいたプレイヤーの位置に向かって前進する
// 一定時間後、射撃をしてから次のパターンを移行する
//========================================================================================
int KAPI::ActionPattern01()
{
	//出現時にプレイヤーがいた座標に向かって進む
	Enemy_Patterns(MovePatternID::TowardsTarget);

	//一定時間がたったら射撃をしてパターンを進める
	if (ownframecount >= MOVING_FRAME_TIME) {

		actionpattern++;			//パターンを進める
		return OnBulletShot;		//射撃をEnemyManagerに伝える
	}
	return 0;
}

//========================================================================================
//							アクションパターン 1
// 
// アニメーションを動かす。その間は移動はしない
// アニメーション完了後はプレイヤーの位置を再度取得する
//========================================================================================
void KAPI::ActionPattern02(std::shared_ptr<IPlayer> player) {
	                                                                //一定速度に落ちるまで減速する
	Enemy_Patterns(MovePatternID::TowardsTarget);		            //行動パターン 0:自機に向かう

	status.speed -= DECELERATION;				                    //減速
	if (status.speed < DECELERATION_LINIT)  actionpattern = 2; 		//速度が0.6を下回ったら逃走パターンに移行する
}
//========================================================================================
//							アクションパターン 2
// 
// 取得した位置の逆方向に逃げる
//========================================================================================
void KAPI::ActionPattern03()
{
	//反対方向に向かって逃走する
	position.x -= cos(radian) * direction;		//X軸の移動
	position.y -= status.speed * status.acceleration;		//Y軸の移動

	if (status.speed < SPPED_LIMIT) {
		status.speed += status.speed * status.acceleration;
	}

}
