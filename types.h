#ifndef TYPES_H
#define TYPES_H

#include "common.h"
//-----------------------------------------------------------------------------------------------------
//				複数の変数で構成されたデータ構造を宣言するファイル
// 
// 
//-----------------------------------------------------------------------------------------------------

//===========================================================
//         元のpngデータとスライスするための設定
// 
// widthとheightでスライスする四角を作る
// rowは横、coluwnは縦に何枚スライスするか決める
// スライスする枚数はrow * coluwnで算出できる
//===========================================================
struct UseTextureDataConfig
{
    const wchar_t* texturepath;     //pngのデータパス
    int width;                      //１枚のスライスに対する横の長さ
    int height;                     //１枚のスライスに対する縦の長さ
    int row;                        // 横方向に切り取る数
    int column;                     //縦方向に切り取る数
};

//===========================================================
// 画像を管理するmapで識別するためのキーに使う定数
//===========================================================
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
//===========================================================
// 敵を番号を管理する
//===========================================================
namespace EnemyID {
    enum EnemyName {
        Toroid = 0,
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

        Barra = 50,
        Zolbak,
        Logram,
        Domogram,
        Derota,
        Grobda,
        Bozalogram,
        Sol,
        Garubarra,
        Garuderota,
        Algo,
        Ad_core,
        Spflag,
        GroundEnemyEnd,


        toroid_type2 = 100 + Toroid,
        zoshi_type2 = 100 + Zoshi,
        zoshi_type3 = 200 + Zoshi,
        Jara_type2  = 100 + Jara,
        zakato_type2 = 100 + Zakato,
        zakato_type3 = 200 + Zakato,
        zakato_type4 = 300 + Zakato,
        bragzakato_type2 = 100 + Bragzakato,
        bragzakato_type3 = 200 + Bragzakato,
        bragzakato_type4 = 300 + Bragzakato,

        Logram_type2 = 100 + Logram,
        Logram_type3 = 200 + Logram,
        Logram_type4 = 300 + Logram,
        Logram_type5 = 400 + Logram,
        Garubarra_type2 = 100 + Garubarra,
        Garubarra_type3 = 200 + Garubarra,
        Garubarra_type4 = 300 + Garubarra,
        Garubarra_type5 = 400 + Garubarra,
        Garubarra_type6 = 500 + Garubarra,
        Garubarra_type7 = 600 + Garubarra,
        Garubarra_type8 = 700 + Garubarra,
        Garubarra_type9 = 800 + Garubarra,


    };
};

//===========================================================
// マップチップの情報の配列と進行度を管理する
//===========================================================
struct MapStatus {
    std::array<int,MapConfig::MAP_H * MapConfig::MAP_W> data;
    int y;
};



#endif //TYPES_H