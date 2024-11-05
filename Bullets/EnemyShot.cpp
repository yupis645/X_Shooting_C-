#include "EnemyShot.h"

#include "IPlayer.h"

using namespace EnemyShotConfig;


EnemyShot::EnemyShot() : rad(0) {  }

// 基底クラスの Update 関数をオーバーライド
int EnemyShot::Create(Vector2 startPos, Vector2 targetPos, float radianplus = 0) {

    active = true;
    position = startPos;

    /*hitbox初期化*/
    hitbox.CenterPositionSync(position, PIC_SIZE);
    //_s->shot[Nextshotnum].player_x = (int)_p.center_x;				//この関数に入った瞬間のプレイヤー座標を記する(X軸)
    //_s->shot[Nextshotnum].player_y = (int)_p.center_y;				//この関数に入った瞬間のプレイヤー座標を記する(Y軸)

    rad = atan2(targetPos.y - (float)hitbox.top, targetPos.x - (float)hitbox.left);		//三角形の角度を算出する

    //発射する弾の向きを正負によって方向を絞る
    if (radianplus != 0) {
        rad += radianplus;
    }

    return 0;
}

int EnemyShot::Init() {
    InitClear();
    rad = 0;

    return 0;
}
int EnemyShot::Update(int framecount)  {

    if (!active) return 0;

    //弾が画面内にある場合
    if (hitbox.left >= 0 && hitbox.top >= 0 && hitbox.left <= ScreenConfig::SRN_W && hitbox.top <= ScreenConfig::SRN_H) {
        position.x += EnemyShotConfig::SPEED* cos(rad);		//X軸の移動
        position.y += EnemyShotConfig::SPEED * sin(rad);		//Y軸の移動

        /*弾の当たり判定の同期*/
        hitbox.CenterPositionSync(position, PIC_SIZE);

    }
    //弾が画面外に出た場合
    else {  Init(); }


    return 0;
}





