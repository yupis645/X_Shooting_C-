#include "ResourceManager.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>  
#include <fstream>
#include "GameTexture.h"

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

    //===============================================================================================
    //                  初期化 & セットアップ
    // 
    // 1.管理するクラスのインスタンスをスマートポインタで生成する
    // 2.ゲーム中に使用するテクスチャをTextureDataManagerに保存し、
    //      GameTextureManagerにて画像をゲームで使えるようにスライスする
    // 3.csvファイルを読み込み、ファイルをCsvDataManagerに保存する
    //===============================================================================================
    bool Init_SetUpTexture(ResourceManager& manager, TextureType type, const std::wstring& path, const TextureConfig& config) {
        // InitTextureとSetUpTextureを順に呼び出す
        if (!manager.InitTextureLoad(type, path)) {
            std::cerr << "Error: Failed to initialize texture for type: " << static_cast<int>(type) << std::endl;
            return false;
        }

        if (!manager.SliceTexturebytype(type,config)) {
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
  Init_SetUpTexture(*this,TextureType::Title, L"res/Title.png", TextureConfigs::TITLE);       //タイトルロゴ
  Init_SetUpTexture(*this,TextureType::Player,  L"res/Player_Sight.png",TextureConfigs::PLAYER);
  Init_SetUpTexture(*this,TextureType::Bullet,  L"res/Bullet.png",TextureConfigs::BULLET);
  Init_SetUpTexture(*this,TextureType::Boss,  L"res/Boss.png",TextureConfigs::BOSS);
  Init_SetUpTexture(*this,TextureType::BossSub,  L"res/Bossparts.png",TextureConfigs::BOSSSUB);
  Init_SetUpTexture(*this,TextureType::PlayerBomber,  L"res/Bomber.png",TextureConfigs::PLAYERBOMBER);
  Init_SetUpTexture(*this,TextureType::EnemyBomber,  L"res/Bomber.png",TextureConfigs::ENEMYBOMBER);
  Init_SetUpTexture(*this,TextureType::Map,  L"res/MapChip.png",TextureConfigs::MAP);

    //3.CSVファイルを取得する
    LoadMapCsvFile("res/Map/Stage1_Front.csv", "res/Map/Stage1_Back.csv");
    //LoadMapCsvFile("res/Map/Stage2_Front.csv", "res/Map/Stage2_Back.csv");
    //LoadMapCsvFile("res/Map/Stage3_Front.csv", "res/Map/Stage3_Back.csv");
}

//////////////////////////////////////////////// /* Texture関連 */ /////////////////////////////////////////////////////////////////////

//===============================================================================================
//                  テクスチャの読み込み
// 
// テクスチャファイルや画像のサイズ、スライスする枚数などのデータを保存する
//===============================================================================================
bool ResourceManager::InitTextureLoad(TextureType type, const std::wstring& path) {
    // ファイルストリームを開いて存在チェック
    std::wifstream file(path);
    if (!file) {
        std::wcerr << L"Error: Texture file not found at path: " << path << std::endl;
        return false;
    }

    texturedata->SetTexPath(type, path);

    return true;
}



//===============================================================================================
//                  テクスチャのセットアップ
// 
// Textruetypeで指定されたキーにpngと付随情報を入れる
//===============================================================================================
bool ResourceManager::SliceTexturebytype(TextureType type, TextureConfig config)
{
    
    gametextures->CreateGameTexture(type,texturedata->GetTexturePath(type),config);
    return false;
}

//===============================================================================================
//                  テクスチャの取得
// 
// インスタンス化されているテクスチャを取り出す
//===============================================================================================
inline std::shared_ptr<GameTexture> ResourceManager::GetTexture(TextureType type) {
    auto tex = gametextures->GetTexture(type);
    // テクスチャが有効かどうかを確認する
    if (tex == nullptr) {
        std::cerr << "Failed to load map chip texture: tex is null." << std::endl;
        return nullptr;  // 失敗を示す
    }

    // 正常に読み込まれた場合
    return tex;        // 成功を示す
}

//////////////////////////////////////////////// /* Csv関連 */ /////////////////////////////////////////////////////////////////////

//===============================================================================================
// csvをファイルから読みだす
//===============================================================================================
bool ResourceManager::LoadMapCsvFile(const std::string& frontcsvfile, const std::string& baclcsvfile) {

    csvdata->LoadMapData(frontcsvfile, baclcsvfile);

    return false;
}
//===============================================================================================
// csvファイルをint配列に変換する
//===============================================================================================
inline std::vector<int> ResourceManager::ConvertDrawMapCsv_Vector() {
    return ConvertCsv_VectorReverse(csvdata->GetDrawmapcsv());
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