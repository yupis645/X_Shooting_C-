#ifndef BULLETSMANAGER_H
#define BULLETSMANAGER_H

class Vector2;

class SpriteRenderer;
class ResourceManager;
class GameTexture;

#include "IBulletsManager.h"
#include "PlayerBom.h"
#include "PlayerShot.h"
#include "EnemyShot.h"


//===================================================================================
//                  画面上の発射物の管理
//===================================================================================
class BulletsManager : public IBulletsManager  {
public:
    //コンストラクタ
    BulletsManager(std::shared_ptr<ResourceManager> rm, std::shared_ptr<SpriteRenderer> sr);

    // プレイヤーの弾
    void CreatePlayerShot(Vector2 pos)override;     
    void InitPlayerShot() override;

    //プレイヤーのボム
    void CreatePlayerBom(Vector2 pos )override;
    void InitPlayerBom() override;

    //敵の弾
    void CreateEnemyShot(Vector2 startPos, Vector2 targetPos, float dir)override;
    void InitEnemyShot()override;

    //３種類の共通処理をまとめた関数
    int Update(int framecount);
    int Draw();

    ~BulletsManager() = default;        //デストラクタ

public:     //ゲッター/セッター
    int GetEnemyshotSum() override;
    int GetPlayershotSum() override;

    std::shared_ptr<EnemyShot> GetEnemyShotIndex(int i) override;
    std::shared_ptr<PlayerShot> GetPlayerShotIndex(int i) override;
    std::shared_ptr<PlayerBom> GetPlayerBom() override;


protected:    //内部で使う個別の更新と描画関数(テストクラスでも使えるようにprotected)
    void DrawPlayerShot()override;
    void UpdatePlayerShot(int frameocunt) override;

    void DrawPlayerBom()override;
    void UpdatePlayerBom(int frameocunt)override;

    void UpdateEnemyShot(int frameocunt)override;
    void DrawEnemyShot()override;

private :
    std::array<std::shared_ptr<PlayerShot>, PlayerConfig::MAX_SHOT> playershots;
    std::shared_ptr<PlayerBom> playerboms;  // Player クラスへの依存
    std::array<std::shared_ptr<EnemyShot>, EnemyShotConfig::MAX_SHOT> enemyshots;
  
    std::shared_ptr<SpriteRenderer> render_;

    std::shared_ptr<GameTexture> shottex;
    std::shared_ptr<GameTexture> bomtex;

};

#endif //BULLETSMANAGER_H