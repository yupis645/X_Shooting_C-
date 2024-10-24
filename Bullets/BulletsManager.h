#ifndef BULLETSMANAGER_H
#define BULLETSMANAGER_H

class Vector2;
class IPlayer;
class BulletBase;

class SpriteRenderer;
class ResourceManager;
class GameTexture;

#include "IBulletsManager.h"
#include "PlayerBom.h"
#include "PlayerShot.h"
#include "EnemyShot.h"
#include <iostream>


//===================================================================================
//                  ‰æ–Êã‚Ì”­Ë•¨‚ÌŠÇ—
//===================================================================================
class BulletsManager : public IBulletsManager  {
public:
    BulletsManager(std::shared_ptr<ResourceManager> rm, std::shared_ptr<SpriteRenderer> sr, std::shared_ptr<IPlayer> lpa);


    // ’e‚Ì¶¬AŠÇ—ŠÖ”‚È‚Ç‚ğ’Ç‰Á
    void CreatePlayerShot(Vector2 pos)override;
    void CreatePlayerBom(Vector2 pos )override;
    void CreateEnemyShot(Vector2 startPos, Vector2 targetPos, float dir)override;



    int Update(int framecount);
    int Draw();

    void InitPlayerShot() override;
    void InitPlayerBom() override;
    void InitEnemyShot()override ;

    void UpdatePlayerShot(int frameocunt) override;
    void UpdatePlayerBom(int frameocunt)override;
    void UpdateEnemyShot(int frameocunt)override;

    void DrawPlayerShot()override;
    void DrawPlayerBom()override;
    void DrawEnemyShot()override;

    int GetEnemyshotSum() override;
    int GetPlayershotSum() override;


    std::shared_ptr<EnemyShot> GetEnemyShotIndex(int i) override;
    std::shared_ptr<PlayerShot> GetPlayerShotIndex(int i) override;
    std::shared_ptr<PlayerBom> GetPlayerBom() override;


    ~BulletsManager() = default;


private :
    std::array<std::shared_ptr<PlayerShot>, PlayerConfig::MAX_SHOT> playershots;
    std::shared_ptr<PlayerBom> playerboms;  // Player ƒNƒ‰ƒX‚Ö‚ÌˆË‘¶
    std::array<std::shared_ptr<EnemyShot>, EnemyShotConfig::MAX_SHOT> enemyshots;
  
    std::shared_ptr<SpriteRenderer> render_;

    std::shared_ptr<GameTexture> shottex;
    std::shared_ptr<GameTexture> bomtex;

};

#endif //BULLETSMANAGER_H