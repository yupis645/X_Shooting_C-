#include "ResourceManager.h"


#include "GameApplication.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>  
#include <fstream>
#include "GameTexture.h"
#include "pch.h"
using namespace DirectX;

//.cpp内でのみ使用する定義をまとめる
namespace {
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
    //                  ゲーム中に使うテクスチャのパスを取得する
    //===============================================================================================
    bool AllTextureLoad(ResourceManager& rm) {
        if (rm.LoadTextureBase(TextureBaseName::Title, L"res/Title.png") ||
            rm.LoadTextureBase(TextureBaseName::Player_Sight, L"res/Player_Sight.png") ||
            rm.LoadTextureBase(TextureBaseName::Bullet, L"res/Bullet.png") ||
            rm.LoadTextureBase(TextureBaseName::Boss, L"res/Boss.png") ||
            rm.LoadTextureBase(TextureBaseName::Algo_Core, L"res/Algo_Core.png") ||
            rm.LoadTextureBase(TextureBaseName::Bomber, L"res/Bomber.png") ||
            rm.LoadTextureBase(TextureBaseName::MapChip, L"res/MapChip.png") ||
            rm.LoadTextureBase(TextureBaseName::AirEnemy, L"res/AirEnemy.png") ||
            rm.LoadTextureBase(TextureBaseName::GroundEnemy, L"res/GroundEnemy.png")) {
            std::cerr << "Error: Failed to load one or more textures." << std::endl;
            return true;  // エラー発生
        }

        return false;  // すべて正常にロード
    }

     //===============================================================================================
    //                  ゲーム中に使うテクスチャのパスを取得する
    //===============================================================================================
    bool AllTexture_Sprit(ResourceManager& rm) {
        if (rm.SplitTexture(SpriteName::Title) ||
            rm.SplitTexture(SpriteName::Player_Sight) ||
            rm.SplitTexture(SpriteName::Bullet) ||
            rm.SplitTexture(SpriteName::Bomber) ||
            rm.SplitTexture(SpriteName::AirEnemy_SmallSprite) ||
            rm.SplitTexture(SpriteName::AirEnemy_MiddleSprite) ||
            rm.SplitTexture(SpriteName::GroundEnemy_SmallSprite) ||
            rm.SplitTexture(SpriteName::GroundEnemy_LargeSprite) ||
            rm.SplitTexture(SpriteName::Boss) ||
            rm.SplitTexture(SpriteName::Algo_Core) ||
            rm.SplitTexture(SpriteName::MapChip) ) {
            std::cerr << "Error: Failed to load one or more textures." << std::endl;
            return true;  // エラー発生
        }

        return false;  // すべて正常にロード
    }



}


//===============================================================================================
//                  コンストラクタ
// 
// 1.管理するクラスのインスタンスをスマートポインタで生成する
// 2.ゲーム中に使用するテクスチャをTextureManagerに保存する
// 3.texturedataに格納された画像をスライスしてgametexturesに格納する
// 4.csvファイルを読み込み、ファイルをCsvDataManagerに保存する
//===============================================================================================
ResourceManager::ResourceManager(std::shared_ptr<GameApplication> g_app)
    :gameapp_(g_app)        //ゲームアプリケーションのスマートポインタを取得
{

    // 1.管理するクラスのインスタンスをスマートポインタで生成する
    texturemanager_ = std::make_shared<TextureManager>();
    csvdata = std::make_shared<CsvDataManager>();

    // 2.テクスチャのファイルパスを取得し、texturedataに格納する
    // 関数はnamespaceにある
    AllTextureLoad(*this);

    // 3.texturedataに格納された画像をスライスしてgametexturesに格納する
    // 関数はnamespaceにある
    AllTexture_Sprit(*this);


    //4.CSVファイルを取得する
    LoadMapCsvFile("res/Map/Stage1_Front.csv", "res/Map/Stage1_Back.csv");
    //LoadMapCsvFile("res/Map/Stage2_Front.csv", "res/Map/Stage2_Back.csv");
    //LoadMapCsvFile("res/Map/Stage3_Front.csv", "res/Map/Stage3_Back.csv");
}

//////////////////////////////////////////////// /* Texture関連 */ /////////////////////////////////////////////////////////////////////

//===============================================================================================
//                  テクスチャの取得
// 
// インスタンス化されているテクスチャを取り出す
//===============================================================================================
 std::shared_ptr<GameTexture> ResourceManager::GetTexture(TextureType type) {
    auto tex = texturemanager_->GetTexture(type);
    // テクスチャが有効かどうかを確認する
    if (tex == nullptr) {
        std::cerr << "Failed to load map chip texture: tex is null." << std::endl;
        return nullptr;  // 失敗を示す
    }

    // 正常に読み込まれた場合
    return tex;        // 成功を示す
}

//////////////////////////////////////////////// /* Csv関連 */ /////////////////////////////////////////////////////////////////////

 bool ResourceManager::LoadTextureBase(TextureBaseName name, const wchar_t* textureFilePath) {
     return texturemanager_->LoadTextureBase(
         name,
         textureFilePath,
         gameapp_->GetDevice(),
         gameapp_->GetDeviceContext()
     );
 }

 bool ResourceManager::SplitTexture(SpriteName name)
 {
     return texturemanager_->SplitTexture(
         name,
         gameapp_->GetDeviceContext()
     );
 }

 //===============================================================================================
// csvをファイルから読みだす
//===============================================================================================
bool ResourceManager::LoadMapCsvFile(const std::string& frontcsvfile, const std::string& baclcsvfile) {

    csvdata->LoadMapFile(frontcsvfile, baclcsvfile);

    return false;
}
//===============================================================================================
// csvファイルをint配列に変換する
//===============================================================================================
 std::vector<int> ResourceManager::ConvertDrawMapCsv_Vector() {
    return ConvertCsv_VectorReverse(csvdata->GetMapData());
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