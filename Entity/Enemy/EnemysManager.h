#ifndef ENEMYSMANAGER_H
#define ENEMYSMANAGER_H

#include "Game.h"
#include "IEnemysManager.h"
#include "IMapManager.h"/*
#include "IPlayer.h"
#include "IBulletManager.h"*/
#include "EnemyBase.h"
#include "GroundEnemyBase.h"
#include "AirEnemyBase.h"

class EnemysManager : public IEnemysManager
{
public:
    EnemysManager(std::shared_ptr<IPlayer> pl, std::shared_ptr<IBulletManager> bm) : player_(pl), bulletmanager_(bm) {};

    int ALLEnemysInit()override;

    int GroundEnemysUpdate(int framecount) override;
    int AirEnemysUpdate(int framecount) override;

    int GroundEnemysDraw() override;
    int AirEnemysDraw() override;

    GroundEnemyBase& GetGroundEnemysIndex(int index) override ;
    AirEnemyBase& GetAirEnemysIndex(int index) override;
    int GetAirEnemysSum() override;
    int GetGroundEnemysSum() override;

    int searchEmptyAirEnemyIndex() override;
    int searchEmptyGroundEnemyIndex() override;


    std::array<GroundEnemyBase, MAX_ENEMY>& GroundEnemysArray()override;

    std::array<AirEnemyBase, MAX_ENEMY>& AirEnemysArray()override;


    void BackMap_Enemy_table( std::shared_ptr<IPlayer> player,std::shared_ptr<IMapManager> map ,int _frame);



    bool LoadBackMapDataCsv(const std::string& csv)  { return LoadCsvReverse(csv, backmap); }
    const std::vector<int>& GetBackMapData() const  { return backmap; }
    // 逆順でデータを読み込む関数
    bool LoadCsvReverse(const std::string& filename, std::vector<int>& data) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open " << filename << std::endl;
            return false;
        }

        std::vector<int> tempData;  // 一時的なデータ格納用のベクタ

        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string cell;
            while (std::getline(ss, cell, ',')) {
                try {
                    int value = std::stoi(cell);  // 整数に変換
                    tempData.push_back(value);    // 一時的にデータを格納
                }
                catch (const std::invalid_argument& e) {
                    std::cerr << "Invalid data: " << cell << std::endl;
                    return false;
                }
                catch (const std::out_of_range& e) {
                    std::cerr << "Number out of range: " << cell << std::endl;
                    return false;
                }
            }
        }

        // 読み込んだデータを逆順に drawmap に追加
        data.insert(data.end(), tempData.rbegin(), tempData.rend());

        file.close();
        return true;
    }

protected:
    std::shared_ptr<IPlayer> player_;
    std::shared_ptr<IBulletManager> bulletmanager_;
    std::array<GroundEnemyBase,MAX_ENEMY> groundenemys;
    std::array<AirEnemyBase,MAX_ENEMY> airenemys;


};

#endif // ENEMYSMANAGER_H