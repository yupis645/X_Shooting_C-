#include "ResourceManager.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>  // for std::invalid_argument, std::out_of_range

//.cpp内でのみ使用する定義をまとめる
namespace  {
    //===============================================================================================
    // csvをint配列に変換する関数
    //===============================================================================================
    std::vector<int> readCsvData(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open " << filename << std::endl;
            return {};
        }

        std::vector<int> data;
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string cell;
            while (std::getline(ss, cell, ',')) {
                try {
                    int value = std::stoi(cell);  // 整数に変換
                    data.push_back(value);        // データを格納
                }
                catch (const std::invalid_argument& e) {
                    std::cerr << "Invalid data: " << cell << std::endl;
                    return {};
                }
                catch (const std::out_of_range& e) {
                    std::cerr << "Number out of range: " << cell << std::endl;
                    return {};
                }
            }
        }

        file.close();
        return data;
    }
    bool Init_SetUpTexture(ResourceManager& manager, TextureType type, const UseTextureDataConfig& config) {
        // InitTextureとSetUpTextureを順に呼び出す
        if (!manager.InitTexture(type, config)) {
            std::cerr << "Error: Failed to initialize texture for type: " << static_cast<int>(type) << std::endl;
            return false;
        }

        if (!manager.SetUpTexture(type)) {
            std::cerr << "Error: Failed to set up texture for type: " << static_cast<int>(type) << std::endl;
            return false;
        }

        return true;  // 両方の処理が成功した場合はtrueを返す
    }

}


//===============================================================================================
//                  コンストラクタ
// 
// 1.管理するクラスのインスタンスをスマートポインタで生成する
// 2.ゲーム中に使用するテクスチャをTextureDataManagerに保存し、
//      GameTextureManagerにて画像をゲームで使えるようにスライスする
// 3.csvファイルを読み込み、ファイルをCsvDataManagerに保存する
//===============================================================================================
ResourceManager::ResourceManager()
{

    // 1.管理するクラスのインスタンスをスマートポインタで生成する
    texturedata = std::make_shared<TextureDataManager>();
    csvdata = std::make_shared<CsvDataManager>();
    gametextures = std::make_shared<GameTextureManager>();

    // 2.テクスチャをゲーム中でも使えるようにロードする
    Init_SetUpTexture(*this,TextureType::Title, { L"res/Title.png",198, 58, 1, 1 });       //タイトルロゴ
    Init_SetUpTexture(*this,TextureType::Player, { L"res/Player_Sight.png",32, 32, 6, 2 });
    Init_SetUpTexture(*this,TextureType::Bullet, { L"res/Bullet.png",16, 16, 3, 1 });
    Init_SetUpTexture(*this,TextureType::Boss, { L"res/Boss.png",32, 32, 11, 11 });
    Init_SetUpTexture(*this,TextureType::BossSub, { L"res/Bossparts.png",32, 32, 5, 1 });
    Init_SetUpTexture(*this,TextureType::PlayerBomber, { L"res/Bomber.png",47, 47, 6, 1 });
    Init_SetUpTexture(*this,TextureType::EnemyBomber, { L"res/Bomber.png",47, 47, 6, 1 });
    Init_SetUpTexture(*this,TextureType::Map, { L"res/MapChip.png",32, 32,12, 10 });

    //3.CSVファイルを取得する
    LoadMapCsvFile("res/Map/Stage1_Front.csv", "res/Map/Stage1_Back.csv");
    //LoadMapCsvFile("res/Map/Stage2_Front.csv", "res/Map/Stage2_Back.csv");
    //LoadMapCsvFile("res/Map/Stage3_Front.csv", "res/Map/Stage3_Back.csv");
}


//===============================================================================================
//                  初期化 & セットアップ
// 
// 1.管理するクラスのインスタンスをスマートポインタで生成する
// 2.ゲーム中に使用するテクスチャをTextureDataManagerに保存し、
//      GameTextureManagerにて画像をゲームで使えるようにスライスする
// 3.csvファイルを読み込み、ファイルをCsvDataManagerに保存する
//===============================================================================================
bool ResourceManager::InitTexture(TextureType type, const UseTextureDataConfig& config) {
    return texturedata->LoadTextureData(type, config);
}

//===============================================================================================
//                  テクスチャのセットアップ
// 
// Textruetypeで指定されたキーにpngと付随情報を入れる
//===============================================================================================
bool ResourceManager::SetUpTexture(TextureType type) {
    return gametextures->TextureInport(type, texturedata->GetTextureData(type));
}

bool ResourceManager::LoadMapCsvFile(const std::string& frontcsvfile, const std::string& baclcsvfile) {

    csvdata->LoadMapData(frontcsvfile, baclcsvfile);

    return false;
}

//===============================================================================================
// csvからint配列に変換してそのまま返す
//===============================================================================================
std::vector<int> ResourceManager::ConvertCsv_Vector(const std::string& filename) {
    std::vector<int> tempData = readCsvData(filename);      //namespaceにある関数でcsvをint配列に変換する
    if (tempData.empty()) {
        return {};  // データが読み込めなかった場合、空のベクタを返す
    }

    return tempData;  // データをそのまま返す
}

//===============================================================================================
// csvからint配列に変換して逆順にして返す
//===============================================================================================
std::vector<int> ResourceManager::ConvertCsv_VectorReverse(const std::string& filename) {
    std::vector<int> tempData = readCsvData(filename);      //namespaceにある関数でcsvをint配列に変換する
    if (tempData.empty()) {
        return {};  // データが読み込めなかった場合、空のベクタを返す
    }

    return std::vector<int>(tempData.rbegin(), tempData.rend());  // データを逆順にして返す
}