#ifndef IENEMYSMANAGER_H
#define IENEMYSMANAGER_H


#include "EnemyBase.h"
#include "GroundEnemyBase.h"
#include "AirEnemyBase.h"

class IEnemysManager {
public:
    virtual ~IEnemysManager() = default;

    virtual int ALLEnemysInit() = 0;

    virtual int GroundEnemysUpdate(int framecount) = 0;
    virtual int AirEnemysUpdate(int framecount) = 0;
    
    virtual int GroundEnemysDraw() = 0;
    virtual int AirEnemysDraw() = 0;

    //インデックスで敵を取得する
    virtual GroundEnemyBase& GetGroundEnemysIndex(int index) = 0;
    virtual AirEnemyBase& GetAirEnemysIndex(int index) = 0;

    virtual int GetAirEnemysSum() = 0;
    virtual int GetGroundEnemysSum() = 0;

    virtual int searchEmptyAirEnemyIndex() = 0;
    virtual int searchEmptyGroundEnemyIndex() = 0;

    virtual std::array<GroundEnemyBase, MAX_ENEMY>& GroundEnemysArray();
    virtual std::array<AirEnemyBase, MAX_ENEMY>& AirEnemysArray();
};

#endif // IENEMYSMANAGER_H