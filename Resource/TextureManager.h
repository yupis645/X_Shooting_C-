#ifndef TEXTUREDATAMANAGER_H
#define TEXTUREDATAMANAGER_H

class GameTexture;

class TextureManager {
public:
    TextureManager(){}


    bool LoadTextureBase(TextureBaseName type, const wchar_t* textureFilePath, ComPtr<ID3D11Device1> device, ComPtr<ID3D11DeviceContext1> deviceContext);


    bool SplitTexture(SpriteName name,ComPtr<ID3D11DeviceContext1> deviceContext);

    const std::vector<std::unique_ptr<Textures>>& GetSpriteTextures(SpriteName name) const {
        return sprites.at(name); // 該当するスプライトを参照で返す
    }

    const Textures* GetSpriteTextureAtIndex(SpriteName name, int index) const {
        const auto& textures = sprites.at(name);
        if (index >= 0 && index < textures.size()) {
            return textures[index].get(); // `unique_ptr` の所有権を移さずにポインタを返す
        }
        return nullptr; // 無効なインデックスの場合は `nullptr`
    }

    const Textures* GetSprite(TextureType type, int index) const;



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
    ~TextureManager() {}
private:
    std::map<TextureBaseName, std::unique_ptr<Textures>> basetexture;
  
    std::map<SpriteName, std::vector<std::unique_ptr<Textures>>> sprites;     // SpriteNameをキーに分割テクスチャを管理するmap

    std::map<TextureType, std::shared_ptr<GameTexture>> textures_;      // TextureType をキーにして GameTexture を管理するマップ

};


#endif //TEXTUREMANAGER_H
