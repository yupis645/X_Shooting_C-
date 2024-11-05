#ifndef TESTBULLETSMANAGER_H
#define TESTBULLETSMANAGER_H

class Vector2;
class GameTexture;
class DebugManager;
class DIContainer;

#include "BulletsManager.h"
#include <iostream>

class TestBulletsManager :public BulletsManager{
public :
    TestBulletsManager(std::shared_ptr<DIContainer> con);


    // íeÇÃê∂ê¨ÅAä«óùä÷êîÇ»Ç«Çí«â¡
    void CreatePlayerShot(Vector2 pos)override;
    void CreatePlayerBom(Vector2 pos)override;
    void CreateEnemyShot(Vector2 startPos, Vector2 targetPos, float dir)override;

    void InitPlayerShot() override;
    void InitPlayerBom() override;
    void InitEnemyShot()override;

    void UpdatePlayerShot(int frameocunt) override;
    void UpdatePlayerBom(int frameocunt)override;
    void UpdateEnemyShot(int frameocunt)override;

    void DrawPlayerShot()override;
    void DrawPlayerBom()override;
    void DrawEnemyShot()override;


    ~TestBulletsManager() = default;

private:
    std::shared_ptr<DebugManager> debug_;
};

#endif		//TESTBULLETSMANAGER_H

