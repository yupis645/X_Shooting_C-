#include "TextureManager.h"

#include "GameTexture.h"

using namespace DirectX;

namespace util{
    TextureBaseName GetTextureType_From_SpriteName(SpriteName name)
    {
        switch (name) {
        case SpriteName::Title:
            return TextureBaseName::Title;
        case SpriteName::Player_Sight:
            return TextureBaseName::Player_Sight;
        case SpriteName::Bullet:
            return TextureBaseName::Bullet;
        case SpriteName::Bomber:
            return TextureBaseName::Bomber;
        case SpriteName::AirEnemy_SmallSprite:
        case SpriteName::AirEnemy_MiddleSprite:
            return TextureBaseName::AirEnemy;
        case SpriteName::GroundEnemy_SmallSprite:
        case SpriteName::GroundEnemy_LargeSprite:
            return TextureBaseName::GroundEnemy;
            break;
        case SpriteName::Boss:
            return TextureBaseName::Boss;
        case SpriteName::Algo_Core:
            return TextureBaseName::Algo_Core;
        case SpriteName::MapChip:
            return TextureBaseName::MapChip;
        default:
            throw std::invalid_argument("Invalid SpriteName");
        }
    }
}

bool TextureManager::LoadTextureBase(TextureBaseName name, const wchar_t* textureFilePath, ComPtr<ID3D11Device1> device, ComPtr<ID3D11DeviceContext1> deviceContext) {
    try {
        auto textures = std::make_unique<Textures>();
        textures->Sprite = std::make_unique<SpriteBatch>(deviceContext.Get());

        ComPtr<ID3D11Resource> resource;
        DX::ThrowIfFailed(
            CreateWICTextureFromFile(device.Get(), textureFilePath, resource.GetAddressOf(), textures->SRV.ReleaseAndGetAddressOf())
        );

        ComPtr<ID3D11Texture2D> texture;
        DX::ThrowIfFailed(resource.As(&texture));

        CD3D11_TEXTURE2D_DESC textureDesc;
        texture->GetDesc(&textureDesc);

        basetexture[name] = std::move(textures);

        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to load texture: " << e.what() << std::endl;
        return false;
    }
}

bool TextureManager::SplitTexture(SpriteName name, ComPtr<ID3D11DeviceContext1> deviceContext)
{
    TextureConfig typeconfig = SpritesConfigs::Configs.at(name);

    // ���̃e�N�X�`�����擾
    auto& it = basetexture.at(util::GetTextureType_From_SpriteName(name));

    // �Ԃ�l�Ƃ��Ďg���x�N�^�[
    std::vector<std::unique_ptr<Textures>> slicedTextures;

    // ���̃e�N�X�`����SRV���擾
    ComPtr<ID3D11ShaderResourceView> originalSRV = it.SRV;
    auto spriteBatch = std::make_unique<SpriteBatch>(deviceContext);

    // �s��̕����ɏ]���ăe�N�X�`�����X���C�X
    for (int row = 0; row < typeconfig.rows; ++row) {
        for (int col = 0; col < typeconfig.columns; ++col) {
            int currentIndex = row * typeconfig.columns + col;
            // startindex��indexcount�Ɋ�Â��ăe�N�X�`���̃X���C�X��I��
            if (currentIndex < typeconfig.startindex || currentIndex >= typeconfig.startindex + typeconfig.indexcount) {
                continue;
            }

            // �V���� Textures �C���X�^���X�𐶐�
            auto sliceTexture = std::make_unique<Textures>();
            sliceTexture->SRV = originalSRV;
            sliceTexture->Sprite = std::make_unique<SpriteBatch>(deviceContext);

            // �X���C�X�͈̔͂��v�Z
            RECT sliceRect;
            sliceRect.left = col * typeconfig.width;
            sliceRect.top = row * typeconfig.height;
            sliceRect.right = sliceRect.left + typeconfig.width;
            sliceRect.bottom = sliceRect.top + typeconfig.height;

            // �X���C�X���ꂽ Textures �I�u�W�F�N�g���x�N�^�[�ɒǉ�
            slicedTextures.push_back(std::move(sliceTexture));
        }
    }

    return false;
}

//=======================================================================================
//png�f�[�^�ƃT�C�Y�Ȃǂ̏����󂯂Ƃ�A�摜���X���C�X���ă����o�ϐ��Ɋi�[����
//=======================================================================================
bool TextureManager::CreateGameTexture(TextureType type, const std::wstring& path, TextureConfig config) {
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
std::shared_ptr<GameTexture> TextureManager::GetTexture(TextureType type) {
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

