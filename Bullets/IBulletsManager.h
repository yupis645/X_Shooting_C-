#ifndef IBULLETMANAGER_H
#define IBULLETMANAGER_H

class BulletBase;
class Vector2;
class PlayerShot;
class PlayerBom;
class EnemyShot;

#include <iostream>

class IBulletsManager {
public:
    ~IBulletsManager() = default;

    // íeÇÃê∂ê¨ÅAä«óùä÷êîÇ»Ç«Çí«â¡
    virtual void CreatePlayerShot(Vector2 pos) = 0;
    virtual void CreatePlayerBom(Vector2 pos) = 0;
    virtual void CreateEnemyShot(Vector2 startPos, Vector2 targetPos, float radianplus = 0) = 0;

    virtual int Update(int framecount) = 0;
    virtual int Draw() = 0;

    virtual void InitPlayerShot() = 0;
    virtual void InitPlayerBom() = 0;
    virtual void InitEnemyShot() = 0;

    virtual void UpdatePlayerShot(int frameocunt) = 0;
    virtual void UpdatePlayerBom(int frameocunt) = 0;
    virtual void UpdateEnemyShot(int frameocunt) = 0;


    virtual void DrawPlayerShot() = 0;
    virtual void DrawPlayerBom() = 0;
    virtual void DrawEnemyShot() = 0;

    virtual int GetEnemyshotSum() = 0;
    virtual int GetPlayershotSum() = 0;

    virtual std::shared_ptr<EnemyShot> GetEnemyShotIndex(int i) = 0;
    virtual std::shared_ptr<PlayerShot> GetPlayerShotIndex(int i) = 0;
    virtual std::shared_ptr<PlayerBom> GetPlayerBom() = 0;



};

#endif //IBULLETMANAGER_H