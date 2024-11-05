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

    // 元のテクスチャを取得
    auto& it = basetexture.at(util::GetTextureType_From_SpriteName(name));

    // 返り値として使うベクター
    std::vector<std::unique_ptr<Textures>> slicedTextures;

    // 元のテクスチャのSRVを取得
    ComPtr<ID3D11ShaderResourceView> originalSRV = it.SRV;
    auto spriteBatch = std::make_unique<SpriteBatch>(deviceContext);

    // 行列の分割に従ってテクスチャをスライス
    for (int row = 0; row < typeconfig.rows; ++row) {
        for (int col = 0; col < typeconfig.columns; ++col) {
            int currentIndex = row * typeconfig.columns + col;
            // startindexとindexcountに基づいてテクスチャのスライスを選択
            if (currentIndex < typeconfig.startindex || currentIndex >= typeconfig.startindex + typeconfig.indexcount) {
                continue;
            }

            // 新しい Textures インスタンスを生成
            auto sliceTexture = std::make_unique<Textures>();
            sliceTexture->SRV = originalSRV;
            sliceTexture->Sprite = std::make_unique<SpriteBatch>(deviceContext);

            // スライスの範囲を計算
            RECT sliceRect;
            sliceRect.left = col * typeconfig.width;
            sliceRect.top = row * typeconfig.height;
            sliceRect.right = sliceRect.left + typeconfig.width;
            sliceRect.bottom = sliceRect.top + typeconfig.height;

            // スライスされた Textures オブジェクトをベクターに追加
            slicedTextures.push_back(std::move(sliceTexture));
        }
    }

    return false;
}

//=======================================================================================
//pngデータとサイズなどの情報を受けとり、画像をスライスしてメンバ変数に格納する
//=======================================================================================
bool TextureManager::CreateGameTexture(TextureType type, const std::wstring& path, TextureConfig config) {
    // textures_ に type に対応する GameTexture が存在しない場合、新たに作成して追加する
    if (textures_.find(type) == textures_.end()) {
        textures_[type] = std::make_shared<GameTexture>(path, config);        //画像データをインスタンス化し、データを渡す
        return false;    // 成功
    }

    return true;        // 失敗
}

//=======================================================================================
// TextureTypeをキーに任意の画像を保存しているGameTextureを返す
//=======================================================================================
std::shared_ptr<GameTexture> TextureManager::GetTexture(TextureType type) {
    // まず指定されたキーをmapから探す
    auto it = textures_.find(type);

    // キーが見つかった場合
    if (it != textures_.end()) {
        return it->second;
    }
    else {
        return nullptr;  // キーが見つからなければnullptrを返す
    }
}

