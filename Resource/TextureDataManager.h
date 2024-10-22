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

private:
    std::map<TextureType, TextureConfig> texdatacongfig;
    std::map<TextureType, std::wstring> texturepath;
};


#endif //TEXTUREMANAGER_H
