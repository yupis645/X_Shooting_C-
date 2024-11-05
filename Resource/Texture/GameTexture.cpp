#include "GameTexture.h"
#include "pch.h"

using namespace DirectX;


//===============================================================================================
//                              �摜�̃��[�h
// 
// �����Ŏ󂯂����������Ƃɉ摜���X���C�X����B
// UseTextureDataConfig�ɂ�[�摜�̃t�@�C���p�X�A�X���C�X����摜�T�C�Y�A�s���A��]���p�b�N����Ă���
//===============================================================================================
bool GameTexture::SliceTexture(const std::wstring& path, TextureConfig cof) {
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
        textures_[i] = std::unique_ptr<Bmp>(emptyBmp[cof.startindex + i]);  // ���|�C���^�� unique_ptr �ɕϊ����Ċi�[
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
std::vector<std::unique_ptr<Bmp>> GameTexture::GetTexturesInRange(int startIndex, int count = 0) const {
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

Textures GameTexture::TextureSet(const wchar_t* textureFilePath)
{
    Textures textures;
    textures.Sprite = std::make_unique<SpriteBatch>(m_d3dContext.Get());      // 2D�X�v���C�g��`�ʂ���N���X�̃I�u�W�F�N�g�𐶐�
    ComPtr<ID3D11Resource> resource;        // ���\�[�X�𐶐�
    DX::ThrowIfFailed(
        CreateWICTextureFromFile(m_d3dDevice.Get(), textureFilePath, resource.GetAddressOf(), textures.SRV.ReleaseAndGetAddressOf())
    );          // �t�@�C������e�N�X�`����ǂݍ���

    return textures;
}

void GameTexture::SplitTexture(const Textures& textures, int spriteWidth, int spriteHeight)
{
    ComPtr<ID3D11Resource> resource;
    DX::ThrowIfFailed(textures.SRV->GetResource(&resource));

    ComPtr<ID3D11Texture2D> texture;
    DX::ThrowIfFailed(resource.As(&texture));

    CD3D11_TEXTURE2D_DESC textureDesc;
    texture->GetDesc(&textureDesc);             // �e�N�X�`���̏ڍ׏����擾

    int numSpritesX = textureDesc.Width / spriteWidth;
    int numSpritesY = textureDesc.Height / spriteHeight;

    for (int y = 0; y < numSpritesY; ++y) {
        for (int x = 0; x < numSpritesX; ++x) {
            RECT sourceRect = { x * spriteWidth, y * spriteHeight, (x + 1) * spriteWidth, (y + 1) * spriteHeight };

            // �X�v���C�g���Ƃ� `Textures` �C���X�^���X���쐬���A�e�N�X�`�������i�[
            auto spriteTextures = std::make_unique<Textures>();
            spriteTextures->Sprite = std::make_unique<SpriteBatch>(m_d3dContext.Get());
            spriteTextures->SRV = textures.SRV;  // �����V�F�[�_�[���\�[�X�r���[�����L

            tex.push_back(std::move(spriteTextures));  // `tex` �x�N�^�[�Ɋi�[
        }
    }
}