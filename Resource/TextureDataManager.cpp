#include "TextureDataManager.h"

#include "GameTexture.h"


//=======================================================================================
//pngデータとサイズなどの情報を受けとり、画像をスライスしてメンバ変数に格納する
//=======================================================================================
bool TextureDataManager::CreateGameTexture(TextureType type, const std::wstring& path, TextureConfig config) {
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
std::shared_ptr<GameTexture> TextureDataManager::GetTexture(TextureType type) {
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

