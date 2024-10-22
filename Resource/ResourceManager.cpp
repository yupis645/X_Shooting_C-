#include "ResourceManager.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>  
#include <fstream>
#include "GameTexture.h"

//.cpp���ł̂ݎg�p�����`���܂Ƃ߂�
namespace  {
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
    //                  ������ & �Z�b�g�A�b�v
    // 
    // 1.�Ǘ�����N���X�̃C���X�^���X���X�}�[�g�|�C���^�Ő�������
    // 2.�Q�[�����Ɏg�p����e�N�X�`����TextureDataManager�ɕۑ����A
    //      GameTextureManager�ɂĉ摜���Q�[���Ŏg����悤�ɃX���C�X����
    // 3.csv�t�@�C����ǂݍ��݁A�t�@�C����CsvDataManager�ɕۑ�����
    //===============================================================================================
    bool Init_SetUpTexture(ResourceManager& manager, TextureType type, const std::wstring& path, const TextureConfig& config) {
        // InitTexture��SetUpTexture�����ɌĂяo��
        if (!manager.InitTextureLoad(type, path)) {
            std::cerr << "Error: Failed to initialize texture for type: " << static_cast<int>(type) << std::endl;
            return false;
        }

        if (!manager.SliceTexturebytype(type,config)) {
            std::cerr << "Error: Failed to set up texture for type: " << static_cast<int>(type) << std::endl;
            return false;
        }

        return true;  // �����̏��������������ꍇ��true��Ԃ�
    }

}


//===============================================================================================
//                  �R���X�g���N�^
// 
// 1.�Ǘ�����N���X�̃C���X�^���X���X�}�[�g�|�C���^�Ő�������
// 2.�Q�[�����Ɏg�p����e�N�X�`����TextureDataManager�ɕۑ����A
//      GameTextureManager�ɂĉ摜���Q�[���Ŏg����悤�ɃX���C�X����
// 3.csv�t�@�C����ǂݍ��݁A�t�@�C����CsvDataManager�ɕۑ�����
//===============================================================================================
ResourceManager::ResourceManager()
{

    // 1.�Ǘ�����N���X�̃C���X�^���X���X�}�[�g�|�C���^�Ő�������
    texturedata = std::make_shared<TextureDataManager>();
    csvdata = std::make_shared<CsvDataManager>();
    gametextures = std::make_shared<GameTextureManager>();

    // 2.�e�N�X�`�����Q�[�����ł��g����悤�Ƀ��[�h����
  Init_SetUpTexture(*this,TextureType::Title, L"res/Title.png", TextureConfigs::TITLE);       //�^�C�g�����S
  Init_SetUpTexture(*this,TextureType::Player,  L"res/Player_Sight.png",TextureConfigs::PLAYER);
  Init_SetUpTexture(*this,TextureType::Bullet,  L"res/Bullet.png",TextureConfigs::BULLET);
  Init_SetUpTexture(*this,TextureType::Boss,  L"res/Boss.png",TextureConfigs::BOSS);
  Init_SetUpTexture(*this,TextureType::BossSub,  L"res/Bossparts.png",TextureConfigs::BOSSSUB);
  Init_SetUpTexture(*this,TextureType::PlayerBomber,  L"res/Bomber.png",TextureConfigs::PLAYERBOMBER);
  Init_SetUpTexture(*this,TextureType::EnemyBomber,  L"res/Bomber.png",TextureConfigs::ENEMYBOMBER);
  Init_SetUpTexture(*this,TextureType::Map,  L"res/MapChip.png",TextureConfigs::MAP);

    //3.CSV�t�@�C�����擾����
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
        return false;
    }

    texturedata->SetTexPath(type, path);

    return true;
}



//===============================================================================================
//                  �e�N�X�`���̃Z�b�g�A�b�v
// 
// Textruetype�Ŏw�肳�ꂽ�L�[��png�ƕt����������
//===============================================================================================
bool ResourceManager::SliceTexturebytype(TextureType type, TextureConfig config)
{
    
    gametextures->CreateGameTexture(type,texturedata->GetTexturePath(type),config);
    return false;
}

//===============================================================================================
//                  �e�N�X�`���̎擾
// 
// �C���X�^���X������Ă���e�N�X�`�������o��
//===============================================================================================
inline std::shared_ptr<GameTexture> ResourceManager::GetTexture(TextureType type) {
    auto tex = gametextures->GetTexture(type);
    // �e�N�X�`�����L�����ǂ������m�F����
    if (tex == nullptr) {
        std::cerr << "Failed to load map chip texture: tex is null." << std::endl;
        return nullptr;  // ���s������
    }

    // ����ɓǂݍ��܂ꂽ�ꍇ
    return tex;        // ����������
}

//////////////////////////////////////////////// /* Csv�֘A */ /////////////////////////////////////////////////////////////////////

//===============================================================================================
// csv���t�@�C������ǂ݂���
//===============================================================================================
bool ResourceManager::LoadMapCsvFile(const std::string& frontcsvfile, const std::string& baclcsvfile) {

    csvdata->LoadMapData(frontcsvfile, baclcsvfile);

    return false;
}
//===============================================================================================
// csv�t�@�C����int�z��ɕϊ�����
//===============================================================================================
inline std::vector<int> ResourceManager::ConvertDrawMapCsv_Vector() {
    return ConvertCsv_VectorReverse(csvdata->GetDrawmapcsv());
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