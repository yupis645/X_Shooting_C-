
//---------------------------------------------------------------------------------------------------------------------------
//                                  弾を管理するクラス
// 
// 敵の弾、プレイヤーの弾、プレイヤーの地上敵に対する爆弾　これら3つの弾を管理する。
// 生成、初期化、更新、描画　の関数がある。
//---------------------------------------------------------------------------------------------------------------------------

#include "BulletsManager.h"

#include "SpriteRenderer.h"
#include "ResourceManager.h"

// 汎用関数
namespace Utils {

    //==========================================================================================
    //                          インデックス検索関数
    //==========================================================================================
    template<typename BulletType, std::size_t N>
    size_t FindActiveIndex(const std::array<std::shared_ptr<BulletType>, N>& bullet, bool isActive) {
        for (std::size_t i = 0; i < bullet.size(); ++i) {           //引数1から配列の要素数を引き出す
            if (bullet[i] && bullet[i]->GetActive() == isActive) {  //弾のactive変数が引数2と一致しているか確認する
                return i;                         //もし見つかったらそのindex番号を返す
            }
        }
        return -1;                                                  //見つからなかったら-1を返す
    }
}

//==========================================================================================
//                          コンストラクタ
//
// 描画クラスとリソースクラスを受けとり、描画クラスはメンバ変数に代入し、リソースクラスからは画像を取得する
// 各種弾の仮生成を行う。
//==========================================================================================
BulletsManager::BulletsManager(std::shared_ptr<ResourceManager> rm, std::shared_ptr<SpriteRenderer> sr) :
    shottex(rm->GetTexture(TextureType::Bullet)),   //弾の画像を取得
    bomtex(rm->GetTexture(TextureType::Bom)),       //ボムの画像を取得
    render_(sr)                                     //描画クラスのスマートポインタの取得
{
    //弾の仮生成
    for (auto& shot : playershots) {        
        shot = std::make_shared<PlayerShot>();      //playershotの仮生成
    }
    for (auto& e_shot : enemyshots) {
        e_shot = std::make_shared<EnemyShot>();     //enemyshotの仮生成
    }
    playerboms = std::make_shared<PlayerBom>();     //playerbomの仮生成

}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                 外部クラスに渡す３種類の処理をまとめた関数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//==========================================================================================
//                         1フレームごとのデータの更新
//==========================================================================================
int BulletsManager::Update(int framecount) {
    UpdatePlayerShot(framecount);
    UpdatePlayerBom(framecount);
    UpdateEnemyShot(framecount);

    return 0;

}

//==========================================================================================
//                              描画
//==========================================================================================
int BulletsManager::Draw() {

    DrawPlayerShot();
    DrawPlayerBom();
    DrawEnemyShot();

    return 0;

}
                 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      プレイヤーの弾
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//==========================================================================================
//                              生成
//==========================================================================================
void BulletsManager::CreatePlayerShot(Vector2 pos) {            // 引数1:playerの座標
    int index = Utils::FindActiveIndex(playershots, false);     //発射フラグが立っていないショット番号を探す
    if (index == -1) return;                                    //返り値が-1なら全てフラグが立っているので生成しない
    playershots[index]->Create(pos);                            //indexが見つかったらそのindexで弾を生成する
};

//==========================================================================================
//                              初期化
//==========================================================================================
void BulletsManager::InitPlayerShot() {
    for (size_t i = 0; i < playershots.size(); i++) {
        playershots[i]->Init();
    }
}


//==========================================================================================
//                               更新
// 引数:フレームカウント
//==========================================================================================
void BulletsManager::UpdatePlayerShot(int frameocunt) {
    for (size_t i = 0; i < playershots.size(); i++) {
        if (playershots[i]->GetActive()) {					//ショットフラグがONなら
            playershots[i]->Update(frameocunt);
        }
    }
}



//==========================================================================================
//                              描画
// 
// playerの弾の見た目は双発なので画像を二つ使う。
// それぞれ中央のx座標からSHOT_SPEED_HOLLOW離れた位置に表示する
//==========================================================================================
void BulletsManager::DrawPlayerShot() {
    for (size_t i = 0; i < playershots.size(); i++) {
        if (playershots[i]->GetActive()) {					//ショットフラグがONなら
            int left_x = static_cast<int>(playershots[i]->GetDrawPos().x - PlayerConfig::SHOT_SPEED_HOLLOW);
            int right_x = static_cast<int>(playershots[i]->GetDrawPos().x + PlayerConfig::SHOT_SPEED_HOLLOW);
            int y = static_cast<int>(playershots[i]->GetDrawPos().y);

            render_->DrawFromCenterPos(shottex, 0, left_x, y, PlayerConfig::SHOT_PIC_SIZE);
            render_->DrawFromCenterPos(shottex, 0, right_x, y, PlayerConfig::SHOT_PIC_SIZE);
        }
    }
}


//==========================================================================================
//                              サイズgetter
//==========================================================================================
int BulletsManager::GetPlayershotSum()
{
    return playershots.size();
}


//==========================================================================================
//                              index指定getter
// 引数:取得したいindex番号
//==========================================================================================
std::shared_ptr<PlayerShot> BulletsManager::GetPlayerShotIndex(int i)
{
    return playershots[i];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                         プレイヤーのボム
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//==========================================================================================
//                         生成
// 引数1:playerの座標
//==========================================================================================
void BulletsManager::CreatePlayerBom(Vector2 pos) {
    if (!playerboms->GetActive()) {
        playerboms->Create(pos);
        return;

    }

}

//==========================================================================================
//                              初期化
//==========================================================================================
void BulletsManager::InitPlayerBom() {
    playerboms->Init();
}


//==========================================================================================
//                              更新
// 引数:フレームカウント
//==========================================================================================
void BulletsManager::UpdatePlayerBom(int frameocunt) {
    if (playerboms->GetActive()) {
        playerboms->Update(frameocunt, PlayerConfig::BOM_SPEED);
    }
}


//==========================================================================================
//                              描画
// 
// Activeがtrue かつ 爆発前はボムの画像を描画する
// 爆発している間はActiveがtrueでも描画しない
//==========================================================================================
void BulletsManager::DrawPlayerBom() {
    if (playerboms->GetActive() && !playerboms->GetIsBomber()) {
        render_->DrawFromCenterPos(bomtex, 0, playerboms->GetDrawPos(), PlayerConfig::BON_PIC_SIZE);
    }
}

//==========================================================================================
//                              bomのゲッター
//==========================================================================================
std::shared_ptr<PlayerBom> BulletsManager::GetPlayerBom()
{
    return playerboms;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                         敵の弾
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//==========================================================================================
//                         生成
// 引数1:弾を発射する敵の座標 , 引数2:playerの座標 , 引数3:発射角度の指定(必要あれば)
//==========================================================================================
void BulletsManager::CreateEnemyShot(Vector2 startPos, Vector2 targetPos, float radianplus = 0) {
    int index = Utils::FindActiveIndex(enemyshots, false);
    if (index == -1) return;
    enemyshots[index]->Create(startPos, targetPos, radianplus);

};

//==========================================================================================
//                              初期化
//==========================================================================================
void BulletsManager::InitEnemyShot() {
    for (size_t i = 0; i < enemyshots.size(); i++) {
        enemyshots[i]->Init();
    }
}


//==========================================================================================
//                              更新
// 引数1:フレームカウント
//==========================================================================================
void BulletsManager::UpdateEnemyShot(int frameocunt) {
    for (size_t i = 0; i < enemyshots.size(); i++) {
        if (enemyshots[i]->GetActive()) {					//ショットフラグがONなら
            enemyshots[i]->Update(frameocunt);
        }
    }
}

//==========================================================================================
//                              描画
//==========================================================================================
void BulletsManager::DrawEnemyShot() {
    for (size_t i = 0; i < enemyshots.size(); i++) {
        if (enemyshots[i]->GetActive()) {					//ショットフラグがONなら描画
            render_->DrawFromCenterPos(shottex, 0, enemyshots[i]->GetDrawPos(),EnemyShotConfig::PIC_SIZE);
        }
    }
}


//==========================================================================================
//                              サイズgetter
//==========================================================================================
int BulletsManager::GetEnemyshotSum()
{
    return enemyshots.size();
}


//==========================================================================================
//                              index指定getter
// 引数:取得したいindex番号
//==========================================================================================
std::shared_ptr<EnemyShot> BulletsManager::GetEnemyShotIndex(int i)
{
    return enemyshots[i];

}
