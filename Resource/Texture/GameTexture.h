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

#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "conioex.h"
#include "types.h"

class GameTexture {
public:
    GameTexture(const std::wstring& path, TextureConfig cof) { SliceTexture(path, cof); }
    
    bool SliceTexture(const std::wstring& path, TextureConfig cof);     //�摜�̃��[�h inline�֐�

    std::vector<std::unique_ptr<Bmp>> GetTexturesInRange(int startIndex, int count) const; // �V�����֐�

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

    ~GameTexture() = default;       // �f�X�g���N�^


private:
    TextureConfig config;
    std::vector<std::unique_ptr<Bmp>> textures_;  // �摜��ێ�����|�C���^�z��
};


//===============================================================================================
//                              �摜�̃��[�h
// 
// �����Ŏ󂯂����������Ƃɉ摜���X���C�X����B
// UseTextureDataConfig�ɂ�[�摜�̃t�@�C���p�X�A�X���C�X����摜�T�C�Y�A�s���A��]���p�b�N����Ă���
//===============================================================================================
inline bool GameTexture::SliceTexture(const std::wstring& path, TextureConfig cof) {
    size_t totalImages = cof.rows * cof.columns;     // �s * �� �ŉ摜�̐����擾
    if (cof.indexcount > totalImages) {
        std::cerr << "Error: Invalid range specified (startIdx + count exceeds total images)." << std::endl;
        return false;
    }

    textures_.resize(cof.indexcount);  // �K�v�ȕ������|�C���^�z������T�C�Y

    // Bmp* �z����쐬
    Bmp** emptyBmp = new Bmp * [totalImages];  // LoadDivBmp�Ŏg�����߂ɋ�̔z����쐬

    if (!LoadDivBmp(path.c_str(), 0, 0, cof.width, cof.height, cof.rows, cof.columns, emptyBmp)) {
        // ���[�h�Ɏ��s�����ꍇ
        std::cerr << "Error: Failed to load texture: " << path.c_str() << std::endl;  // �G���[�R�[�h���o��
        delete[] emptyBmp;  // ���������[�N��h�����߂ɔz������
        return false;       // ���s
    }

    // �w�肳�ꂽ�͈͂̓��e�� textures_ �Ɉړ�
    for (int i = 0; i < cof.indexcount; ++i) {
        textures_[i] = std::unique_ptr<Bmp>(emptyBmp[cof.startindex+ i]);  // ���|�C���^�� unique_ptr �ɕϊ����Ċi�[
    }

    // emptyBmp �z�񎩑̂����
    delete[] emptyBmp;

    return true;
}

//===============================================================================================
//                    ���������摜��index���w�肵�Ă��͈̔͂��擾����
// 
// �����P�Ŏ擾����擾���J�n����index���w�肷��
// �����Q�ň����P����ǂꂾ���̐���index���擾����
//===============================================================================================
inline std::vector<std::unique_ptr<Bmp>> GameTexture::GetTexturesInRange(int startIndex, int count = 0) const {
    // �͈͂̌���
    if (startIndex < 0 || startIndex >= textures_.size()) {
        std::cerr << "Error: Invalid startIndex: " << startIndex << std::endl;
        return {};
    }

    // �擾�͈͂�textures_�̃T�C�Y�𒴂��Ȃ��悤�ɒ���
    int endIndex = (std::min)(static_cast<int>(textures_.size()), startIndex + count);

    std::vector<std::unique_ptr<Bmp>> result;
    for (int i = startIndex; i < endIndex; ++i) {
        // textures_�̓��e���R�s�[���ĐV����unique_ptr�ɂ���
        result.push_back(std::make_unique<Bmp>(*textures_[i]));
    }

    return result;
}


#endif //GAMETEXTURE_H