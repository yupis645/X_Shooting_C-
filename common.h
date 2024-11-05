#ifndef GAME_DEFINITIONS_H
#define GAME_DEFINITIONS_H

#include	"conioex.h" 
#include "Geometry.h"

//-------------------------------------------------------------------------------------------
//			Gameで使う構造体やプロトタイプ宣言をしている
// 
//構造体は ・プレイヤー ・空中敵 ・地上敵 ・ボス　・マップ ・各種画像データ など
// プロトタイプ宣言は ゲームループ,各オブジェクトの初期化、生成、更新、描画
//-------------------------------------------------------------------------------------------

#define TestMode true			//タイトルやポーズ画面に操作説明が出る & デバックモードが使用できるようになる。

// DebugOn と StageRupe は TestMode 有効時のみ作動する
#define DebugOn true			//TestModeがtrueの時のみ使用できるデバックモードのフラグ。falseにするとデバックモードに入れなくなる
#define StageRupe false			//trueなら指定したステージからループする。falseならボスを倒した地点で終了
//ここまで





//==============================================================
//					/*プレイヤー関係の定義*/
// 
//==============================================================

namespace PlayerConfig {
	constexpr int SPEED = 5;		//プレイヤーの移動速度	
	constexpr int PLAYER_HITBOX_SIZE = 16;		//画像のサイズ
	constexpr int PLAYER_PIC_SIZE = 32;		//画像のサイズ

	constexpr int SIGHT_HITBOX_SIZE = 32;		//画像のサイズ
	constexpr int SIGHT_PIC_SIZE = 32;		//画像のサイズ

	constexpr int MAX_SHOT = 3;		//画面内に表示できるショットの数
	constexpr int SHOT_SPEED = 20;		//ショットの弾速
	constexpr int SHOT_SPEED_HOLLOW = 8;
	constexpr int SHOT_HITBOX_WIDTH = 32;		//画像のサイズ
	constexpr int SHOT_HITBOX_HEIGHT = 16;		//画像のサイズ
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
constexpr int MAX_LEVEL = 64;			//敵の出現レベルの上限

namespace SpriteSize {
	constexpr int PLAYER       = 32;
	constexpr int LOOKON_SIGHT = 32;
	constexpr int BULLET       = 8;
	constexpr int ENEMY_SMALL  = 32;
	constexpr int ENEMY_MEDIUM = 48;
	constexpr int ENEMY_LARGE  = 64;
	constexpr int BOMBER	   = 47;
	constexpr int MAP_CHIP	   = 32;
}


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
	GameStatus() :Score(0), Life(0) {};
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
	GameObject() : position(0, 0), hitbox(0, 0, 0, 0), active(false) {
		// 共通の初期化処理
	}

	virtual void InitClear() {
		position = Vector2::zero;
		hitbox = Boxcollider::zero;
		active = false;
	}

	virtual Vector2 GetPosition()const { return position; }
	virtual void SetPosition(Vector2 pos) { position = pos; }

	virtual Boxcollider GetHitbox()const { return hitbox; }
	virtual void SetHitbox(Boxcollider box) { hitbox = box; }

	virtual bool GetActive() { return active; }
	virtual void SetActive(bool isactive) { active = isactive; }


	~GameObject() = default;

protected:
	Vector2 position;
	Boxcollider hitbox;
	bool active;
};


//==============================================================
//					画面関連の定義
// 
//==============================================================
namespace ScreenConfig {
	constexpr int PXW        = 1;		     //サイズ比率(横幅)
	constexpr int PXH        = 1;		     //サイズ比率(高さ)
	constexpr int WIN_W      = 200 * 3;	     //(8*25*4)	//ウィンドウサイズ(横幅)
	constexpr int WIN_H      = 260 * 3;		 //(8*25*3)	//ウィンドウサイズ(縦幅)
	constexpr int SRN_W      = WIN_W / PXW;	 //画面サイズ(横幅)
	constexpr int SRN_H      = WIN_H / PXH;	 //画面サイズ(高さ)
	constexpr int CENTER_X   = SRN_W / 2;	 //画面の中央X座標
	constexpr int CENTER_Y   = SRN_H / 2;	 //画面の中央Y座標
	constexpr int WORD_W     = 8;	         //1文字の横幅
	constexpr int HALFWORD_W = 4;		     //半角文字の横幅
	constexpr int WORD_H     = 15;		     //1文字の高さ
}

//==============================================================
//				画面ID：現在の画面の状態を表す
// 
//==============================================================
enum SceneID {
	TITLE = 1,     // タイトル
	GAME = 2,      // ゲーム
	RESULT = 3,    // 結果
	OPTION = 4,    // オプション
	APP_EXIT = 999 // アプリ終了
};

namespace SceneConfig {
	constexpr int FRAME_COUNT_VALUE = 1;		//フレームカウントする際に1フレームで加算する値

}

constexpr int AIR_ENEMY_MAX_LEVEL = 64;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//==============================================================
//					マップ関連の定義
// 
//==============================================================
namespace MapConfig {
	constexpr int MAP_W = ScreenConfig::SRN_W / 31;	//マップのサイズ(画面の大きさ / マップチップのサイズ)	
	constexpr int MAP_H = ScreenConfig::SRN_H / 31;	//マップのサイズ(画面の大きさ / マップチップのサイズ)
	constexpr int CHIP_SIZE = 32;			//マップチップのサイズ(正方形)
	constexpr int SCROLL_SPEED = 1;		//スクロールのスピード
	constexpr int MAX_STAGE = 3;		//ステージ数
}

enum class TextureBaseName {
	Title,
	Player_Sight,
	Bullet,
	Bomber,
	AirEnemy,
	GroundEnemy,
	Boss,
	Algo_Core,
	MapChip
};

enum class SpriteName {
	Title,
	Player_Sight,
	Bullet,
	Bomber,
	AirEnemy_SmallSprite,
	AirEnemy_MiddleSprite,
	GroundEnemy_SmallSprite,
	GroundEnemy_LargeSprite,
	Boss,
	Algo_Core,
	MapChip
};

enum class TextureType {
	Title,
	Player,
	Targetsight,
	Bullet,
	Bom,
	Map,
	Bomber,
	PlayerBomber,
	BomBomber,
	Air_EnemyBomber,
	Ground_EnemyBomber,

	AirEnemy,
	Toroid,
	Torkan,
	Giddospario,
	Zoshi,
	Jara,
	Kapi,
	Terrazi,
	Zakato,
	Bragzakato,
	Garuzakato,
	Bacura,
	AirEnemyEnd,

	GroundEnemy,
	Barra,
	Zolbak,
	Logram,
	Domogram,
	Derota,
	Grobda,
	Bozalogram,
	Sol,
	Garubarra,
	Garuderota,
	Boss,
	BossParts,
	Algo,
	Ad_core,
	Spflag,
	GroundEnemyEnd
};

//==============================================================
//					PNGデータ関連
// 
//==============================================================
struct SpritesConfig {
	int width;   // 1つのスライスの横幅
	int height;  // 1つのスライスの縦幅
	int rows;    // 行数
	int columns; // 列数
};


namespace SpritesConfigs {
	const std::map<SpriteName, TextureConfig> Configs = {
		{Title                  ,{198						, 58						,  1,  1 }},
		{Player_Sight           ,{SpriteSize::PLAYER		, SpriteSize::PLAYER		,  6,  2}},
		{Bullet                 ,{SpriteSize::BULLET		,SpriteSize::BULLET			,  3,  1,}},
		{Bomber                 ,{SpriteSize::BOMBER		, SpriteSize::BOMBER		,  6,  2}},
		{AirEnemy_SmallSprite   ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	, 11, 11}},
		{AirEnemy_MiddleSprite  ,{SpriteSize::ENEMY_MEDIUM	, SpriteSize::ENEMY_MEDIUM	,  8, 8}},
		{GroundEnemy_SmallSprite,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  4, 8}},
		{GroundEnemy_LargeSprite,{SpriteSize::ENEMY_LARGE	, SpriteSize::ENEMY_LARGE	,  4, 7}},
		{Boss                   ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	, 11, 11}},
		{Algo_Core              ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  4, 2}},
		{MapChip                ,{SpriteSize::MAP_CHIP		, SpriteSize::MAP_CHIP		, 12, 10}}
	};
}
//==============================================================
//					PNGデータ関連
// 
//==============================================================
struct TextureConfig {
	int width;   // 1つのスライスの横幅
	int height;  // 1つのスライスの縦幅
	int rows;    // 行数
	int columns; // 列数
	int startindex;
	int indexcount;
};

namespace TextureConfigs {
	const std::map<TextureType, TextureConfig> Configs = {
		{TextureType::Title          ,{198, 58,  1,  1, 0, 1}},
		{TextureType::Player         ,{SpriteSize::PLAYER		, SpriteSize::PLAYER		,  6,  2, 2, 3}},
		{TextureType::Targetsight    ,{SpriteSize::LOOKON_SIGHT	, SpriteSize::LOOKON_SIGHT	,  6,  2, 0, 2}},
		{TextureType::Bullet         ,{SpriteSize::BULLET		,SpriteSize::BULLET			,  3,  1, 0, 2}},
		{TextureType::Bom            ,{SpriteSize::BULLET		,  SpriteSize::BULLET		,  3,  1, 2, 1}},
		{TextureType::Boss           ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	, 11, 11, 0, 11 * 11}},
		{TextureType::BossParts      ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  5,  1, 0, 1}},
		{TextureType::Bomber         ,{SpriteSize::BOMBER		, SpriteSize::BOMBER		,  6,  1, 0, 6}},
		{TextureType::Air_EnemyBomber,{SpriteSize::BOMBER		, SpriteSize::BOMBER		,  6,  2, 6, 6}},
		{TextureType::Map            ,{SpriteSize::MAP_CHIP		, SpriteSize::MAP_CHIP		, 12, 10, 0, 12 * 10}},

		{TextureType::Toroid         ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  8, 1 , 0, 8}},
		{TextureType::Torkan         ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  8, 2 , 8, 7}},
		{TextureType::Giddospario    ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  8, 3 ,16, 8}},
		{TextureType::Zoshi          ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  8, 4 ,24, 4}},
		{TextureType::Jara           ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  8, 5 ,32, 6}},
		{TextureType::Kapi           ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  8, 6 ,40, 7}},
		{TextureType::Terrazi        ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  8, 7 ,48, 7}},
		{TextureType::Zakato         ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  8, 8 ,56, 1}},
		{TextureType::Bragzakato     ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  8, 9 ,64, 1}},
		{TextureType::Garuzakato     ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  8,10 ,72, 1}},
		{TextureType::Bacura         ,{SpriteSize::ENEMY_MEDIUM	, SpriteSize::ENEMY_MEDIUM	,  8, 8 ,56, 8}},

		{TextureType::Barra          ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  4, 1 ,0,  2}},
		{TextureType::Zolbak         ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  4, 2 ,4,  4}},
		{TextureType::Logram         ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  4, 3 ,8,  4}},
		{TextureType::Domogram       ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  4, 4 ,12, 4}},
		{TextureType::Derota         ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  4, 5 ,16, 4}},
		{TextureType::Grobda         ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  4, 6 ,20, 4}},
		{TextureType::Bozalogram     ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  4, 7 ,24, 1}},
		{TextureType::Sol            ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  4, 8 ,28, 4}},
		{TextureType::Garubarra      ,{SpriteSize::ENEMY_LARGE	, SpriteSize::ENEMY_LARGE	,  4, 6 ,20, 1}},
		{TextureType::Garuderota     ,{SpriteSize::ENEMY_LARGE	, SpriteSize::ENEMY_LARGE	,  4, 7 ,24, 4}},
		{TextureType::Algo           ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  4, 1 , 0, 4}},
		{TextureType::Ad_core        ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  4, 2 , 4, 1}},
		{TextureType::Spflag         ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  4, 1 , 2, 1}}
	};
}

struct EnemyStatus {
	int number;			//エネミーの種類を区別するための番号
	int hitbox_size;	//当たり判定のサイズ
	int pic_size;		//画像サイズ
	int type;		    //同一個体の違う挙動
	int anim_sum;	    //行動パターンの数
	int points;		    //ポイント
	float speed;	    //移動速度
	float acceleration;	//加速度
};

// 敵データの配列
namespace EnemyStatusData{
	constexpr EnemyStatus DUMMY      {-1 ,  0,  0, 0,  0,    0, 0.0f, 0.0f  };	// ダミー
	constexpr EnemyStatus TOROID     { 0 , 32, 32, 0,  8,   30, 2.0f, 0.04f };	// トーロイド
	constexpr EnemyStatus TORKAN     { 1 , 32, 32, 0,  6,   50, 4.0f, 0.0f  };   // タルケン
	constexpr EnemyStatus GIDDOSPARIO{ 2 , 16, 32, 0,  8,   10, 7.0f, 0.0f  };   // ギドスパリオ
	constexpr EnemyStatus ZOSHI      { 3 , 32, 32, 0,  4,   70, 3.0f, 0.0f  };   // ゾシー
	constexpr EnemyStatus JARA       { 4 , 32, 32, 0,  6,  150, 4.0f, 0.06f };   // ジアラ
	constexpr EnemyStatus KAPI       { 5 , 32, 32, 0,  7,  300, 4.0f, 0.15f };   // カピ
	constexpr EnemyStatus TERRAZI    { 6 , 32, 32, 0,  7,  700, 5.0f, 0.08f };   // テラジ
	constexpr EnemyStatus ZAKATO     { 7 , 16, 32, 0,  1,  100, 3.0f, 0.0f  };   // ザカート
	constexpr EnemyStatus BRAGZAKATO { 8 , 16, 32, 0,  1,  600, 3.0f, 0.0f  };   // ブラグザカート
	constexpr EnemyStatus GARUZAKATO { 9 , 16, 32, 0,  1, 1000, 3.0f, 0.0f  };   // ガルザカート
	constexpr EnemyStatus BACURA     { 10, 48, 48, 0,  8,    0, 2.0f, 0.0f  };   // バキュラ

	constexpr EnemyStatus BARRA      { 50, 32, 32, 0,  1,  100, 0.0f , 0.0f };   // バーラ
	constexpr EnemyStatus ZOLBAK     { 51, 32, 32, 0,  4,  200, 0.0f , 0.0f };   // ゾルバグ
	constexpr EnemyStatus LOGRAM     { 52, 32, 32, 0,  4,  300, 0.0f , 0.0f };   // ログラム
	constexpr EnemyStatus DOMOGRAM   { 53, 32, 32, 0,  4,  800, 0.75f, 0.5f };   // ドモグラム
	constexpr EnemyStatus DEROTA     { 54, 32, 32, 0,  4,  200, 0.0f , 0.0f };   // デローダ
	constexpr EnemyStatus GROBDA     { 55, 32, 32, 0,  4,  200, 0.5f , 0.5f };   // グロブダー
	constexpr EnemyStatus BOZALOGRAM { 56, 32, 32, 0,  1,  600, 0.0f , 0.0f };   // ボザログラム
	constexpr EnemyStatus SOL        { 57, 32, 32, 0,  4, 2000, 0.0f , 0.0f };   // ソル
	constexpr EnemyStatus GARUBARRA  { 58, 32, 63, 0,  1,  300, 0.0f , 0.0f };   // ガルバーラ
	constexpr EnemyStatus GARUDEROTA { 59, 32, 64, 0,  4, 2000, 0.0f , 0.0f };   // ガルデロータ
	constexpr EnemyStatus ALGO       { 60, 16, 48, 0,  0, 1000, 0.0f , 0.0f };   // アルゴ
	constexpr EnemyStatus AD_CORE    { 61, 32, 64, 0,  1, 4000, 0.0f , 0.0f };   // A/Gコア
	constexpr EnemyStatus SPFLAG     { 62, 32, 32, 0,  1, 1000, 0.0f , 0.0f };   // SPフラッグ
}

namespace EnemyTextureConfig {
	constexpr int S_SIZE_SLICE_WIDTH = 32;      // 1つのスライスの横幅
	constexpr int S_SIZE_SLICE_HEIGHT = 32;     // 1つのスライスの縦幅
	constexpr int M_SIZE_SLICE_WIDTH = 48;      // 1つのスライスの横幅
	constexpr int M_SIZE_SLICE_HEIGHT = 48;     // 1つのスライスの縦幅
	constexpr int L_SIZE_SLICE_WIDTH = 64;      // 1つのスライスの横幅
	constexpr int L_SIZE_SLICE_HEIGHT = 64;     // 1つのスライスの縦幅
	constexpr int AIR_ENEMY_SLICE_ROWS_MAX = 8;          // 行数
	constexpr int GROUND_ENEMY_SLICE_ROWS_MAX = 4;          // 行数
	constexpr int SLICE_COLUMNS = 1;       // 列数
}
//==============================================================
//					数学
// 
//==============================================================
//#define ABS(num) ((num) > 0 ? (num) : -(num))		//符号を外した値を返す
//#define REPEAT(num,min,max) if(num > max){num = min;} else if(num < min){num = max;}		

template<typename T>
T ABS(T num) {
	return num > 0 ? num : -num;
}

template<typename T>
void Clamp(T& num, T min, T max) {
	if (num > max) {
		num = min;
	}
	else if (num < min) {
		num = max;
	}
}

//============================================================================================================================
//			インターフェース型変数のインスタンスチェック
// 
// インターフェース型を最初に指定し、そのあとに判別したい実装クラスを指定することで
//		実装クラスがインスタンス化されているか確認できる。返り値は
//		実装クラスならそのクラスが帰る
//		それ以外ならnullptr帰る
//============================================================================================================================
template <typename TargetType, typename InterfaceType>
std::shared_ptr<TargetType> InterfaceInstanceCheak(const std::shared_ptr<InterfaceType>& instance, const std::string& typeName) {
	auto castedInstance = std::dynamic_pointer_cast<TargetType>(instance);

	return castedInstance;
}

//============================================================================================================================
//								描画
//============================================================================================================================
struct Textures {
	ComPtr<ID3D11ShaderResourceView> SRV;     //シェーダーリソースビュー
	std::unique_ptr<DirectX::SpriteBatch> Sprite;            //2Dスプライトを描写するクラス
};

													/*変数宣言*/

const Boxcollider winView = { 0,0,ScreenConfig::SRN_W,ScreenConfig::SRN_H };		//画面の端っこの座標。画面内に映っているか判定する


extern bool DebugEnable;




//namespace TextureConfigs {
//	constexpr TextureConfig TITLE          { 198, 58,  1,  1, 0, 1         };
//	constexpr TextureConfig PLAYER         { 32 , 32,  6,  2, 2, 3         };
//	constexpr TextureConfig TARGETSIGHT    { 32 , 32,  6,  2, 0, 2         };
//	constexpr TextureConfig BULLET         { 8  ,  8,  3,  1, 0, 2         };
//	constexpr TextureConfig BOM            { 8  ,  8,  3,  1, 2, 1         };
//	constexpr TextureConfig BOSS           { 32 , 32, 11, 11, 0, 11 * 11   };
//	constexpr TextureConfig BOSSALGO       { 32 , 32,  5,  1, 0, 1         };
//	constexpr TextureConfig COMMON_BOMBER  { 48 , 48,  6,  1, 0, 6         };
//	constexpr TextureConfig AIR_ENEMYBOMBER{ 48 , 48,  6,  2, 6, 6         };
//	constexpr TextureConfig MAP            { 32 , 32, 12, 10, 0, 12 * 10   };
//
//	constexpr TextureConfig TOROID         { 32, 32,  8, 1 , 0, 8        };
//	constexpr TextureConfig TORKAN         { 32, 32,  8, 2 , 8, 7        };
//	constexpr TextureConfig GIDDOSPARIO    { 32, 32,  8, 3 ,16, 8        };
//	constexpr TextureConfig ZOSHI          { 32, 32,  8, 4 ,24, 4        };
//	constexpr TextureConfig JARA           { 32, 32,  8, 5 ,32, 6        };
//	constexpr TextureConfig KAPI           { 32, 32,  8, 6 ,40, 7        };
//	constexpr TextureConfig TERRAZI        { 32, 32,  8, 7 ,48, 7        };
//	constexpr TextureConfig ZAKATO         { 32, 32,  8, 8 ,56, 1        };
//	constexpr TextureConfig BRAGZAKATO     { 32, 32,  8, 9 ,64, 1        };
//	constexpr TextureConfig GARUZAKATO     { 32, 32,  8,10 ,72, 1        };
//	constexpr TextureConfig BACURA         { 48, 48,  8, 8 ,56, 8        };
//
//	constexpr TextureConfig BARRA          { 32, 32,  4, 1 ,0,  2        };
//	constexpr TextureConfig ZOLBAK         { 32, 32,  4, 2 ,4,  4        };
//	constexpr TextureConfig LOGRAM         { 32, 32,  4, 3 ,8,  4        };
//	constexpr TextureConfig DOMOGRAM       { 32, 32,  4, 4 ,12, 4        };
//	constexpr TextureConfig DEROTA         { 32, 32,  4, 5 ,16, 4        };
//	constexpr TextureConfig GROBDA         { 32, 32,  4, 6 ,20, 4        };
//	constexpr TextureConfig BOZALOGRAM     { 32, 32,  4, 7 ,24, 1        };
//	constexpr TextureConfig SOL            { 32, 32,  4, 8 ,28, 4        };
//	constexpr TextureConfig GARUBARRA      { 64, 64,  4, 6 ,20, 1        };
//	constexpr TextureConfig GARUDEROTA     { 64, 64,  4, 7, 24, 4        };
//	constexpr TextureConfig ALGO           { 32, 32,  4, 1 , 0, 4        };
//	constexpr TextureConfig AD_CORE        { 32, 32,  4, 2 , 4, 1        };
//	constexpr TextureConfig SPFLAG         { 32, 32,  4, 1 , 2, 1        };
//
//}


#endif // GAME_DEFINITIONS_H