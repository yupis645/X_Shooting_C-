#ifndef ENEMYSMANAGER_H
#define ENEMYSMANAGER_H

class IBulletsManager;
class IPlayer;
class IMapManager;
class ResourceManager;
class GameTexture;
class SpriteRenderer;

#include <iostream>
#include "types.h"
#include "IEnemysManager.h"
#include "AirEnemyBase.h"
#include "GroundEnemyBase.h"

class EnemysManager : public IEnemysManager
{
public:
    EnemysManager(std::weak_ptr<IPlayer> pl,
        std::weak_ptr<IBulletsManager> bm,
        std::weak_ptr<IMapManager> mr,
        std::shared_ptr<ResourceManager> rm,
        std::shared_ptr<SpriteRenderer> sm);

    int ALLEnemysInit()override;

    void CreateAirEnemy(EnemyID::EnemyName name);
    void CreateGroundEnemy(EnemyID::EnemyName name);

    int GroundEnemysUpdate(int framecount) override;
    int AirEnemysUpdate(int framecount) override;

    int GroundEnemysDraw() override;
    int AirEnemysDraw() override;

    std::shared_ptr<GroundEnemyBase> GetGroundEnemysIndex(int index) override ;
    std::shared_ptr<AirEnemyBase> GetAirEnemysIndex(int index) override;
    int GetAirEnemysSum() override;
    int GetGroundEnemysSum() override;

    int searchEmptyAirEnemyIndex() override;
    int searchEmptyGroundEnemyIndex() override;


    std::array<std::shared_ptr<GroundEnemyBase>, GroundEnemyConfig::MAX_ENEMY>& GroundEnemysArray()override;

    std::array<std::shared_ptr<AirEnemyBase>, AirEnemyConfig::MAX_ENEMY>& AirEnemysArray()override;



    void SwapMapdata(std::vector<int>);       //int配列のmapdataを更新する

    void BackMap_Enemy_table( std::shared_ptr<IPlayer> player,std::shared_ptr<IMapManager> map ,int _frame);

    ~EnemysManager() = default;

    //bool LoadBackMapDataCsv(const std::string& csv)  { return LoadCsvReverse(csv, backmap); }
    //const std::vector<int>& GetBackMapData() const  { return backmap; }
    //// 逆順でデータを読み込む関数
    //bool LoadCsvReverse(const std::string& filename, std::vector<int>& data) {
    //    std::ifstream file(filename);
    //    if (!file.is_open()) {
    //        std::cerr << "Failed to open " << filename << std::endl;
    //        return false;
    //    }
    //    std::vector<int> tempData;  // 一時的なデータ格納用のベクタ
    //    std::string line;
    //    while (std::getline(file, line)) {
    //        std::stringstream ss(line);
    //        std::string cell;
    //        while (std::getline(ss, cell, ',')) {
    //            try {
    //                int value = std::stoi(cell);  // 整数に変換
    //                tempData.push_back(value);    // 一時的にデータを格納
    //            }
    //            catch (const std::invalid_argument& e) {
    //                std::cerr << "Invalid data: " << cell << std::endl;
    //                return false;
    //            }
    //            catch (const std::out_of_range& e) {
    //                std::cerr << "Number out of range: " << cell << std::endl;
    //                return false;
    //            }
    //        }
    //    }
    //    // 読み込んだデータを逆順に drawmap に追加
    //    data.insert(data.end(), tempData.rbegin(), tempData.rend());
    //    file.close();
    //    return true;
    //}

protected:
    std::weak_ptr<IPlayer> player_;
    std::weak_ptr<IBulletsManager> bullets_;
    std::weak_ptr<IMapManager> mapdata_;

    std::shared_ptr<SpriteRenderer> render_;

    std::map<EnemyID::EnemyName, std::shared_ptr<GameTexture>> textures_;      // TextureType をキーにして GameTexture を管理するマップ

    std::array<std::shared_ptr<GroundEnemyBase>,GroundEnemyConfig::MAX_ENEMY> groundenemys;
    std::array<std::shared_ptr<AirEnemyBase>,AirEnemyConfig::MAX_ENEMY> airenemys;

    std::vector<int> enemyplacement;           //マップチップの配置を管理するint配列


    void SetEnemyTexture(std::shared_ptr<ResourceManager> rm);
};

#endif // ENEMYSMANAGER_H