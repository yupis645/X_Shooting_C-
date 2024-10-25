#ifndef GAME_DEFINITIONS_H
#define GAME_DEFINITIONS_H

#include	"conioex.h" 
#include "Geometry.h"
#include "Game.h"
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <Windows.h>
#include <array>
#include <iostream>
#include <vector>
#include <map>
#include "di.hpp"


namespace di = boost::di;

// ----------------------------------------------------------------
// アプリ共通の定義
// ----------------------------------------------------------------


#define TestMode true			//タイトルやポーズ画面に操作説明が出る & デバックモードが使用できるようになる。

// DebugOn と StageRupe は TestMode 有効時のみ作動する
#define DebugOn true			//TestModeがtrueの時のみ使用できるデバックモードのフラグ。falseにするとデバックモードに入れなくなる
#define StageRupe false			//trueなら指定したステージからループする。falseならボスを倒した地点で終了
//ここまで


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
	constexpr TextureConfig TITLE          { 198, 58,  1,  1, 0, 1         };
	constexpr TextureConfig PLAYER         { 32 , 32,  6,  2, 2, 3         };
	constexpr TextureConfig TARGETSIGHT    { 32 , 32,  6,  2, 0, 2         };
	constexpr TextureConfig BULLET         { 8  ,  8,  3,  1, 0, 2         };
	constexpr TextureConfig BOM            { 8  ,  8,  3,  1, 2, 1         };
	constexpr TextureConfig BOSS           { 32 , 32, 11, 11, 0, 11 * 11   };
	constexpr TextureConfig BOSSALGO       { 32 , 32,  5,  1, 0, 1         };
	constexpr TextureConfig COMMON_BOMBER  { 48 , 48,  6,  1, 0, 6         };
	constexpr TextureConfig AIR_ENEMYBOMBER{ 48 , 48,  6,  1, 6, 6         };
	constexpr TextureConfig MAP            { 32 , 32, 12, 10, 0, 12 * 10   };

	constexpr TextureConfig TOROID         { 32, 32,  1, 8 , 0, 8        };
	constexpr TextureConfig TORKAN         { 32, 32,  8, 2 , 8, 7        };
	constexpr TextureConfig GIDDOSPARIO    { 32, 32,  8, 3 ,16, 8        };
	constexpr TextureConfig ZOSHI          { 32, 32,  8, 4 ,24, 4        };
	constexpr TextureConfig JARA           { 32, 32,  8, 5 ,32, 6        };
	constexpr TextureConfig KAPI           { 32, 32,  8, 6 ,40, 7        };
	constexpr TextureConfig TERRAZI        { 32, 32,  8, 7 ,48, 7        };
	constexpr TextureConfig ZAKATO         { 32, 32,  8, 8 ,56, 1        };
	constexpr TextureConfig BRAGZAKATO     { 32, 32,  8, 9 ,64, 1        };
	constexpr TextureConfig GARUZAKATO     { 32, 32,  8,10 ,72, 1        };
	constexpr TextureConfig BACURA         { 48, 48,  8, 8 ,56, 8        };

	constexpr TextureConfig BARRA          { 32, 32,  1, 4 ,0,  2        };
	constexpr TextureConfig ZOLBAK         { 32, 32,  1, 8 ,4,  4        };
	constexpr TextureConfig LOGRAM         { 32, 32,  1,12 ,8,  4        };
	constexpr TextureConfig DOMOGRAM       { 32, 32,  1,16 ,12, 4        };
	constexpr TextureConfig DEROTA         { 32, 32,  1,20 ,16, 4        };
	constexpr TextureConfig GROBDA         { 32, 32,  1,24 ,20, 4        };
	constexpr TextureConfig BOZALOGRAM     { 32, 32,  1,28 ,24, 1        };
	constexpr TextureConfig SOL            { 32, 32,  1,32 ,28, 4        };
	constexpr TextureConfig GARUBARRA      { 64, 64,  1,22 ,20, 1        };
	constexpr TextureConfig GARUDEROTA     { 64, 64,  1,28 ,24, 4        };
	constexpr TextureConfig ALGO           { 48, 48,  1, 4 , 0, 4        };
	constexpr TextureConfig AD_CORE        { 64, 64,  1, 1 , 0, 1        };
	constexpr TextureConfig SPFLAG         { 32, 32,  1, 3 , 3, 1        };

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
	constexpr EnemyStatus TOROID     { 0 , 32, 32, 1,  8,   30, 2.0f, 0.04f };	// トーロイド
	constexpr EnemyStatus TORKAN     { 1 , 32, 32, 0,  7,   50, 4.0f, 0.0f  };   // タルケン
	constexpr EnemyStatus GIDDOSPARIO{ 2 , 16, 32, 0,  8,   10, 7.0f, 0.0f  };   // ギドスパリオ
	constexpr EnemyStatus ZOSHI      { 3 , 32, 32, 2,  4,   70, 3.0f, 0.0f  };   // ゾシー
	constexpr EnemyStatus JARA       { 4 , 32, 32, 0,  6,  150, 4.0f, 0.04f };   // ジアラ
	constexpr EnemyStatus KAPI       { 5 , 32, 32, 0,  7,  300, 4.0f, 0.15f };   // カピ
	constexpr EnemyStatus TERRAZI    { 6 , 32, 32, 0,  7,  700, 5.0f, 0.08f };   // テラジ
	constexpr EnemyStatus ZAKATO     { 7 , 16, 32, 3,  1,  100, 3.0f, 0.0f  };   // ザカート
	constexpr EnemyStatus BRAGZAKATO { 8 , 16, 32, 3,  1,  600, 3.0f, 0.0f  };   // ブラグザカート
	constexpr EnemyStatus GARUZAKATO { 9 , 16, 32, 0,  1, 1000, 3.0f, 0.0f  };   // ガルザカート
	constexpr EnemyStatus BACURA     { 10, 48, 48, 0,  8,    0, 2.0f, 0.0f  };   // バキュラ

	constexpr EnemyStatus BARRA      { 50, 32, 32, 0,  1,  100, 0.0f , 0.0f };   // バーラ
	constexpr EnemyStatus ZOLBAK     { 51, 32, 32, 0,  4,  200, 0.0f , 0.0f };   // ゾルバグ
	constexpr EnemyStatus LOGRAM     { 52, 32, 32, 4,  4,  300, 0.0f , 0.0f };   // ログラム
	constexpr EnemyStatus DOMOGRAM   { 53, 32, 32, 0,  4,  800, 0.75f, 0.5f };   // ドモグラム
	constexpr EnemyStatus DEROTA     { 54, 32, 32, 0,  4,  200, 0.0f , 0.0f };   // デローダ
	constexpr EnemyStatus GROBDA     { 55, 32, 32, 8,  4,  200, 0.5f , 0.5f };   // グロブダー
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

													/*変数宣言*/

const Boxcollider winView = { 0,0,ScreenConfig::SRN_W,ScreenConfig::SRN_H };		//画面の端っこの座標。画面内に映っているか判定する


extern bool DebugEnable;



#endif // GAME_DEFINITIONS_H