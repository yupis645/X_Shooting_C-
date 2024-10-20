#ifndef GAMETEXTURE_H
#define GAMETEXTURE_H

//-----------------------------------------------------------------------------------------------
//              ゲームで使う一枚のテクスチャに対する情報を保持するクラス
// 
// スライスされた画像を保存するクラス
// メンバ変数のインデックス一つに付きスライスされた画像が入っている。
// Load関数ではpngデータ、スライスする画像の横、縦の長さ、行数、列数をしていしてスライスされた画像をメンバ変数に格納していく
// Draw関数でインデックスと座標を引き数として受け取り、その位置から画像を表示させる
//-----------------------------------------------------------------------------------------------

#include <vector>
#include <memory>
#include <iostream>
#include <stdexcept>
#include "conioex.h"
#include "types.h"

class GameTexture {
public:
    GameTexture(UseTextureDataConfig config) { Load(config); }

    //===============================================================================================
    //画像のロード
    //===============================================================================================
    bool Load(UseTextureDataConfig config);

    //===============================================================================================
    // 指定したインデックスの画像を描画
    //===============================================================================================
    void Draw(int index, int x, int y) const;

    //===============================================================================================
    // デストラクタで動的に確保されたメモリを解放
    //===============================================================================================
    ~GameTexture() = default;


private:
    std::vector<std::unique_ptr<Bmp>> textures_;  // 画像を保持するポインタ配列
};


//===============================================================================================
//画像のロード
//===============================================================================================
inline bool GameTexture::Load(UseTextureDataConfig config) {
    size_t totalImages = config.row * config.column;
    textures_.resize(totalImages);  // 必要な分だけポインタ配列をリサイズ

    // Bmp* 配列を作成
    Bmp** s = new Bmp * [totalImages];
    if (!LoadDivBmp(config.texturepath, 0, 0, config.width, config.height, config.row, config.column, s)) {
        std::cerr << "Error: Failed to load texture: " << config.texturepath << std::endl;
        delete[] s;  // メモリリークを防ぐために配列を解放
        return false;
    }

    // s の内容を textures_ に移動
    for (size_t i = 0; i < totalImages; ++i) {
        textures_[i] = std::unique_ptr<Bmp>(s[i]);  // 生ポインタを unique_ptr に変換して格納
    }

    // s 配列自体を解放
    delete[] s;

    return true;
}

//===============================================================================================
//画像の表示
//===============================================================================================
inline void  GameTexture::Draw(int index, int x, int y) const {
    if (index < 0 || index >= textures_.size()) {
        std::cerr << "Error: Invalid texture index: " << index << std::endl;
        return;
    }
    Bmp* s = textures_[index].get();
    DrawBmp(x, y, s);
}

#endif //GAMETEXTURE_H