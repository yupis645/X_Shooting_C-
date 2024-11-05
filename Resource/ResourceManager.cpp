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

//.cpp���ł̂ݎg�p�����`���܂Ƃ߂�
namespace {
//===============================================================================================
// csv��int�z��ɕϊ�����֐�
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
                    int value = std::stoi(cell);  // �����ɕϊ�
                    data.push_back(value);        // �f�[�^���i�[
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
//                  �P���̉摜�𕡐��̃L�[�Ŏ�舵��
// 
// Enemy�Ȃǂ͈ꖇ�̉摜�ɕ���ł���ꍇ�A�摜�̃p�X�͈�̃L�[�ɂ̂ݕۑ�����
// TextureType��enum�Ȃ̂Ŕԍ�������ł��邽�߁A�A�����Ă���L�[�Ŕ��ʂ��Ă���
//===============================================================================================
    const std::wstring& TextureTypeToTexturePath(std::shared_ptr<TextureManager> tdm, TextureType type) {

        //Playeer��png�f�[�^�ɂ�Player�ƃ��b�N�I���T�C�g�̉摜�������Ă���
        if (TextureType::Player <= type && type <= TextureType::Targetsight) {
            return tdm->GetTexturePath(TextureType::Player);
        }

        //Bullet��png�f�[�^�ɂ̓V���b�g�̒e�ƃ{���̉摜�������Ă���
        if (TextureType::Bullet <= type && type <= TextureType::Bom) {
            return tdm->GetTexturePath(TextureType::Bullet);
        }

        //Bomber��png�f�[�^�ɂ� ���@ / �n��̍\���� / �{�� �̔��j�摜�Ƌ󒆂̓G�̌��j���̉摜�������Ă���
        if (TextureType::Bomber <= type && type <= TextureType::Ground_EnemyBomber) {
            return tdm->GetTexturePath(TextureType::Bomber);
        }
        //AirEnemy��png�f�[�^�ɂ͋󒆂̓G�̉摜�������Ă���
        if (TextureType::AirEnemy <= type && type <= TextureType::Bacura) {
            return tdm->GetTexturePath(TextureType::AirEnemy);
        }

        //GroundEnemy��png�f�[�^�ɂ͒n��̓G�̉摜�������Ă���
        if (TextureType::GroundEnemy <= type && type <= TextureType::Garuderota || type == TextureType::Spflag) {
            return tdm->GetTexturePath(TextureType::GroundEnemy);
        }
        //GroundEnemy��png�f�[�^�ɂ͒n��̓G�̉摜�������Ă���
        if (TextureType::Algo <= type && type <= TextureType::Ad_core) {
            return tdm->GetTexturePath(TextureType::BossParts);
        }

        //���Ă͂܂���̂��Ȃ���΂��̂܂�type�̂��̂��g��
        return tdm->GetTexturePath(type);

    }

    //===============================================================================================
    //                  �Q�[�����Ɏg���e�N�X�`���̃p�X���擾����
    //===============================================================================================
    bool AllTextureLoad(ResourceManager& rm) {
        if (rm.InitTextureLoad(TextureType::Title, L"res/Title.png") ||
            rm.InitTextureLoad(TextureType::Player, L"res/Player_Sight.png") ||
            rm.InitTextureLoad(TextureType::Bullet, L"res/Bullet.png") ||
            rm.InitTextureLoad(TextureType::Boss, L"res/Boss.png") ||
            rm.InitTextureLoad(TextureType::BossParts, L"res/Algo_Core.png") ||
            rm.InitTextureLoad(TextureType::Bomber, L"res/Bomber.png") ||
            rm.InitTextureLoad(TextureType::Map, L"res/MapChip.png") ||
            rm.InitTextureLoad(TextureType::AirEnemy, L"res/AirEnemy.png") ||
            rm.InitTextureLoad(TextureType::GroundEnemy, L"res/GroundEnemy.png")) {
            std::cerr << "Error: Failed to load one or more textures." << std::endl;
            return true;  // �G���[����
        }

        return false;  // ���ׂĐ���Ƀ��[�h
    }

//===============================================================================================
   //                  �v���C���[���g���摜���쐬����
   //===============================================================================================
    bool Player_Convert_GameTex(ResourceManager& rm) {
        if (rm.SliceTexturebytype(TextureType::Player,       TextureConfigs::PLAYER) ||
            rm.SliceTexturebytype(TextureType::Targetsight,  TextureConfigs::TARGETSIGHT) ||
            rm.SliceTexturebytype(TextureType::Bullet,       TextureConfigs::BULLET) ||
            rm.SliceTexturebytype(TextureType::Bom,          TextureConfigs::BOM) ||
            rm.SliceTexturebytype(TextureType::PlayerBomber, TextureConfigs::COMMON_BOMBER) ||
            rm.SliceTexturebytype(TextureType::BomBomber,    TextureConfigs::COMMON_BOMBER)) {
            std::cerr << "Error: Failed to Player convert." << std::endl;
            return true;  // �G���[����
        }
        return false;
    }
//===============================================================================================
  //                  �^�C�g����ʂŎg���摜���쐬����
  //===============================================================================================
    bool Title_Convert_GameTex(ResourceManager& rm) {
        if (rm.SliceTexturebytype(TextureType::Title, TextureConfigs::TITLE)) {       //�^�C�g�����S
            std::cerr << "Error: Failed to title convert." << std::endl;
            return true;  // �G���[����
        }
        return false;
    }
//===============================================================================================
 //                  map�Ŏg���}�b�v�`�b�v�̉摜���쐬����
 //===============================================================================================
    bool Map_Convert_GameTex(ResourceManager& rm) {
        if (rm.SliceTexturebytype(TextureType::Map, TextureConfigs::MAP)) {
            std::cerr << "Error: Failed to map convert." << std::endl;
            return true;  // �G���[����
        }
        return false;
    }
//===============================================================================================
 //                  �n��G�̉摜���쐬����
 //===============================================================================================
    bool GroundEnemy_Convert_GameTex(ResourceManager& rm) {
         if (rm.SliceTexturebytype(TextureType::Ground_EnemyBomber, TextureConfigs::COMMON_BOMBER) ||
            rm.SliceTexturebytype(TextureType::Barra,               TextureConfigs::BARRA) ||
            rm.SliceTexturebytype(TextureType::Zolbak,              TextureConfigs::ZOLBAK) ||
            rm.SliceTexturebytype(TextureType::Logram,              TextureConfigs::LOGRAM) ||
            rm.SliceTexturebytype(TextureType::Domogram,            TextureConfigs::DOMOGRAM) ||
            rm.SliceTexturebytype(TextureType::Derota,              TextureConfigs::DEROTA) ||
            rm.SliceTexturebytype(TextureType::Grobda,              TextureConfigs::GROBDA) ||
            rm.SliceTexturebytype(TextureType::Bozalogram,          TextureConfigs::BOZALOGRAM) ||
            rm.SliceTexturebytype(TextureType::Sol,                 TextureConfigs::SOL) ||
            rm.SliceTexturebytype(TextureType::Garubarra,           TextureConfigs::GARUBARRA) ||
            rm.SliceTexturebytype(TextureType::Garuderota,          TextureConfigs::GARUDEROTA) ||
            rm.SliceTexturebytype(TextureType::Boss,                TextureConfigs::BOSS) ||
            rm.SliceTexturebytype(TextureType::Algo,                TextureConfigs::ALGO) ||
            rm.SliceTexturebytype(TextureType::Ad_core,             TextureConfigs::AD_CORE) ||
            rm.SliceTexturebytype(TextureType::Spflag,              TextureConfigs::SPFLAG)) {
            std::cerr << "Error: Failed to GroundEnemy convert." << std::endl;
            return true;  // �G���[����
        }
        return false;
    }

//===============================================================================================
//                  �󒆓G�̉摜���쐬����
//===============================================================================================
    bool AirEnemy_Convert_GameTex(ResourceManager& rm) {
        if (rm.SliceTexturebytype(TextureType::Air_EnemyBomber, TextureConfigs::AIR_ENEMYBOMBER) ||
            rm.SliceTexturebytype(TextureType::Toroid,          TextureConfigs::TOROID) ||
            rm.SliceTexturebytype(TextureType::Torkan,          TextureConfigs::TORKAN) ||
            rm.SliceTexturebytype(TextureType::Giddospario,     TextureConfigs::GIDDOSPARIO) ||
            rm.SliceTexturebytype(TextureType::Zoshi,           TextureConfigs::ZOSHI) ||
            rm.SliceTexturebytype(TextureType::Jara,            TextureConfigs::JARA) ||
            rm.SliceTexturebytype(TextureType::Kapi,            TextureConfigs::KAPI) ||
            rm.SliceTexturebytype(TextureType::Terrazi,         TextureConfigs::TERRAZI) ||
            rm.SliceTexturebytype(TextureType::Zakato,          TextureConfigs::ZAKATO) ||
            rm.SliceTexturebytype(TextureType::Bragzakato,      TextureConfigs::BRAGZAKATO) ||
            rm.SliceTexturebytype(TextureType::Garuzakato,      TextureConfigs::GARUZAKATO) ||
            rm.SliceTexturebytype(TextureType::Bacura,          TextureConfigs::BACURA)) {
            std::cerr << "Error: Failed to AirEnemy convert." << std::endl;
            return true;  // �G���[����
        }
        return false;
    }


//===============================================================================================
//                  �e�N�X�`�����Q�[���Ŏg����悤�ɃX���C�X����
//===============================================================================================
    bool AllTex_Convert_GameTex(ResourceManager& rm) {

        if (Player_Convert_GameTex(rm) ||
            Title_Convert_GameTex(rm) ||
            Map_Convert_GameTex(rm) ||
            GroundEnemy_Convert_GameTex(rm) ||
            AirEnemy_Convert_GameTex(rm)) {
            std::cerr << "Error: Failed to Texture convert." << std::endl;
            return true;  // �G���[����
        }

        return false;  // ���ׂĐ���Ƀ��[�h
    }

}


//===============================================================================================
//                  �R���X�g���N�^
// 
// 1.�Ǘ�����N���X�̃C���X�^���X���X�}�[�g�|�C���^�Ő�������
// 2.�Q�[�����Ɏg�p����e�N�X�`����TextureManager�ɕۑ�����
// 3.texturedata�Ɋi�[���ꂽ�摜���X���C�X����gametextures�Ɋi�[����
// 4.csv�t�@�C����ǂݍ��݁A�t�@�C����CsvDataManager�ɕۑ�����
//===============================================================================================
ResourceManager::ResourceManager(std::shared_ptr<GameApplication> g_app)
    :gameapp_(g_app)        //�Q�[���A�v���P�[�V�����̃X�}�[�g�|�C���^���擾
{

    // 1.�Ǘ�����N���X�̃C���X�^���X���X�}�[�g�|�C���^�Ő�������
    texturemanager_ = std::make_shared<TextureManager>();
    csvdata = std::make_shared<CsvDataManager>();

    // 2.�e�N�X�`���̃t�@�C���p�X���擾���Atexturedata�Ɋi�[����
    // �֐���namespace�ɂ���
    AllTextureLoad(*this);

    // 3.texturedata�Ɋi�[���ꂽ�摜���X���C�X����gametextures�Ɋi�[����
    // �֐���namespace�ɂ���
    AllTex_Convert_GameTex(*this);


    //4.CSV�t�@�C�����擾����
    LoadMapCsvFile("res/Map/Stage1_Front.csv", "res/Map/Stage1_Back.csv");
    //LoadMapCsvFile("res/Map/Stage2_Front.csv", "res/Map/Stage2_Back.csv");
    //LoadMapCsvFile("res/Map/Stage3_Front.csv", "res/Map/Stage3_Back.csv");
}

//////////////////////////////////////////////// /* Texture�֘A */ /////////////////////////////////////////////////////////////////////

//===============================================================================================
//                  �e�N�X�`���̓ǂݍ���
// 
// �e�N�X�`���t�@�C����摜�̃T�C�Y�A�X���C�X���閇���Ȃǂ̃f�[�^��ۑ�����
//===============================================================================================
bool ResourceManager::InitTextureLoad(TextureType type, const std::wstring& path) {
    // �t�@�C���X�g���[�����J���đ��݃`�F�b�N
    std::wifstream file(path);
    if (!file) {
        std::wcerr << L"Error: Texture file not found at path: " << path << std::endl;
        return true;
    }

    texturemanager_->SetBaseTexture(type);

    return false;
}



//===============================================================================================
//                  �e�N�X�`���̃Z�b�g�A�b�v
// 
// Textruetype�Ŏw�肳�ꂽ�L�[��png�ƕt����������
//===============================================================================================
bool ResourceManager::SliceTexturebytype(TextureType type, TextureConfig config)
{
    if (texturemanager_->CreateGameTexture(type, TextureTypeToTexturePath(texturemanager_, type), config))
    {
        std::wcerr << L"Error: Texture  not found : " << std::endl;
        return true;
    }
    return false;
}

//===============================================================================================
//                  �e�N�X�`���̎擾
// 
// �C���X�^���X������Ă���e�N�X�`�������o��
//===============================================================================================
 std::shared_ptr<GameTexture> ResourceManager::GetTexture(TextureType type) {
    auto tex = texturemanager_->GetTexture(type);
    // �e�N�X�`�����L�����ǂ������m�F����
    if (tex == nullptr) {
        std::cerr << "Failed to load map chip texture: tex is null." << std::endl;
        return nullptr;  // ���s������
    }

    // ����ɓǂݍ��܂ꂽ�ꍇ
    return tex;        // ����������
}

//////////////////////////////////////////////// /* Csv�֘A */ /////////////////////////////////////////////////////////////////////

 bool ResourceManager::LoadTexture(TextureType type,const wchar_t* textureFilePath) {
     return texturemanager_->LoadTexture(
         type,
         textureFilePath,
         gameapp_->GetDevice(),
         gameapp_->GetDeviceContext()
     );
 }

 std::vector<std::unique_ptr<Textures>> ResourceManager::SplitTexture(TextureType type)
 {
     TextureConfig typeconfig = TextureConfigs::Configs.at(type);

     // ���̃e�N�X�`�����擾
     auto& it = texturemanager_->GetBaseTexture(type);

     // �Ԃ�l�Ƃ��Ďg���x�N�^�[
     std::vector<std::unique_ptr<Textures>> slicedTextures;

     // ���̃e�N�X�`����SRV���擾
     ComPtr<ID3D11ShaderResourceView> originalSRV = it.SRV;
     auto spriteBatch = std::make_unique<SpriteBatch>(gameapp_->GetDeviceContext().Get());

     // �s��̕����ɏ]���ăe�N�X�`�����X���C�X
     for (int row = 0; row < typeconfig .rows; ++row) {
         for (int col = 0; col < typeconfig .columns; ++col) {
             int currentIndex = row * typeconfig .columns + col;
             // startindex��indexcount�Ɋ�Â��ăe�N�X�`���̃X���C�X��I��
             if (currentIndex < typeconfig .startindex || currentIndex >= typeconfig .startindex + typeconfig .indexcount) {
                 continue;
             }

             // �V���� Textures �C���X�^���X�𐶐�
             auto sliceTexture = std::make_unique<Textures>();
             sliceTexture->SRV = originalSRV;
             sliceTexture->Sprite = std::make_unique<SpriteBatch>(gameapp_->GetDeviceContext().Get());

             // �X���C�X�͈̔͂��v�Z
             RECT sliceRect;
             sliceRect.left = col * typeconfig .width;
             sliceRect.top = row * typeconfig .height;
             sliceRect.right = sliceRect.left + typeconfig .width;
             sliceRect.bottom = sliceRect.top + typeconfig .height;

             // �X���C�X���ꂽ Textures �I�u�W�F�N�g���x�N�^�[�ɒǉ�
             slicedTextures.push_back(std::move(sliceTexture));
         }
     }

     return slicedTextures;
 }

 //===============================================================================================
// csv���t�@�C������ǂ݂���
//===============================================================================================
bool ResourceManager::LoadMapCsvFile(const std::string& frontcsvfile, const std::string& baclcsvfile) {

    csvdata->LoadMapFile(frontcsvfile, baclcsvfile);

    return false;
}
//===============================================================================================
// csv�t�@�C����int�z��ɕϊ�����
//===============================================================================================
 std::vector<int> ResourceManager::ConvertDrawMapCsv_Vector() {
    return ConvertCsv_VectorReverse(csvdata->GetMapData());
}

//===============================================================================================
// csv����int�z��ɕϊ����Ă��̂܂ܕԂ�
//===============================================================================================
std::vector<int> ResourceManager::ConvertCsv_Vector(const std::string& filename) {
    std::vector<int> tempData = readCsvData(filename);      //namespace�ɂ���֐���csv��int�z��ɕϊ�����
    if (tempData.empty()) {
        return {};  // �f�[�^���ǂݍ��߂Ȃ������ꍇ�A��̃x�N�^��Ԃ�
    }

    return tempData;  // �f�[�^�����̂܂ܕԂ�
}

//===============================================================================================
// csv����int�z��ɕϊ����ċt���ɂ��ĕԂ�
//===============================================================================================
std::vector<int> ResourceManager::ConvertCsv_VectorReverse(const std::string& filename) {
    std::vector<int> tempData = readCsvData(filename);      //namespace�ɂ���֐���csv��int�z��ɕϊ�����
    if (tempData.empty()) {
        return {};  // �f�[�^���ǂݍ��߂Ȃ������ꍇ�A��̃x�N�^��Ԃ�
    }

    return std::vector<int>(tempData.rbegin(), tempData.rend());  // �f�[�^���t���ɂ��ĕԂ�
}