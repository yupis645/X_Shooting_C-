#include "TextureManager.h"

#include "GameTexture.h"

using namespace DirectX;

namespace util{
    TextureBaseName GetTextureBaseName_From_SpriteName(SpriteName name)
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
    SpriteName GetSpriteName_From_TextureType(TextureType type)
    {
        if (type == TextureType::Title)
        {
            return SpriteName::Title;
        }
        else if (type == TextureType::Player || type == TextureType::Targetsight) {
            return SpriteName::Player_Sight;
        }
        else if (type == TextureType::Bullet || type == TextureType::Bullet)
        {
            return SpriteName::Bullet;
        }
        else if (type == TextureType::Map) {
            return SpriteName::MapChip;
        }
        else if (type == TextureType::Bomber || type == TextureType::PlayerBomber ||
            type == TextureType::BomBomber ||
            type == TextureType::Air_EnemyBomber || type == TextureType::Ground_EnemyBomber) {
            return SpriteName::Bomber;
        }
        else if (type <= TextureType::Toroid && type >= TextureType::Garuzakato)
        {
            return SpriteName::AirEnemy_SmallSprite;
        }
        else if (type == TextureType::Bacura)
        {
            return SpriteName::AirEnemy_MiddleSprite;
        }
        else if (type <= TextureType::Barra && type >= TextureType::Sol ||
            type <= TextureType::Boss && type >= TextureType::Spflag)
        {
            return SpriteName::GroundEnemy_SmallSprite;
        }
        else if (type == TextureType::Garubarra || type == TextureType::Garuderota)
        {
            return SpriteName::GroundEnemy_LargeSprite;
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
    SpritesConfig config = SpritesConfigs::Configs.at(name);

    // �x�[�X�e�N�X�`�����擾
    auto& baseTexture = basetexture.at(util::GetTextureBaseName_From_SpriteName(name));
    ComPtr<ID3D11ShaderResourceView> originalSRV = baseTexture->SRV;

    // ���������e�N�X�`�����i�[����x�N�^�[
    std::vector<std::unique_ptr<Textures>> slicedTextures;

    // ��������slicedTextures�Ɋi�[
    for (int row = 0; row < config.rows; ++row) {
        for (int col = 0; col < config.columns; ++col) {
            auto sliceTexture = std::make_unique<Textures>();
            sliceTexture->SRV = originalSRV;
            sliceTexture->Sprite = std::make_unique<SpriteBatch>(deviceContext);

            RECT sliceRect;
            sliceRect.left = col * config.width;
            sliceRect.top = row * config.height;
            sliceRect.right = sliceRect.left + config.width;
            sliceRect.bottom = sliceRect.top + config.height;

            slicedTextures.push_back(std::move(sliceTexture));
        }
    }

    // spriteTextures�Ɋi�[
    sprites[name] = std::move(slicedTextures);

    return false;
}

inline const Textures* TextureManager::GetSprite(TextureType type, int index) const {
    const auto& textures = sprites.at(util::GetSpriteName_From_TextureType(type));

    if (index >= 0 && index < textures.size()) {
        int startindex = TextureConfigs::Configs.at(type).startindex;       //�^�C�v���Ƃɏ����Őݒ肳��Ă���index�ԍ����擾

        return textures[startindex + index].get(); // `unique_ptr` �̏��L�����ڂ����Ƀ|�C���^��Ԃ�
    }
    return nullptr; // �����ȃC���f�b�N�X�̏ꍇ�� `nullptr`
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

