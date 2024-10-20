#include "ResourceManager.h"


//===========================================================================
//					画像データ
//===========================================================================
PNGDATA PngData = {
	 L"res/STG_Title.png",
	L"res/EDGE STG自機.png",
	L"res/STG 弾.png",
	 L"res/STG_A_enemy.png",
	 L"res/STG_G_enemy.png"  ,
	 L"res/BOSS.png",
	 L"res/BOSS_PATS.png",
	L"res/bomber.png",
	L"res/Map/MapChip.png",
};


// マップデータを定数として定義
const std::array<CSVMapData, 3> MapCsvData = { {
		// ステージ1
		{
			{ "res/Map/ARIA0.csv", "res/Map/stage1/1-1Front.csv", "res/Map/stage1/1-2Front.csv", "res/Map/stage1/1-3Front.csv", "res/Map/stage1/1-4Front.csv" },
			{ "res/Map/ARIA0.csv", "res/Map/stage1/1-1Back.csv",  "res/Map/stage1/1-2Back.csv",  "res/Map/stage1/1-3Back.csv",  "res/Map/stage1/1-4Back.csv" }
		},
	// ステージ2
	{
		{ "res/Map/ARIA0.csv", "res/Map/stage2/2-1_Front.csv", "res/Map/stage2/2-2_Front.csv", "res/Map/stage2/2-3_Front.csv", "res/Map/stage2/2-4_Front.csv" },
		{ "res/Map/ARIA0.csv", "res/Map/stage2/2-1_Back.csv",  "res/Map/stage2/2-2_Back.csv",  "res/Map/stage2/2-3_Back.csv",  "res/Map/stage2/2-4_Back.csv" }
	},
	// ステージ3
	{
		{ "res/Map/ARIA0.csv", "res/Map/stage3/3-1_Front.csv", "res/Map/stage3/3-2_Front.csv", "res/Map/stage3/3-3_Front.csv", "res/Map/stage3/3-4_Front.csv" },
		{ "res/Map/ARIA0.csv", "res/Map/stage3/3-1_Back.csv",  "res/Map/stage3/3-2_Back.csv",  "res/Map/stage3/3-3_Back.csv",  "res/Map/stage3/3-4_Back.csv" }
	}
} };
