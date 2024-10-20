#include "GameTextureManager.h"

//=======================================================================================
//png�f�[�^�ƃT�C�Y�Ȃǂ̏����󂯂Ƃ�A�摜���X���C�X���ă����o�ϐ��Ɋi�[����
//=======================================================================================
bool GameTextureManager::TextureInport( TextureType type , UseTextureDataConfig config) {
    // textures_ �� type �ɑΉ����� GameTexture �����݂��Ȃ��ꍇ�A�V���ɍ쐬���Ēǉ�����
    if (textures_.find(type) == textures_.end()) {
        textures_[type] = std::make_shared<GameTexture>(config);
        return false;    // ����
    }

    return true;        // ���s
}

//=======================================================================================
// �C�ӂ� GameTexture ��`�悷�鋤�ʊ֐�
//=======================================================================================

std::shared_ptr<GameTexture> GameTextureManager::GetTexture(TextureType type) {
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

//===============================================================================================
//�摜�̃��[�h
//===============================================================================================
bool GameTextureManager::TextureLoad(TextureType type, UseTextureDataConfig config)
{
    textures_.at(type)->Load(config);

    return false;
}

//===============================================================================================
// �w�肵���C���f�b�N�X�̉摜��`��
//===============================================================================================
void GameTextureManager::TextureDraw(TextureType type, int index, int x, int y)
{
    textures_.at(type)->Draw(index,x,y);
}
