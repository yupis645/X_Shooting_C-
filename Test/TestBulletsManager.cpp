#include "TestBulletsManager.h"

#include "DIContainer.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "GameTexture.h"
#include "IPlayer.h"
#include "DebugManager.h"

TestBulletsManager::TestBulletsManager(std::shared_ptr<DIContainer> con):
    BulletsManager(con->Create<ResourceManager>() ,con->Create<SpriteRenderer>()),
    debug_(con->Create<DebugManager>())
{
}

void TestBulletsManager::CreatePlayerShot(Vector2 pos)
{
    BulletsManager::CreatePlayerShot(pos);
}

void TestBulletsManager::CreatePlayerBom(Vector2 pos)
{
    BulletsManager::CreatePlayerBom(pos);
}

void TestBulletsManager::CreateEnemyShot(Vector2 startPos, Vector2 targetPos, float dir)
{
    BulletsManager::CreateEnemyShot(startPos, targetPos, dir);
}



void TestBulletsManager::InitPlayerShot()
{
    BulletsManager::InitPlayerShot();
}

void TestBulletsManager::InitPlayerBom()
{
    BulletsManager::InitPlayerBom();
}

void TestBulletsManager::InitEnemyShot()
{
    BulletsManager::InitEnemyShot();
}



void TestBulletsManager::UpdatePlayerShot(int frameocunt)
{
    BulletsManager::UpdatePlayerShot(frameocunt);
}

void TestBulletsManager::UpdatePlayerBom(int frameocunt)
{
    BulletsManager::UpdatePlayerBom(frameocunt);
}

void TestBulletsManager::UpdateEnemyShot(int frameocunt)
{
    BulletsManager::UpdateEnemyShot(frameocunt);
}



void TestBulletsManager::DrawPlayerShot()
{
    BulletsManager::DrawPlayerShot();
    for (int i = 0; i < BulletsManager::GetPlayershotSum(); i++) {
        debug_->DrawHitBox(*BulletsManager::GetPlayerShotIndex(i), 255, 0, 0, false);
    }
}

void TestBulletsManager::DrawPlayerBom()
{
    BulletsManager::DrawPlayerBom();
    if (BulletsManager::GetPlayerBom()->GetIsBomber()) {
        debug_->DrawHitBox(*BulletsManager::GetPlayerBom(), 255, 255, 0, false);
    }
}


void TestBulletsManager::DrawEnemyShot()
{
    BulletsManager::DrawEnemyShot();
    for (size_t i = 0; i < BulletsManager::GetEnemyshotSum(); i++) {
        if (BulletsManager::GetEnemyShotIndex(i)->GetActive()) {
            debug_->DrawHitBox(*BulletsManager::GetEnemyShotIndex(i), 255, 0, 0, false);
        }
    }
}

