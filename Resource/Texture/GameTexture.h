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

#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "conioex.h"
#include "types.h"

class GameTexture {
public:
    GameTexture(const std::wstring& path, TextureConfig cof) { SliceTexture(path, cof); }
    
    bool SliceTexture(const std::wstring& path, TextureConfig cof);     //画像のロード inline関数

    std::vector<std::unique_ptr<Bmp>> GetTexturesInRange(int startIndex, int count) const; // 新しい関数

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

    ~GameTexture() = default;       // デストラクタ


private:
    TextureConfig config;
    std::vector<std::unique_ptr<Bmp>> textures_;  // 画像を保持するポインタ配列
};


//===============================================================================================
//                              画像のロード
// 
// 引数で受けった情報をもとに画像をスライスする。
// UseTextureDataConfigには[画像のファイルパス、スライスする画像サイズ、行数、列数]がパックされている
//===============================================================================================
inline bool GameTexture::SliceTexture(const std::wstring& path, TextureConfig cof) {
    size_t totalImages = cof.rows * cof.columns;     // 行 * 列 で画像の数を取得
    if (cof.indexcount > totalImages) {
        std::cerr << "Error: Invalid range specified (startIdx + count exceeds total images)." << std::endl;
        return false;
    }

    textures_.resize(cof.indexcount);  // 必要な分だけポインタ配列をリサイズ

    // Bmp* 配列を作成
    Bmp** emptyBmp = new Bmp * [totalImages];  // LoadDivBmpで使うために空の配列を作成

    if (!LoadDivBmp(path.c_str(), 0, 0, cof.width, cof.height, cof.rows, cof.columns, emptyBmp)) {
        // ロードに失敗した場合
        std::cerr << "Error: Failed to load texture: " << path.c_str() << std::endl;  // エラーコードを出す
        delete[] emptyBmp;  // メモリリークを防ぐために配列を解放
        return false;       // 失敗
    }

    // 指定された範囲の内容を textures_ に移動
    for (int i = 0; i < cof.indexcount; ++i) {
        textures_[i] = std::unique_ptr<Bmp>(emptyBmp[cof.startindex+ i]);  // 生ポインタを unique_ptr に変換して格納
    }

    // emptyBmp 配列自体を解放
    delete[] emptyBmp;

    return true;
}

//===============================================================================================
//                    分割した画像をindexを指定してその範囲を取得する
// 
// 引数１で取得する取得を開始するindexを指定する
// 引数２で引数１からどれだけの数のindexを取得する
//===============================================================================================
inline std::vector<std::unique_ptr<Bmp>> GameTexture::GetTexturesInRange(int startIndex, int count = 0) const {
    // 範囲の検証
    if (startIndex < 0 || startIndex >= textures_.size()) {
        std::cerr << "Error: Invalid startIndex: " << startIndex << std::endl;
        return {};
    }

    // 取得範囲がtextures_のサイズを超えないように調整
    int endIndex = (std::min)(static_cast<int>(textures_.size()), startIndex + count);

    std::vector<std::unique_ptr<Bmp>> result;
    for (int i = startIndex; i < endIndex; ++i) {
        // textures_の内容をコピーして新しいunique_ptrにする
        result.push_back(std::make_unique<Bmp>(*textures_[i]));
    }

    return result;
}


#endif //GAMETEXTURE_H