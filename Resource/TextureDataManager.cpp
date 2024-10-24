#include "TextureDataManager.h"

#include "GameTexture.h"


//=======================================================================================
//png�f�[�^�ƃT�C�Y�Ȃǂ̏����󂯂Ƃ�A�摜���X���C�X���ă����o�ϐ��Ɋi�[����
//=======================================================================================
bool TextureDataManager::CreateGameTexture(TextureType type, const std::wstring& path, TextureConfig config) {
    // textures_ �� type �ɑΉ����� GameTexture �����݂��Ȃ��ꍇ�A�V���ɍ쐬���Ēǉ�����
    if (textures_.find(type) == textures_.end()) {
        textures_[type] = std::make_shared<GameTexture>(path, config);        //�摜�f�[�^���C���X�^���X�����A�f�[�^��n��
        return false;    // ����
    }

    return true;        // ���s
}

//=======================================================================================
// TextureType���L�[�ɔC�ӂ̉摜��ۑ����Ă���GameTexture��Ԃ�
//=======================================================================================
std::shared_ptr<GameTexture> TextureDataManager::GetTexture(TextureType type) {
    // �܂��w�肳�ꂽ�L�[��map����T��
    auto it = textures_.find(type);

    // �L�[�����������ꍇ
    if (it != textures_.end()) {
        return it->second;
    }
    else {
        return nullptr;  // �L�[��������Ȃ����nullptr��Ԃ�
    }
}

