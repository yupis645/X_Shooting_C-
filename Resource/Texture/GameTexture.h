#ifndef GAMETEXTURE_H
#define GAMETEXTURE_H

//-----------------------------------------------------------------------------------------------
//              �Q�[���Ŏg���ꖇ�̃e�N�X�`���ɑ΂������ێ�����N���X
// 
// �X���C�X���ꂽ�摜��ۑ�����N���X
// �����o�ϐ��̃C���f�b�N�X��ɕt���X���C�X���ꂽ�摜�������Ă���B
// Load�֐��ł�png�f�[�^�A�X���C�X����摜�̉��A�c�̒����A�s���A�񐔂����Ă����ăX���C�X���ꂽ�摜�������o�ϐ��Ɋi�[���Ă���
// Draw�֐��ŃC���f�b�N�X�ƍ��W���������Ƃ��Ď󂯎��A���̈ʒu����摜��\��������
//-----------------------------------------------------------------------------------------------

#include <vector>
#include <memory>
#include <iostream>
#include <stdexcept>
#include "conioex.h"
#include "types.h"

class GameTexture {
public:
    GameTexture(UseTextureDataConfig config) { Load(config); }

    //===============================================================================================
    //�摜�̃��[�h
    //===============================================================================================
    bool Load(UseTextureDataConfig config);

    //===============================================================================================
    // �w�肵���C���f�b�N�X�̉摜��`��
    //===============================================================================================
    void Draw(int index, int x, int y) const;

    //===============================================================================================
    // �f�X�g���N�^�œ��I�Ɋm�ۂ��ꂽ�����������
    //===============================================================================================
    ~GameTexture() = default;


private:
    std::vector<std::unique_ptr<Bmp>> textures_;  // �摜��ێ�����|�C���^�z��
};


//===============================================================================================
//�摜�̃��[�h
//===============================================================================================
inline bool GameTexture::Load(UseTextureDataConfig config) {
    size_t totalImages = config.row * config.column;
    textures_.resize(totalImages);  // �K�v�ȕ������|�C���^�z������T�C�Y

    // Bmp* �z����쐬
    Bmp** s = new Bmp * [totalImages];
    if (!LoadDivBmp(config.texturepath, 0, 0, config.width, config.height, config.row, config.column, s)) {
        std::cerr << "Error: Failed to load texture: " << config.texturepath << std::endl;
        delete[] s;  // ���������[�N��h�����߂ɔz������
        return false;
    }

    // s �̓��e�� textures_ �Ɉړ�
    for (size_t i = 0; i < totalImages; ++i) {
        textures_[i] = std::unique_ptr<Bmp>(s[i]);  // ���|�C���^�� unique_ptr �ɕϊ����Ċi�[
    }

    // s �z�񎩑̂����
    delete[] s;

    return true;
}

//===============================================================================================
//�摜�̕\��
//===============================================================================================
inline void  GameTexture::Draw(int index, int x, int y) const {
    if (index < 0 || index >= textures_.size()) {
        std::cerr << "Error: Invalid texture index: " << index << std::endl;
        return;
    }
    Bmp* s = textures_[index].get();
    DrawBmp(x, y, s);
}

#endif //GAMETEXTURE_H