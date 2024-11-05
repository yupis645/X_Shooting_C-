//----------------------------------------------------------------------------------------------------------------
//													衝突判定
// 
// 当たり判定があるオブジェクト同士を比べて衝突判定を行う
// 1.プレイヤーと敵の弾
// 2.プレイヤーと空中敵
// 3.空中敵とプレイヤーの弾
//----------------------------------------------------------------------------------------------------------------
#include "CollisionManager.h"

#include "PlayerBom.h"
#include "PlayerShot.h"
#include "EnemyShot.h"
#include "AirEnemyBase.h"
#include "EnemyShot.h"
#include "Player.h"
#include "BulletsManager.h"
#include "EnemysManager.h"
#include <memory>
#include <vector>


CollisionManager::CollisionManager()
{
	
}


bool CollisionManager::CollisionUpdate(std::weak_ptr<IBulletsManager> bullets_, std::weak_ptr<IEnemysManager> enemys_, std::weak_ptr<IPlayer> player_)
{
	auto useplayer = player_.lock();
	auto useenemys = enemys_.lock();
	auto usebullets = bullets_.lock();


	// 1.プレイヤーと敵の弾
	for (int i = 0; i < usebullets->GetEnemyshotSum(); i++) {
		if (usebullets->GetEnemyShotIndex(i)->GetActive() && !useplayer->Getshootdown()) {
			if (useplayer->GetHitbox().BoxCollision(usebullets->GetEnemyShotIndex(i)->GetHitbox()))
			{
				useplayer->HitCollision(true);
				break;
			}
		}
	}

	// 2.プレイヤーと空中敵
	for (int i = 0; i < useenemys->GetAirEnemysSum(); i++) {
		if (useenemys->GetAirEnemysIndex(i)->GetActive() && !useenemys->GetAirEnemysIndex(i)->Getshootdown()) {
			if (useenemys->GetAirEnemysIndex(i)->GetHitbox().BoxCollision(useplayer->GetHitbox()))
			{
				useplayer->HitCollision(true);
				useenemys->GetAirEnemysIndex(i)->HitCollision(true);
				break;
			}

			// 3.空中敵とプレイヤーの弾
			for (int j = 0; j < usebullets->GetPlayershotSum(); j++) {
				if (usebullets->GetPlayerShotIndex(j)->GetActive()) {
					if (useenemys->GetAirEnemysIndex(i)->GetHitbox().BoxCollision(usebullets->GetPlayerShotIndex(j)->GetHitbox()))
					{
						useenemys->GetAirEnemysIndex(i)->HitCollision(true);
						break;
					}
				}
			}
		}
	}


	return false;
}

