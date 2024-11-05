#include "GameTexture.h"
#include "pch.h"

using namespace DirectX;


//===============================================================================================
//                              画像のロード
// 
// 引数で受けった情報をもとに画像をスライスする。
// UseTextureDataConfigには[画像のファイルパス、スライスする画像サイズ、行数、列数]がパックされている
//===============================================================================================
bool GameTexture::SliceTexture(const std::wstring& path, TextureConfig cof) {
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
        textures_[i] = std::unique_ptr<Bmp>(emptyBmp[cof.startindex + i]);  // 生ポインタを unique_ptr に変換して格納
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
std::vector<std::unique_ptr<Bmp>> GameTexture::GetTexturesInRange(int startIndex, int count = 0) const {
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

Textures GameTexture::TextureSet(const wchar_t* textureFilePath)
{
    Textures textures;
    textures.Sprite = std::make_unique<SpriteBatch>(m_d3dContext.Get());      // 2Dスプライトを描写するクラスのオブジェクトを生成
    ComPtr<ID3D11Resource> resource;        // リソースを生成
    DX::ThrowIfFailed(
        CreateWICTextureFromFile(m_d3dDevice.Get(), textureFilePath, resource.GetAddressOf(), textures.SRV.ReleaseAndGetAddressOf())
    );          // ファイルからテクスチャを読み込む

    return textures;
}

void GameTexture::SplitTexture(const Textures& textures, int spriteWidth, int spriteHeight)
{
    ComPtr<ID3D11Resource> resource;
    DX::ThrowIfFailed(textures.SRV->GetResource(&resource));

    ComPtr<ID3D11Texture2D> texture;
    DX::ThrowIfFailed(resource.As(&texture));

    CD3D11_TEXTURE2D_DESC textureDesc;
    texture->GetDesc(&textureDesc);             // テクスチャの詳細情報を取得

    int numSpritesX = textureDesc.Width / spriteWidth;
    int numSpritesY = textureDesc.Height / spriteHeight;

    for (int y = 0; y < numSpritesY; ++y) {
        for (int x = 0; x < numSpritesX; ++x) {
            RECT sourceRect = { x * spriteWidth, y * spriteHeight, (x + 1) * spriteWidth, (y + 1) * spriteHeight };

            // スプライトごとに `Textures` インスタンスを作成し、テクスチャ情報を格納
            auto spriteTextures = std::make_unique<Textures>();
            spriteTextures->Sprite = std::make_unique<SpriteBatch>(m_d3dContext.Get());
            spriteTextures->SRV = textures.SRV;  // 同じシェーダーリソースビューを共有

            tex.push_back(std::move(spriteTextures));  // `tex` ベクターに格納
        }
    }
}