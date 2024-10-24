#ifndef TEXTUREDATAMANAGER_H
#define TEXTUREDATAMANAGER_H

class GameTexture;

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include "types.h"

class TextureDataManager {
public:
    TextureDataManager() {
    }

    void SetTexConfig(TextureType type, const TextureConfig& config) {
        texdatacongfig[type] = config;  // �f�[�^���X�V
    }
    const TextureConfig& GetTextureConfig(TextureType type) const {
        return texdatacongfig.at(type);
    }

    void SetTexPath(TextureType type, const std::wstring& path) {
        texturepath[type] = path;  // �f�[�^���X�V
    }
    const std::wstring& GetTexturePath(TextureType type) const {
        return texturepath.at(type);
    }


    const wchar_t* WStringToConstWChar(const std::wstring& str) {
        return str.c_str();
    }

    //=======================================================================================
  //png�f�[�^�ƃT�C�Y�Ȃǂ̏����󂯂Ƃ�A�摜���X���C�X���ă����o�ϐ��Ɋi�[����
  //=======================================================================================
    bool CreateGameTexture(TextureType type, const std::wstring&, TextureConfig config);

    //=======================================================================================
    // �C�ӂ� GameTexture ��`�悷�鋤�ʊ֐�
    //=======================================================================================
    std::shared_ptr<GameTexture> GetTexture(TextureType type);

    //getter
    const std::map<TextureType, std::shared_ptr<GameTexture>>& GetAllTexture() const { return textures_; }

    //=======================================================================================
    //                          �f�X�g���N�^
    //=======================================================================================
    ~TextureDataManager() {}



private:
    std::map<TextureType, TextureConfig> texdatacongfig;
    std::map<TextureType, std::wstring> texturepath;
    std::map<TextureType, std::shared_ptr<GameTexture>> textures_;      // TextureType ���L�[�ɂ��� GameTexture ���Ǘ�����}�b�v

};


#endif //TEXTUREMANAGER_H
