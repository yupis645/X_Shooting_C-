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
    //                  �Q�[�����Ɏg���e�N�X�`���̃p�X���擾����
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
            return true;  // �G���[����
        }

        return false;  // ���ׂĐ���Ƀ��[�h
    }

     //===============================================================================================
    //                  �Q�[�����Ɏg���e�N�X�`���̃p�X���擾����
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
    AllTexture_Sprit(*this);


    //4.CSV�t�@�C�����擾����
    LoadMapCsvFile("res/Map/Stage1_Front.csv", "res/Map/Stage1_Back.csv");
    //LoadMapCsvFile("res/Map/Stage2_Front.csv", "res/Map/Stage2_Back.csv");
    //LoadMapCsvFile("res/Map/Stage3_Front.csv", "res/Map/Stage3_Back.csv");
}

//////////////////////////////////////////////// /* Texture�֘A */ /////////////////////////////////////////////////////////////////////

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