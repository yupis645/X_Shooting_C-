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



/////-------------------------------------------------------------

// 敵画像のインデックス定義
enum Air_EnemyType {
	TOROID = 0,
	TORKAN,
	GIDDOSPARIO,
	ZOSHI,
	JARA,
	KAPI,
	TERRAZI,
	ZAKATO,
	BRAGZAKATO,
	GARUZAKATO,
	BACURA,
	A_ENEMY_SUMS		// 敵の総数
};
enum Ground_EnemyType {
	BARRA = 0,
	ZOLBAK,
	LOGRAM,
	DOMOGRAM,
	DEROTA,
	GROBDA,
	BOZALOGRAM,
	SOL,
	GARUBARRA,
	GARUDEROTA,
	AG_ALG,
	AG_CORE,
	SPECIALFLAG,
	G_ENEMY_SUMS // 敵の総数
};


enum GameModeStateNumber {
	Title = 0,
	Game,
	Option,
	Result,
	GameEnd = 99,

};

//============================================
//  空中、地上共通のステータス
//============================================
typedef struct ENEMY_DATA {
	int number;			//エネミーの種類を区別するための番号
	int hitbox_size;	//当たり判定のサイズ
	int pic_size;		//画像サイズ
	int type;		//同一個体の違う挙動
	int dir;		//向き
	int anim;		//アニメーションパターンの切り替えタイミング
	int anim_sum;	//行動パターンの数
	int points;		//ポイント
	float speed;	//移動速度
	float acc;		//加速度
}ENEMY_DATA;





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
	}

	virtual Vector2 GetPosition()const {	return position;	}
	virtual void SetPosition(Vector2 pos){	position = pos;	}

	virtual Boxcollider GetHitbox()const {	return hitbox;	}
	virtual void SetHitbox(Boxcollider box){hitbox = box;	}

	virtual bool GetActive() { return active; }
	virtual void SetActive(bool isactive) { active = isactive; }


	virtual ~GameObject() {}

protected :
	Vector2 position;
	Boxcollider hitbox;
	bool active;
};

class EnemyStatusData {
public:
	EnemyStatusData(int num = 0,int hsize = 0,int psize = 0,int t = 0,int a_num = 0,int a_sum = 0,int p = 0,float sp = 0,float ac = 0) :
		number(num), hitbox_size(hsize), pic_size(psize), type(t), anim_number(a_num), anim_sum(a_sum), points(p), speed(sp), acceleration(ac) {}
	~EnemyStatusData() {}

	virtual int Init()
	{
		number = 0; 
		hitbox_size = 0;
		pic_size = 0;
		type = 0;
		anim_number = 0;
		anim_sum = 0; 
		points = 0;
		speed = 0; 
		acceleration = 0;

		return 0;
	}

	//データをA = Bの形で代入できるようにする代入演算子
	EnemyStatusData& operator=(const EnemyStatusData& set) {
		if (this != &set) {  // 自己代入を防ぐ
			this->number = set.number;
			this->hitbox_size = set.hitbox_size;
			this->pic_size = set.pic_size;
			this->type = set.type;
			this->anim_number = set.anim_number;
			this->anim_sum = set.anim_sum;
			this->points = set.points;
			this->speed = set.speed;
			this->acceleration = set.acceleration;
		}
		return *this;		//値を代入した自分を返す
	}

	int number;			//エネミーの種類を区別するための番号
	int hitbox_size;	//当たり判定のサイズ
	int pic_size;		//画像サイズ
	int type;		//同一個体の違う挙動
	int anim_number;		//行動パターン番号
	int anim_sum;	//行動パターンの数
	int points;		//ポイント
	float speed;	//移動速度
	float acceleration;		//加速度
};

// 敵データの配列
const std::array<EnemyStatusData, 11> A_ENEMY_DATA_ARRAY = {
	EnemyStatusData(0 , 32, 32, 1,  0, 8,   30, 2.0f, 0.04f),  // トーロイド
	EnemyStatusData(1 , 32, 32, 0,  8, 7,   50, 4.0f, 0.0f),   // タルケン
	EnemyStatusData(2 , 16, 32, 0, 16, 8,   10, 7.0f, 0.0f),  // ギドスパリオ
	EnemyStatusData(3 , 32, 32, 2, 24, 4,   70, 3.0f, 0.0f),  // ゾシー
	EnemyStatusData(4 , 32, 32, 0, 32, 6,  150, 4.0f, 0.04f),// ジアラ
	EnemyStatusData(5 , 32, 32, 0, 40, 7,  300, 4.0f, 0.15f),// カピ
	EnemyStatusData(6 , 32, 32, 0, 48, 7,  700, 5.0f, 0.08f),// テラジ
	EnemyStatusData(7 , 16, 32, 3, 56, 1,  100, 3.0f, 0.0f), // ザカート
	EnemyStatusData(8 , 16, 32, 3, 64, 1,  600, 3.0f, 0.0f), // ブラグザカート
	EnemyStatusData(9 , 16, 32, 0, 72, 1, 1000, 3.0f, 0.0f),// ガルザカート
	EnemyStatusData(10, 48, 48, 0, 56, 8,    0, 2.0f, 0.0f)   // バキュラ
};

const std::array<EnemyStatusData, 13> G_ENEMY_DATA_ARRAY = {
	EnemyStatusData(50, 32, 32, 0,  1, 1,  100, 0.0f , 0.0f),      // バーラ
	EnemyStatusData(51, 32, 32, 0,  4, 4,  200, 0.0f , 0.0f),      // ゾルバグ
	EnemyStatusData(52, 32, 32, 4,  8, 4,  300, 0.0f , 0.0f),      // ログラム
	EnemyStatusData(53, 32, 32, 0, 12, 4,  800, 0.75f, 0.5f),   // ドモグラム
	EnemyStatusData(54, 32, 32, 0, 16, 4,  200, 0.0f , 0.0f),		    // デローダ
	EnemyStatusData(55, 32, 32, 8, 20, 4,  200, 0.5f , 0.5f),   // グロブダー
	EnemyStatusData(56, 32, 32, 0, 24, 1,  600, 0.0f , 0.0f),      // ボザログラム
	EnemyStatusData(57, 32, 32, 0, 28, 4, 2000, 0.0f , 0.0f),      // ソル
	EnemyStatusData(58, 32, 63, 0, 20, 1,  300, 0.0f , 0.0f),      // ガルバーラ
	EnemyStatusData(59, 32, 64, 0, 24, 4, 2000, 0.0f , 0.0f),      // ガルデロータ
	EnemyStatusData(60, 16, 48, 0,  4, 0, 1000, 0.0f , 0.0f),      // アルゴ
	EnemyStatusData(61, 32, 64, 0,  4, 1, 4000, 0.0f , 0.0f),      // A/Gコア
	EnemyStatusData(62, 32, 32, 0,  3, 1, 1000, 0.0f , 0.0f)       // SPフラッグ
};

// 敵の画像データ管理用のマップ
//std::map<int, std::vector<Bmp*>> ImageManager::air_enemy;
//std::map<int, std::vector<Bmp*>> ImageManager::ground_enemy;

//
//// 画像データの構造体
//struct PNGDATA {
//	const wchar_t* Title;
//	const wchar_t* Player;
//	const wchar_t* Shot;
//	const wchar_t* A_Enemy;
//	const wchar_t* G_Enemy;
//	const wchar_t* Boss;
//	const wchar_t* BossSub;
//	const wchar_t* bomber;
//	const wchar_t* Map;
//};
//
//class ImageManager {
//public:
//	// プレイヤーや弾の画像
//	static Bmp* Title;
//	static Bmp* player[12];
//	static Bmp* bullet[3];
//	static Bmp* boss[120];
//	static Bmp* bosspats[5];
//
//	static Bmp* PlayerBomber[6];
//	static Bmp* EnemyBomber[6];
//
//	// 空中と地上の敵画像を map で管理
//	static std::map<int, std::vector<Bmp*>> air_enemy;
//	static std::map<int, std::vector<Bmp*>> ground_enemy;
//
//	// PNGデータを管理する構造体のインスタンス
//	static PNGDATA PngData;
//
//	ImageManager() {}
//	~ImageManager() {}
//
//	// 初期化関数
//	static void Init() {
//		// プレイヤー画像のロード
//		LoadDivBmp(PngData.Player, 0, 0, PlayerConfig::PIC_SIZE, PlayerConfig::PIC_SIZE, 6, 2, player);
//		LoadDivBmp(PngData.Shot, 0, 0, PlayerShotConfig::PIC_SIZE, PlayerShotConfig::PIC_SIZE, 3, 1, bullet);
//
//		// 空中敵の画像のロード
//		for (int i = 0; i < A_ENEMY_SUMS; i++) {
//			std::vector<Bmp*> enemyPics(AirEnemyConfig::PIC_LINE_WIDE * 11);
//			LoadDivBmp(PngData.A_Enemy, 0, 0, A_ENEMY_DATA_ARRAY[i].pic_size, A_ENEMY_DATA_ARRAY[i].pic_size,
//				AirEnemyConfig::PIC_LINE_WIDE, 11, enemyPics.data());
//			air_enemy[i] = enemyPics;
//		}
//
//		// 地上敵の画像のロード
//		for (int i = 0; i < G_ENEMY_SUMS; i++) {
//			std::vector<Bmp*> enemyPics(GroundEnemyConfig::PIC_LINE_WIDE * 11);
//			LoadDivBmp(PngData.G_Enemy, 0, 0, G_ENEMY_DATA_ARRAY[i].pic_size,
//				G_ENEMY_DATA_ARRAY[i].pic_size, AirEnemyConfig::PIC_LINE_WIDE, 9, enemyPics.data());
//			ground_enemy[i] = enemyPics;
//		}
//
//		// ボスのパーツと画像のロード
//		LoadDivBmp(PngData.BossSub, 0, 0, 48, 16, 4, 2, bosspats);
//		LoadDivBmp(PngData.Boss, 0, 0, 32, 32, 11, 11, boss);
//		LoadDivBmp(PngData.bomber, 0, 0, 47, 47, 6, 1, PlayerBomber);
//		LoadDivBmp(PngData.bomber, 0, 0, 47, 47, 12, 1, EnemyBomber);
//	}
//};
//
//// PNGDATA の定義
//PNGDATA ImageManager::PngData = {
//	L"res/STG_Title.png",
//	L"res/EDGE STG自機.png",
//	L"res/STG 弾.png",
//	L"res/STG_A_enemy.png",
//	L"res/STG_G_enemy.png",
//	L"res/BOSS.png",
//	L"res/BOSS_PATS.png",
//	L"res/bomber.png",
//	L"res/Map/MapChip.png"
//};
//
//

#endif // GAME_H
