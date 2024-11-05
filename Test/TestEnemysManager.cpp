#include "TestEnemysManager.h"

#include "Game.h"
#include "IEnemysManager.h"
#include "IMapManager.h"
#include "IPlayer.h"
#include "IBulletsManager.h"
#include "EnemyBase.h"
#include "GroundEnemyBase.h"
#include "AirEnemyBase.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "Player.h"
#include "DebugManager.h"
#include "DIContainer.h"

TestEnemysManager::TestEnemysManager(std::weak_ptr<IPlayer> pl,
	std::weak_ptr<IBulletsManager> bm,
	std::weak_ptr<IMapManager> mr,
	std::shared_ptr<DIContainer> con):
	EnemysManager(pl, bm,mr,con->Create<ResourceManager>(),con->Create<SpriteRenderer>()),
	debug_(con->Create<DebugManager>())
{
}

int TestEnemysManager::ALLEnemysInit()
{
	return EnemysManager::ALLEnemysInit();
}

void TestEnemysManager::CreateAirEnemy(EnemyID::EnemyName name)
{
	EnemysManager::CreateAirEnemy(name);
}

void TestEnemysManager::CreateGroundEnemy(EnemyID::EnemyName name)
{
	EnemysManager::CreateGroundEnemy(name);
}

int TestEnemysManager::GroundEnemysUpdate(int framecount)
{
	return EnemysManager::GroundEnemysUpdate(framecount);
	
}

int TestEnemysManager::AirEnemysUpdate(int framecount)
{
	return EnemysManager::AirEnemysUpdate(framecount);
	
}

int TestEnemysManager::GroundEnemysDraw()
{
	return EnemysManager::GroundEnemysDraw();
	
}

int TestEnemysManager::AirEnemysDraw()
{
	EnemysManager::AirEnemysDraw();
	for (size_t i = 0; i < EnemysManager::GetAirEnemys().size(); i++) {
		if (EnemysManager::GetAirEnemys()[i]->GetActive()) {
			debug_->DrawHitBox(*EnemysManager::GetAirEnemys()[i], 255, 0, 0, false);
		}
	}

	return 0;
}

