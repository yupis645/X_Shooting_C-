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
//                  １枚の画像を複数のキーで取り扱う
// 
// Enemyなどは一枚の画像に並んでいる場合、画像のパスは一つのキーにのみ保存する
// TextureTypeはenumなので番号が並んでいるため、連続しているキーで判別している
//===============================================================================================
    const std::wstring& TextureTypeToTexturePath(std::shared_ptr<TextureDataManager> tdm, TextureType type) {

        //PlayeerのpngデータにはPlayerとロックオンサイトの画像が入っている
        if (TextureType::Player <= type && type <= TextureType::Targetsight) {
            return tdm->GetTexturePath(TextureType::Player);
        }

        //Bulletのpngデータにはショットの弾とボムの画像が入っている
        if (TextureType::Bullet <= type && type <= TextureType::Bom) {
            return tdm->GetTexturePath(TextureType::Bullet);
        }

        //Bomberのpngデータには 自機 / 地上の構造物 / ボム の爆破画像と空中の敵の撃破時の画像が入っている
        if (TextureType::Bomber <= type && type <= TextureType::Ground_EnemyBomber) {
            return tdm->GetTexturePath(TextureType::Bomber);
        }
        //AirEnemyのpngデータには空中の敵の画像が入っている
        if (TextureType::AirEnemy <= type && type <= TextureType::Bacura) {
            return tdm->GetTexturePath(TextureType::AirEnemy);
        }

        //GroundEnemyのpngデータには地上の敵の画像が入っている
        if (TextureType::GroundEnemy <= type && type <= TextureType::Spflag) {
            return tdm->GetTexturePath(TextureType::GroundEnemy);
        }
        //GroundEnemyのpngデータには地上の敵の画像が入っている
        if (TextureType::Algo <= type && type <= TextureType::Ad_core) {
            return tdm->GetTexturePath(TextureType::BossParts);
        }

        //当てはまるものがなければそのままtypeのものを使う
        return tdm->GetTexturePath(type);

    }

    //===============================================================================================
    //                  ゲーム中に使うテクスチャのパスを取得する
    //===============================================================================================
    bool AllTextureLoad(ResourceManager& rm) {
        if (rm.InitTextureLoad(TextureType::Title, L"res/Title.png") ||
            rm.InitTextureLoad(TextureType::Player, L"res/Player_Sight.png") ||
            rm.InitTextureLoad(TextureType::Bullet, L"res/Bullet.png") ||
            rm.InitTextureLoad(TextureType::Boss, L"res/Boss.png") ||
            rm.InitTextureLoad(TextureType::BossParts, L"res/Bossparts.png") ||
            rm.InitTextureLoad(TextureType::Bomber, L"res/Bomber.png") ||
            rm.InitTextureLoad(TextureType::Map, L"res/MapChip.png") ||
            rm.InitTextureLoad(TextureType::AirEnemy, L"res/AirEnemy.png") ||
            rm.InitTextureLoad(TextureType::GroundEnemy, L"res/GroundEnemy.png")) {
            std::cerr << "Error: Failed to load one or more textures." << std::endl;
            return true;  // エラー発生
        }

        return false;  // すべて正常にロード
    }

//===============================================================================================
   //                  プレイヤーが使う画像を作成する
   //===============================================================================================
    bool Player_Convert_GameTex(ResourceManager& rm) {
        if (rm.SliceTexturebytype(TextureType::Player, TextureConfigs::PLAYER) ||
            rm.SliceTexturebytype(TextureType::Targetsight, TextureConfigs::TARGETSIGHT) ||
            rm.SliceTexturebytype(TextureType::Bullet, TextureConfigs::BULLET) ||
            rm.SliceTexturebytype(TextureType::Bom, TextureConfigs::BOM) ||
            rm.SliceTexturebytype(TextureType::PlayerBomber, TextureConfigs::COMMON_BOMBER) ||
            rm.SliceTexturebytype(TextureType::BomBomber, TextureConfigs::COMMON_BOMBER)) {
            std::cerr << "Error: Failed to Player convert." << std::endl;
            return true;  // エラー発生
        }
        return false;
    }
//===============================================================================================
  //                  タイトル画面で使う画像を作成する
  //===============================================================================================
    bool Title_Convert_GameTex(ResourceManager& rm) {
        if (rm.SliceTexturebytype(TextureType::Title, TextureConfigs::TITLE)) {       //タイトルロゴ
            std::cerr << "Error: Failed to title convert." << std::endl;
            return true;  // エラー発生
        }
        return false;
    }
//===============================================================================================
 //                  mapで使うマップチップの画像を作成する
 //===============================================================================================
    bool Map_Convert_GameTex(ResourceManager& rm) {
        if (rm.SliceTexturebytype(TextureType::Map, TextureConfigs::MAP)) {
            std::cerr << "Error: Failed to map convert." << std::endl;
            return true;  // エラー発生
        }
        return false;
    }
//===============================================================================================
 //                  地上敵の画像を作成する
 //===============================================================================================
    bool GroundEnemy_Convert_GameTex(ResourceManager& rm) {
        if (rm.SliceTexturebytype(TextureType::Ground_EnemyBomber, TextureConfigs::COMMON_BOMBER)) {
            std::cerr << "Error: Failed to GroundEnemy convert." << std::endl;
        }
        if (rm.SliceTexturebytype(TextureType::Barra, TextureConfigs::BARRA)) {
            std::cerr << "Error: Failed to GroundEnemy convert." << std::endl;
        }
        if (rm.SliceTexturebytype(TextureType::Zolbak, TextureConfigs::ZOLBAK)) {
            std::cerr << "Error: Failed to GroundEnemy convert." << std::endl;
        }
        if (rm.SliceTexturebytype(TextureType::Logram, TextureConfigs::LOGRAM)) {
            std::cerr << "Error: Failed to GroundEnemy convert." << std::endl;
        }
        if (rm.SliceTexturebytype(TextureType::Domogram, TextureConfigs::DOMOGRAM)) {
            std::cerr << "Error: Failed to GroundEnemy convert." << std::endl; 
        }
        if (rm.SliceTexturebytype(TextureType::Derota, TextureConfigs::DEROTA)) {
            std::cerr << "Error: Failed to GroundEnemy convert." << std::endl;
        }
        if (rm.SliceTexturebytype(TextureType::Grobda, TextureConfigs::GROBDA)) {
            std::cerr << "Error: Failed to GroundEnemy convert." << std::endl;
        }
        if (rm.SliceTexturebytype(TextureType::Bozalogram, TextureConfigs::BOZALOGRAM)) {
            std::cerr << "Error: Failed to GroundEnemy convert." << std::endl;
        }
        if (rm.SliceTexturebytype(TextureType::Sol, TextureConfigs::SOL)) { 
            std::cerr << "Error: Failed to GroundEnemy convert." << std::endl;
        }
        if (rm.SliceTexturebytype(TextureType::Garubarra, TextureConfigs::GARUBARRA)) {
            std::cerr << "Error: Failed to GroundEnemy convert." << std::endl;
        }
        if (rm.SliceTexturebytype(TextureType::Garuderota, TextureConfigs::GARUDEROTA)) {
            std::cerr << "Error: Failed to GroundEnemy convert." << std::endl; 
        }
        if (rm.SliceTexturebytype(TextureType::Boss, TextureConfigs::BOSS))
        {
            std::cerr << "Error: Failed to GroundEnemy convert." << std::endl;
        }
        if (rm.SliceTexturebytype(TextureType::Algo, TextureConfigs::ALGO)) {
            std::cerr << "Error: Failed to GroundEnemy convert." << std::endl;
        }
        if (rm.SliceTexturebytype(TextureType::Ad_core, TextureConfigs::AD_CORE)) {
            std::cerr << "Error: Failed to GroundEnemy convert." << std::endl;
        }
        if (rm.SliceTexturebytype(TextureType::Spflag, TextureConfigs::SPFLAG)) {
            std::cerr << "Error: Failed to GroundEnemy convert." << std::endl;
        }

        return false;
        //return false;
        // if (rm.SliceTexturebytype(TextureType::Ground_EnemyBomber, TextureConfigs::COMMON_BOMBER) ||
        //    rm.SliceTexturebytype(TextureType::Barra, TextureConfigs::BARRA) ||
        //    rm.SliceTexturebytype(TextureType::Zolbak, TextureConfigs::ZOLBAK) ||
        //    rm.SliceTexturebytype(TextureType::Logram, TextureConfigs::LOGRAM) ||
        //    rm.SliceTexturebytype(TextureType::Domogram, TextureConfigs::DOMOGRAM) ||
        //    rm.SliceTexturebytype(TextureType::Derota, TextureConfigs::DEROTA) ||
        //    rm.SliceTexturebytype(TextureType::Grobda, TextureConfigs::GROBDA) ||
        //    rm.SliceTexturebytype(TextureType::Bozalogram, TextureConfigs::BOZALOGRAM) ||
        //    rm.SliceTexturebytype(TextureType::Sol, TextureConfigs::SOL) ||
        //    rm.SliceTexturebytype(TextureType::Garubarra, TextureConfigs::GARUBARRA) ||
        //    rm.SliceTexturebytype(TextureType::Garuderota, TextureConfigs::GARUDEROTA) ||
        //    rm.SliceTexturebytype(TextureType::Boss, TextureConfigs::BOSS) ||
        //    rm.SliceTexturebytype(TextureType::Algo, TextureConfigs::ALGO) ||
        //    rm.SliceTexturebytype(TextureType::Ad_core, TextureConfigs::AD_CORE) ||
        //    rm.SliceTexturebytype(TextureType::Spflag, TextureConfigs::SPFLAG)) {
        //    std::cerr << "Error: Failed to GroundEnemy convert." << std::endl;
        //    return true;  // エラー発生
        //}
        //return false;
    }

//===============================================================================================
//                  空中敵の画像を作成する
//===============================================================================================
    bool AirEnemy_Convert_GameTex(ResourceManager& rm) {
        if (rm.SliceTexturebytype(TextureType::Air_EnemyBomber, TextureConfigs::AIR_ENEMYBOMBER) ||
            rm.SliceTexturebytype(TextureType::Toroid, TextureConfigs::TOROID) ||
            rm.SliceTexturebytype(TextureType::Torkan, TextureConfigs::TORKAN) ||
            rm.SliceTexturebytype(TextureType::Giddospario, TextureConfigs::GIDDOSPARIO) ||
            rm.SliceTexturebytype(TextureType::Zoshi, TextureConfigs::ZOSHI) ||
            rm.SliceTexturebytype(TextureType::Jara, TextureConfigs::JARA) ||
            rm.SliceTexturebytype(TextureType::Kapi, TextureConfigs::KAPI) ||
            rm.SliceTexturebytype(TextureType::Terrazi, TextureConfigs::TERRAZI) ||
            rm.SliceTexturebytype(TextureType::Zakato, TextureConfigs::ZAKATO) ||
            rm.SliceTexturebytype(TextureType::Bragzakato, TextureConfigs::BRAGZAKATO) ||
            rm.SliceTexturebytype(TextureType::Garuzakato, TextureConfigs::GARUZAKATO) ||
            rm.SliceTexturebytype(TextureType::Bacura, TextureConfigs::BACURA)) {
            std::cerr << "Error: Failed to AirEnemy convert." << std::endl;
            return true;  // エラー発生
        }
        return false;
    }


//===============================================================================================
//                  テクスチャをゲームで使えるようにスライスする
//===============================================================================================
    bool AllTex_Convert_GameTex(ResourceManager& rm) {

        if (Player_Convert_GameTex(rm) ||
            Title_Convert_GameTex(rm) ||
            Map_Convert_GameTex(rm) ||
            GroundEnemy_Convert_GameTex(rm) ||
            AirEnemy_Convert_GameTex(rm)) {
            std::cerr << "Error: Failed to Texture convert." << std::endl;
            return true;  // エラー発生
        }

        return false;  // すべて正常にロード
    }

}


//===============================================================================================
//                  コンストラクタ
// 
// 1.管理するクラスのインスタンスをスマートポインタで生成する
// 2.ゲーム中に使用するテクスチャをTextureDataManagerに保存する
// 3.texturedataに格納された画像をスライスしてgametexturesに格納する
// 4.csvファイルを読み込み、ファイルをCsvDataManagerに保存する
//===============================================================================================
ResourceManager::ResourceManager()
{

    // 1.管理するクラスのインスタンスをスマートポインタで生成する
    texturedata = std::make_shared<TextureDataManager>();
    csvdata = std::make_shared<CsvDataManager>();

    // 2.テクスチャのファイルパスを取得し、texturedataに格納する
    // 関数はnamespaceにある
    AllTextureLoad(*this);

    // 3.texturedataに格納された画像をスライスしてgametexturesに格納する
    // 関数はnamespaceにある
    AllTex_Convert_GameTex(*this);


    //4.CSVファイルを取得する
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
        return true;
    }

    texturedata->SetTexPath(type, path);

    return false;
}



//===============================================================================================
//                  テクスチャのセットアップ
// 
// Textruetypeで指定されたキーにpngと付随情報を入れる
//===============================================================================================
bool ResourceManager::SliceTexturebytype(TextureType type, TextureConfig config)
{
    if (texturedata->CreateGameTexture(type, TextureTypeToTexturePath(texturedata, type), config))
    {
        std::wcerr << L"Error: Texture  not found : " << std::endl;
        return true;
    }
    return false;
}

//===============================================================================================
//                  テクスチャの取得
// 
// インスタンス化されているテクスチャを取り出す
//===============================================================================================
 std::shared_ptr<GameTexture> ResourceManager::GetTexture(TextureType type) {
    auto tex = texturedata->GetTexture(type);
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