#ifndef TEXTUREDATAMANAGER_H
#define TEXTUREDATAMANAGER_H

class GameTexture;

class TextureManager {
public:
    TextureManager() {
    }

    void SetTexConfig(TextureType type, const TextureConfig& config) {
        texdatacongfig[type] = config;  // データを更新
    }
    const TextureConfig& GetTextureConfig(TextureType type) const {
        return texdatacongfig.at(type);
    }

    void SetBaseTexture(TextureType type, std::unique_ptr<Textures> tex) {
        basetexture[type] = std::move(tex);  // 所有権を移動
    }

    bool LoadTextureBase(TextureBaseName type, const wchar_t* textureFilePath, ComPtr<ID3D11Device1> device, ComPtr<ID3D11DeviceContext1> deviceContext);


    bool SplitTexture(SpriteName name,ComPtr<ID3D11DeviceContext1> deviceContext);


    const Textures& GetBaseTexture(TextureType type) const {
        return *(basetexture.at(type));
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
    ~TextureManager() {}


private:
    std::map<TextureType, TextureConfig> texdatacongfig;
    std::map<TextureBaseName, std::unique_ptr<Textures>> basetexture;
    std::map<SpriteName, std::unique_ptr<Textures>> sprites;

    std::map<TextureType, std::shared_ptr<GameTexture>> textures_;      // TextureType をキーにして GameTexture を管理するマップ

};


#endif //TEXTUREMANAGER_H
