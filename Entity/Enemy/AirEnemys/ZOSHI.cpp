
//----------------------------------------------------------------------------------------------------------------------------------------
//													ゾシー
// 
// 回転する弾のような敵
// タイプによって挙動が違い
//	type 0:	画面に登場時はプレイヤーに向かって進むが、一定時間後にランダムに方向転換する
//	type 1: 登場時から一定間隔でプレイヤーの位置をサーチして方向転換する
//	type 2: 画面の下から登場して上に向かって進み、一定間隔後はプレイヤーをサーチして方向転換する
//----------------------------------------------------------------------------------------------------------------------------------------

#include "AirEnemyBase.h"

#include "common.h"
#include "Player.h"

constexpr int   ANIM_UPDATE_INTERVAL = 5;		//アニメーション画像を入れ替えるフレーム数
constexpr int   ACTION_UPDATE_INTERVAL = 120;	//方向転換する一定のタイミング

namespace {

	Vector2 GetRandomTargetPositon(const Vector2& pos ) {

		// ランダムなX座標
		float targetX = static_cast<float>(std::rand()) / RAND_MAX * ScreenConfig::SRN_W ;

		// ランダムなY座標(制限:画面の下方向限定)
		float targetY = pos.y + static_cast<float>(std::rand()) / RAND_MAX * (ScreenConfig::SRN_H - pos.y);

		return Vector2(targetX, targetY);

 }
}


//========================================================================================
//					コンストラクタ
// 
// インスタンスが作られた時点でステータス、座標などの情報を取得する
//========================================================================================
ZOSHI::ZOSHI(std::weak_ptr<IPlayer> player, int num)
{
	Create(player, num);		//インスタンス生成時に必要なステータスを設定する
}

//========================================================================================
//								初期化
// 
// メンバ変数を全て初期化する
//========================================================================================
void ZOSHI::Init() {
	EnemyBase::Init();		//メンバ変数を初期化する
}


//========================================================================================
//							生成(ステータスの取得など)
// 第１引数 : プレイヤーの情報を持ったスマートポインタ
// 第２引数 : 敵の識別番号、及びタイプ。(100の位がタイプを表す [203 なら type 2、number 3となる])
// 
// インスタンス化に必要な情報を取得する
//	1.ステータスの初期値,設定値を取得する。
//	2_1.typeが 2 の時はx座標をplayerから一定距離話して設定し、y座標を画面の一番下に設定する
//  2_2. type 2以外の時はx座標はランダムでy座標は0からはじめる
//  3.activeやtypeなどEnemyBaseの変数で調整が必要なものを調整する

//========================================================================================
int ZOSHI::Create(std::weak_ptr<IPlayer> player, int number)
{
	auto useplayer = player.lock();		//スマートポインタを一時shared_ptrに変換する

	//	1.ステータスの初期値,設定値を取得する。
	EnemyBase::StatusSetup(EnemyStatusData::ZOSHI);

	
	//  2.activeやtypeなどEnemyBaseの変数で調整が必要なものを調整する
	AirEnemyBase::Create(useplayer, number);

	//	3_1.画面下から登場する特殊なタイプ
	if (status.type == 2) {
		position.y = ScreenConfig::SRN_H;
		AirEnemyBase::InitPostionPattern(useplayer->GetPosition().x);
		TergetRadian(useplayer->GetPosition());
	}

	//  3_2. 他のキャラと変わらない登場
	else {
		AirEnemyBase::InitPostionPattern();

	}


	return 0;
}


//========================================================================================
//							更新
// 第１引数 : プレイヤーの情報を持ったスマートポインタ
// 
// EnemyManagerに使ってもらうための関数
//  AirEnemyBase::Updateが固有のアクションを設定したUniqueUpdate関数を呼び出す。
//========================================================================================
int ZOSHI::Update(std::weak_ptr<IPlayer> player)
{
	return  AirEnemyBase::Update(player);
}

//========================================================================================
//							固有のアクション
// 第１引数 : プレイヤーの情報を持ったスマートポインタ
// 
//敵の種類によってかわる関数。
// 1.アニメーションの更新
// 2.設定された座標に向かってすすむ
//========================================================================================
int ZOSHI::UniqueUpdate(std::shared_ptr<IPlayer> player)
{

	// 1.アニメーションの更新
	AirEnemyBase::AnimUpdate(ANIM_UPDATE_INTERVAL);


	// 2.設定された座標に向かって
	Enemy_Patterns(MovePatternID::TowardsTarget);


	return ActionPattern01(player);
	
}


//========================================================================================
//							アクションパターン
// 第１引数 : プレイヤーの情報を持ったスマートポインタ
// 
// 一定のフレームに入り、方向転換しつつ弾を発射する
//		type 0:一定フレーム毎にランダムの座標に方向転換する
//		type 1:一定フレーム毎にプレイヤーの座標に方向転換する
//		type 2:同上
//========================================================================================
int ZOSHI::ActionPattern01(std::shared_ptr<IPlayer> player_)
{

	// 1.一定フレーム毎に入る
	if (ownframecount % ACTION_UPDATE_INTERVAL == 0)
	{
		Vector2 randomtarget = GetRandomTargetPositon(position);		//ランダムの座標を取得

		//タイプ別のアクション
		switch (status.type) {
		case 0:										//type 0:一定フレーム毎にランダムの座標に方向転換する
			TergetRadian(randomtarget);		
			break;
		case 1:										//type 1:一定フレーム毎にプレイヤーの座標に方向転換する
		case 2:										//type 2:同上
			TergetRadian(player_->GetPosition());
			break;
		default :
			break;
		}
		
		return OnBulletShot;			//弾も放つ
		
	}
	return 0;
}

