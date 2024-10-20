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
        // マップに存在するかチェック
      //  if (pngdata_.find(type) != pngdata_.end()) {
            pngdata_[type] = config;  // データを更新
            return true;  // 成功
     //   }
        //else {
        //    return false;  // 失敗: typeが存在しない
        //}
    }

    // テクスチャデータの取得
    const UseTextureDataConfig& GetTextureData(TextureType type) const {
        return pngdata_.at(type);  // 存在しない場合は例外をスロー
    }

private:
    std::map<TextureType, UseTextureDataConfig> pngdata_;
};

#endif //TEXTUREMANAGER_H

