#ifndef TEXTUREDATAMANAGER_H
#define TEXTUREDATAMANAGER_H

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include "types.h"

class TextureDataManager {
public:
    TextureDataManager() {
    }

    bool LoadTextureData(TextureType type, const UseTextureDataConfig& config) {
        // �}�b�v�ɑ��݂��邩�`�F�b�N
      //  if (pngdata_.find(type) != pngdata_.end()) {
            pngdata_[type] = config;  // �f�[�^���X�V
            return true;  // ����
     //   }
        //else {
        //    return false;  // ���s: type�����݂��Ȃ�
        //}
    }

    // �e�N�X�`���f�[�^�̎擾
    const UseTextureDataConfig& GetTextureData(TextureType type) const {
        return pngdata_.at(type);  // ���݂��Ȃ��ꍇ�͗�O���X���[
    }

private:
    std::map<TextureType, UseTextureDataConfig> pngdata_;
};

#endif //TEXTUREMANAGER_H

