#ifndef TESTENEMYSMANAGER_H
#define TESTENEMYSMANAGER_H

class IBulletsManager;
class IPlayer;
class IMapManager;
class GameTexture;
class DIContainer;
class DebugManager;

#include <iostream>
#include "types.h"
#include "EnemysManager.h"
#include "AirEnemyBase.h"
#include "GroundEnemyBase.h"

class TestEnemysManager : public EnemysManager{
public:
    TestEnemysManager(std::weak_ptr<IPlayer> pl,
        std::weak_ptr<IBulletsManager> bm,
        std::weak_ptr<IMapManager> mr,
        std::shared_ptr<DIContainer> con);

    int ALLEnemysInit()override;

    void CreateAirEnemy(EnemyID::EnemyName name);
    void CreateGroundEnemy(EnemyID::EnemyName name);

    int GroundEnemysUpdate(int framecount) override;
    int AirEnemysUpdate(int framecount) override;

    int GroundEnemysDraw() override;
    int AirEnemysDraw() override;






private:
    std::shared_ptr<DebugManager> debug_;

};

#endif  //TESTENEMYSMANAGER_H