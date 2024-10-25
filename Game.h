#ifndef GAME_H
#define GAME_H

#include "common.h"
//#include "commonutility.h"
#include "Geometry.h"
//#include "Player.h"
#include <array>
#include <map>
#include <vector>

//-------------------------------------------------------------------------------------------
//			Gameで使う構造体やプロトタイプ宣言をしている
// 
//構造体は ・プレイヤー ・空中敵 ・地上敵 ・ボス　・マップ ・各種画像データ など
// プロトタイプ宣言は ゲームループ,各オブジェクトの初期化、生成、更新、描画
//-------------------------------------------------------------------------------------------


//==============================================================
//					/*プレイヤー関係の定義*/
// 
//==============================================================

namespace PlayerConfig {
	constexpr int SPEED = 5;		//プレイヤーの移動速度	
	constexpr int PLAYER_HITBOX_SIZE = 16;		//画像のサイズ
	constexpr int PLAYER_PIC_SIZE = 32;		//画像のサイズ

	constexpr int SIGHT_HITBOX_SIZE = 32;		//画像のサイズ
	constexpr int SIGHT_PIC_SIZE = 32;			//画像のサイズ

	constexpr int MAX_SHOT = 3;		//画面内に表示できるショットの数
	constexpr int SHOT_SPEED = 20;	//ショットの弾速
	constexpr int SHOT_SPEED_HOLLOW = 8;
	constexpr int SHOT_HITBOX_SIZE = 8;		//画像のサイズ
	constexpr int SHOT_PIC_SIZE = 8;		//画像のサイズ

	constexpr int BOM_SPEED = 5;		//ショットの弾速
	constexpr int BOM_RANGE = 100;		//ボムの射程距離
	constexpr int BUNBER_HITBOX_SIZE = 24;		//画像のサイズ
	constexpr int BON_PIC_SIZE = 8;		//画像のサイズ
}
//==============================================================
//					/*エネミー共通の定義*/
// 
//==============================================================
namespace AirEnemyConfig {
	constexpr int PIC_LINE_WIDE = 8;		//空中敵の画像の行の数
	constexpr int MAX_ENEMY = 20;			//敵の最大出現数( 空中と地上は別カウント)
}
namespace GroundEnemyConfig {
	constexpr int PIC_LINE_WIDE = 4;		//空中敵の画像の行の数
	constexpr int MAX_ENEMY = 20;			//敵の最大出現数( 空中と地上は別カウント)
}
namespace EnemyShotConfig {
	constexpr int HITBOX_SIZE = 8;		//画像のサイズ
	constexpr int PIC_SIZE = 8;		//画像のサイズ
	constexpr int SPEED = 4;			//敵弾の基本の速度
	constexpr int MAX_SHOT = 17;			//敵弾の基本の速度

}
constexpr int MAX_LEVEL	= 64;			//敵の出現レベルの上限

constexpr int BOMBER_PIC_SIZE = 47;			//敵の出現レベルの上限



//============================================
//ボス & 砲台、コアのステータス
//============================================
//typedef struct BOSS {
//	bool F;				//出現フラグ
//	bool down;			//撃墜判定(コア破壊)
//	ENEMY_ST enemy[5];	//砲台×4とコアの情報
//	float center_x;		//x軸中心座標
//	float center_y;		//y軸中心座標
//	int pic_x;			//左上x座標(スプライト用)
//	int pic_y;			//左上y座標(スプライト用)
//
//	Bmp* pic[120];				//本体を分割したスプライト
//	Bmp* pats[5];				//撃破前の砲台とコアの画像
//}BOSS;

//============================================
//デバック用の構造体
//============================================
struct DenugState {
	bool G_enemy_stop;
	bool A_enemy_stop;
	bool Player_invalid;
};







//==============================================================================================
//					全体シーンで使用するデータ
// 
// ・Gameで加算され、リザルトで表示するscore
// ・タイトル画面で1Playerか2Playerどちらかを選ぶかで初期値が変わるlife
//==============================================================================================
class GameStatus {
public:
	GameStatus():Score(0), Life(0) {};
	~GameStatus() {}
	// スコアのゲッターとセッター
	int score() const { return Score; }
	void score(int s) { Score = s; }
	// ライフのゲッターとセッター
	int life() const { return Life; }
	void life(int l) { Life = l; }

private:
	int Score;
	int Life;
};
//==============================================================================================
//					instanceとして存在するオブジェクトの基底クラス
//==============================================================================================
class GameObject {
public:
	GameObject(): position(0, 0),hitbox(0,0,0,0),active(false) {
		// 共通の初期化処理
	}

	virtual void InitClear() {
		 position = Vector2::zero;
		 hitbox = Boxcollider::zero;
		 active = false;
	}

	virtual Vector2 GetPosition()const {	return position;	}
	virtual void SetPosition(Vector2 pos){	position = pos;	}

	virtual Boxcollider GetHitbox()const {	return hitbox;	}
	virtual void SetHitbox(Boxcollider box){hitbox = box;	}

	virtual bool GetActive() { return active; }
	virtual void SetActive(bool isactive) { active = isactive; }


	~GameObject() = default;

protected :
	Vector2 position;
	Boxcollider hitbox;
	bool active;
};


#endif // GAME_H
