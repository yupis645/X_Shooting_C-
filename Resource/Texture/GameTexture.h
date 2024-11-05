#ifndef GAMETEXTURE_H
#define GAMETEXTURE_H

//-----------------------------------------------------------------------------------------------
//              �Q�[���Ŏg���ꖇ�̃e�N�X�`���ɑ΂������ێ�����N���X
// 
// �X���C�X���ꂽ�摜��ۑ�����N���X
// �����o�ϐ��̃C���f�b�N�X��ɕt���X���C�X���ꂽ�摜�������Ă���B
// Load�֐��ł�png�f�[�^�A�X���C�X����摜�̉��A�c�̒����A�s���A�񐔂����Ă����ăX���C�X���ꂽ�摜�������o�ϐ��Ɋi�[���Ă���
// Draw�֐��ŃC���f�b�N�X�ƍ��W���������Ƃ��Ď󂯎��A���̈ʒu����摜��\��������
// Load�֐��ADraw�֐���inline�ŃN���X�O�ɓ��e�������Ă���
//-----------------------------------------------------------------------------------------------

#include "conioex.h"

class GameTexture {
public:
    GameTexture(const std::wstring& path, TextureConfig cof) :config(cof) { SliceTexture(path, cof); }
    
    bool SliceTexture(const std::wstring& path, TextureConfig cof);     //�摜�̃��[�h inline�֐�

    std::vector<std::unique_ptr<Bmp>> GetTexturesInRange(int startIndex, int count) const; // �V�����֐�

    Textures TextureSet(const wchar_t* textureFilePath);

    void SplitTexture(const Textures& textures, int spriteWidth, int spriteHeight);

    Bmp* GetTextureIndex(int index) const {
        // �C���f�b�N�X�͈̔̓`�F�b�N
        if (index < 0 || index >= static_cast<int>(textures_.size())) {
            std::cerr << "Error: Invalid texture index: " << index << std::endl;
            return nullptr;
        }

        // �w�肳�ꂽ�C���f�b�N�X�̃e�N�X�`����Ԃ�
        return textures_[index].get();
    }

    const std::vector<std::unique_ptr<Bmp>>& GetTextures() const {
        return textures_;
    }

    TextureConfig GetConfig() { return config; }

    ~GameTexture() = default;       // �f�X�g���N�^


private:
    TextureConfig config;
    std::vector<std::unique_ptr<Bmp>> textures_;  // �摜��ێ�����|�C���^�z��

    std::vector<std::unique_ptr<Textures>> tex;  // �摜��ێ�����|�C���^�z��

     
};



#endif //GAMETEXTURE_H