#ifndef TEXTUREDATAMANAGER_H
#define TEXTUREDATAMANAGER_H

class GameTexture;

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include "types.h"

class TextureDataManager {
public:
    TextureDataManager() {
    }

    void SetTexConfig(TextureType type, const TextureConfig& config) {
        texdatacongfig[type] = config;  // データを更新
    }
    const TextureConfig& GetTextureConfig(TextureType type) const {
        return texdatacongfig.at(type);
    }

    void SetTexPath(TextureType type, const std::wstring& path) {
        texturepath[type] = path;  // データを更新
    }
    const std::wstring& GetTexturePath(TextureType type) const {
        return texturepath.at(type);
    }


    const wchar_t* WStringToConstWChar(const std::wstring& str) {
        return str.c_str();
    }

    //=======================================================================================
  //pngデータとサイズなどの情報を受けとり、画像をスライスしてメンバ変数に格納する
  //=======================================================================================
    bool CreateGameTexture(TextureType type, const std::wstring&, TextureConfig config);

    //=======================================================================================
    // 任意の GameTexture を描画する共通関数
    //=======================================================================================
    std::shared_ptr<GameTexture> GetTexture(TextureType type);

    //getter
    const std::map<TextureType, std::shared_ptr<GameTexture>>& GetAllTexture() const { return textures_; }

    //=======================================================================================
    //                          デストラクタ
    //=======================================================================================
    ~TextureDataManager() {}



private:
    std::map<TextureType, TextureConfig> texdatacongfig;
    std::map<TextureType, std::wstring> texturepath;
    std::map<TextureType, std::shared_ptr<GameTexture>> textures_;      // TextureType をキーにして GameTexture を管理するマップ

};


#endif //TEXTUREMANAGER_H
