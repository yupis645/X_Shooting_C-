#ifndef IENEMYSMANAGER_H
#define IENEMYSMANAGER_H

class EnemyBase;
class GroundEnemyBase;
class AirEnemyBase;

class IEnemysManager {
public:
    virtual ~IEnemysManager() = default;
    virtual int ALLEnemysInit() = 0;

    virtual void CreateAirEnemy(EnemyID::EnemyName name) = 0;
    virtual void CreateGroundEnemy(EnemyID::EnemyName name) = 0;

    virtual int GroundEnemysUpdate(int framecount) = 0;
    virtual int AirEnemysUpdate(int framecount) = 0;
    
    virtual int GroundEnemysDraw() = 0;
    virtual int AirEnemysDraw() = 0;

    //インデックスで敵を取得する
    virtual std::shared_ptr<GroundEnemyBase>  GetGroundEnemysIndex(int index) = 0;
    virtual std::shared_ptr<AirEnemyBase> GetAirEnemysIndex(int index) = 0;

    virtual int GetAirEnemysSum() = 0;
    virtual int GetGroundEnemysSum() = 0;

    virtual int searchEmptyAirEnemyIndex() = 0;
    virtual int searchEmptyGroundEnemyIndex() = 0;

    virtual std::array<std::shared_ptr<GroundEnemyBase>, GroundEnemyConfig::MAX_ENEMY>& GroundEnemysArray() =0;
    virtual std::array<std::shared_ptr<AirEnemyBase>, AirEnemyConfig::MAX_ENEMY>& AirEnemysArray() = 0;

    
};

#endif // IENEMYSMANAGER_H