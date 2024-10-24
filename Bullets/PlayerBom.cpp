#include "PlayerBom.h"

using namespace PlayerConfig;


//===============================================================
//					ボムの作成
// 
// 画面上に一つしか存在できない
// ・爆発範囲の設定
// ・発射座標の設定
// ・発射したY座標をrangeに保存する
//===============================================================
int PlayerBom::Create(Vector2 pos) {
    active = true;			//有効化する
    bomber = false;				    //着弾フラグをOFFにする

    hitbox.CenterPositionSync(pos, BUNBER_HITBOX_SIZE);     //爆発範囲の設定
    range = static_cast<int>(pos.y);			//ボムの発射位置を決める(自機のy軸の一番上)
    bombertime = 0;
    position = pos;

    return 0;
}


//===============================================================
//					ボムの初期化
// 
// 基底クラスのinitと組み合わせて初期化
//===============================================================
int PlayerBom::Init() {
    InitClear();
    range = 0;              
    bomber = false;

    return 0;
}


//===============================================================
//					ボムの更新
// 
// 射程距離でボムが爆発する。その前後で処理が違う
// 爆発前 : Y軸方向移動する。射程距離に達している場合、爆発フラグを建てる
// 爆発後 : 一定時間、爆発フラグが建った瞬間の座標を中心に設定されている爆発判定を出す
// 
//・当たり判定と座標を同期させる
// ・爆発フラグが建つ前はボムの持つスピードで座標移動し、一定距離進むと
//		ボムの出現フラグをfalse、爆発フラグをtrueに、rangeを0にする
// 
// ・爆発フラグが建っている場合はrange変数を制限時間として利用し、
//		10フレームに達するまでは中心座標をｓ浮くロールに合わせて移動させ、
//		時間になったらフラグを消去する
// 
//===============================================================
int PlayerBom::Update(int framecount,float shootspeed) {

    if (!active) return 0; //ボムの発射フラグがONなら

    /*ボム(爆破前)の更新*/
    if (bomber == false) {					
        FallUpdate();
    }

    /*ボム(爆発後)の更新*/
    else {				
        BomberUpdate(framecount);
    }


    return 0;
}

//===============================================================
//					ボムを発射している間
// 
//一定距離まですすむ
//===============================================================
void PlayerBom::FallUpdate()
{
    position.y -= PlayerConfig::BOM_SPEED;			//設定されたボムの速度もそって画面上に向かって進む

    if (ABS(range - position.y) >= BOM_RANGE) {		//ボムの発射地点から特定距離まで進んだら(画像のサイズもあるので判定はhitboxのtopからとっている)
        bomber = true;								//攻撃判定をONにする
    }
}


//===============================================================
//					爆発している間の更新
// 
// bombertimeが一定時間地上に対して攻撃判定を出し続ける
// また画面のスクロールに合わせて攻撃判定も移動する
//===============================================================
void PlayerBom::BomberUpdate(int framecount)
{

    bombertime++;							//初期化したrange変数を使って攻撃判定の出現時間を制御する

    //爆発中は座標をスクロールに合わせる
    if (framecount % MapConfig::SCROLL_SPEED == 0) {
        position.y++;
    }
    if (bombertime % 10 == 0) {				//攻撃判定が出て10フレーム経過したら
        Init();                             //完全終了(初期化)
    }

    //画面スクロールに対する位置の同期(爆発後)				
    hitbox.CenterPositionSync(position, PlayerConfig::BUNBER_HITBOX_SIZE);

}


