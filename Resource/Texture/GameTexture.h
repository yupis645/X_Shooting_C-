#ifndef GAMETEXTURE_H
#define GAMETEXTURE_H

//-----------------------------------------------------------------------------------------------
//              ゲームで使う一枚のテクスチャに対する情報を保持するクラス
// 
// スライスされた画像を保存するクラス
// メンバ変数のインデックス一つに付きスライスされた画像が入っている。
// Load関数ではpngデータ、スライスする画像の横、縦の長さ、行数、列数をしていしてスライスされた画像をメンバ変数に格納していく
// Draw関数でインデックスと座標を引き数として受け取り、その位置から画像を表示させる
// Load関数、Draw関数はinlineでクラス外に内容を書いている
//-----------------------------------------------------------------------------------------------

#include "conioex.h"

class GameTexture {
public:
    GameTexture(const std::wstring& path, TextureConfig cof) :config(cof) { SliceTexture(path, cof); }
    
    bool SliceTexture(const std::wstring& path, TextureConfig cof);     //画像のロード inline関数

    std::vector<std::unique_ptr<Bmp>> GetTexturesInRange(int startIndex, int count) const; // 新しい関数

    Textures TextureSet(const wchar_t* textureFilePath);

    void SplitTexture(const Textures& textures, int spriteWidth, int spriteHeight);

    Bmp* GetTextureIndex(int index) const {
        // インデックスの範囲チェック
        if (index < 0 || index >= static_cast<int>(textures_.size())) {
            std::cerr << "Error: Invalid texture index: " << index << std::endl;
            return nullptr;
        }

        // 指定されたインデックスのテクスチャを返す
        return textures_[index].get();
    }

    const std::vector<std::unique_ptr<Bmp>>& GetTextures() const {
        return textures_;
    }

    TextureConfig GetConfig() { return config; }

    ~GameTexture() = default;       // デストラクタ


private:
    TextureConfig config;
    std::vector<std::unique_ptr<Bmp>> textures_;  // 画像を保持するポインタ配列

    std::vector<std::unique_ptr<Textures>> tex;  // 画像を保持するポインタ配列

     
};



#endif //GAMETEXTURE_H