#include "GameTextureManager.h"

//=======================================================================================
//pngデータとサイズなどの情報を受けとり、画像をスライスしてメンバ変数に格納する
//=======================================================================================
bool GameTextureManager::TextureInport( TextureType type , UseTextureDataConfig config) {
    // textures_ に type に対応する GameTexture が存在しない場合、新たに作成して追加する
    if (textures_.find(type) == textures_.end()) {
        textures_[type] = std::make_shared<GameTexture>(config);
        return false;    // 成功
    }

    return true;        // 失敗
}

//=======================================================================================
// 任意の GameTexture を描画する共通関数
//=======================================================================================

std::shared_ptr<GameTexture> GameTextureManager::GetTexture(TextureType type) {
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

//===============================================================================================
//画像のロード
//===============================================================================================
bool GameTextureManager::TextureLoad(TextureType type, UseTextureDataConfig config)
{
    textures_.at(type)->Load(config);

    return false;
}

//===============================================================================================
// 指定したインデックスの画像を描画
//===============================================================================================
void GameTextureManager::TextureDraw(TextureType type, int index, int x, int y)
{
    textures_.at(type)->Draw(index,x,y);
}
