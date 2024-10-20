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
	constexpr int PXW = 1;		//サイズ比率(横幅)
	constexpr int PXH = 1;		//サイズ比率(高さ)
	constexpr int WIN_W = 200 * 3;	//(8*25*4)	//ウィンドウサイズ(横幅)
	constexpr int WIN_H = 260 * 3;		//(8*25*3)	//ウィンドウサイズ(縦幅)
	constexpr int SRN_W = WIN_W / PXW;			//画面サイズ(横幅)
	constexpr int SRN_H = WIN_H / PXH;			//画面サイズ(高さ)
	constexpr int CENTER_X = SRN_W / 2;		//画面の中央X座標
	constexpr int CENTER_Y = SRN_H / 2;		//画面の中央Y座標
	constexpr int WORD_W = 8;					//1文字の横幅
	constexpr int HALFWORD_W = 4;				//半角文字の横幅
	constexpr int WORD_H = 15;				//1文字の高さ
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
void Clamp(T & num, T min, T max) {
	if (num > max) {
		num = min;
	}
	else if (num < min) {
		num = max;
	}
}
//
//Vector2 LeftTopPos(Vector2 centerpos, int size) {
//	return Vector2(centerpos.x - (size / 2), centerpos.y - (size / 2));
//}
//


//==============================================================
//					シーン構造体
//			各画面で使う変数を定義する
// 
//==============================================================
class Scenestatus {
public :

	void FrameCountUpdate(int value) {
		framecount += value;
		if (framecount > 10000) framecount = 0;
	}

	void framecountReset() { framecount = 0; }
	int Getframecount() const { return framecount; }

	POINT Getcarsor()const { return carsor; }
	void movecarsor_x(LONG value, int min, int max) { carsor.x = carsorclamp(carsor.x + value,min , max); }
	void movecarsor_y(LONG value, int min, int max) { carsor.y = carsorclamp(carsor.y + value, min, max); }

	LONG carsorclamp(LONG value, int min, int max) {
		if (value < min) { return max; }
		else if (value > max) { return min; }

		return value;
	}

	bool SceneChangeSignal() { return currentsceneID != nextsceneID; }

	int Getcurrentscene()const { return currentsceneID; }
	void Setnextscene(int value) { nextsceneID = value; }
	int Getnextscene() { return nextsceneID; }
	
	
	
private:
	int framecount;
	int currentsceneID;
	int	nextsceneID;		//次の遷移先の画面ID
	POINT carsor;		//カーソルの位置

};



////
//class ParttitionMap {
//public:
//	bool drawFlag;
//	std::array<int, MapConfig::MAP_H* MapConfig::MAP_H > data;
//	int x, y;
//
//	ParttitionMap() : drawFlag(false), x(0), y(0), data({}) {}
//	~ParttitionMap() {}
//};
//
//// マップデータを管理するクラス
//class WholeMap {
//public:
//
//	int stage;
//	int currentparttition_num;
//	int x, y;
//	std::array<ParttitionMap, MapConfig::MAP_PARTITION_SUM> frontmap;
//	std::array<ParttitionMap, MapConfig::MAP_PARTITION_SUM> backmap;
//
//	Bmp* pics[MapConfig::MAP_PARTITION_SUM];
//	const wchar_t* filenames[MapConfig::MAP_PARTITION_SUM];
//
//	WholeMap() : stage(0), currentparttition_num(0), x(0), y(0) {}
//	~WholeMap() {}
//
//};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

													/*変数宣言*/

const Boxcollider winView = { 0,0,ScreenConfig::SRN_W,ScreenConfig::SRN_H };		//画面の端っこの座標。画面内に映っているか判定する

			
extern bool DebugEnable;



#endif // GAME_DEFINITIONS_H