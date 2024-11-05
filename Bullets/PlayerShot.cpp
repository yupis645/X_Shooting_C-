#include "PlayerShot.h"


//===============================================================
//					ショットの作成
// 
// 発射最大数以下なら座標や当たり判定を設定して弾を生成する
// ・発射フラグを建てる
// ・当たり判定を設定する
// ・発射カウントを加算する
//===============================================================
int PlayerShot::Create(Vector2 pos) {

    active = true;					//ショット発射フラグを立てる

    //SetRectSquareValues(hitbox,SHOT_HITBOX_SIZE);			//当たり判定を設定する(自機の当たり判定と同じ大きさ)
    hitbox.CenterPositionSync(pos, PlayerConfig::SHOT_HITBOX_WIDTH,PlayerConfig::SHOT_HITBOX_HEIGHT);
    position = pos;

    return 0;
}


//===============================================================
//					ショットの初期化
// 
// 基底クラスから追加された変数はないので基底クラスのinitで初期化
//===============================================================
int PlayerShot::Init() {
    InitClear();

    return false;
}


//===============================================================
//					ショットの更新
// 
// フラグが建っているショットを全て更新する
// ・Y座標移動
// ・画面外に出たらその管理番号のショットを初期化する
//===============================================================
int PlayerShot::Update(int framecount) {

    if (!active) return 0;

    position.y -= PlayerConfig::SHOT_SPEED;		//ショットの座標を設定した値分進める
    hitbox.CenterPositionSync(position, PlayerConfig::SHOT_HITBOX_WIDTH, PlayerConfig::SHOT_HITBOX_HEIGHT);

    if (position.y < 0) {			//ショットが画面外に出たら
        Init();
    }

    return 0;
}
