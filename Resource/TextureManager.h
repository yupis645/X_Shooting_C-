#ifndef TEXTUREDATAMANAGER_H
#define TEXTUREDATAMANAGER_H

class GameTexture;

class TextureManager {
public:
    TextureManager() {
    }

    void SetTexConfig(TextureType type, const TextureConfig& config) {
        texdatacongfig[type] = config;  // �f�[�^���X�V
    }
    const TextureConfig& GetTextureConfig(TextureType type) const {
        return texdatacongfig.at(type);
    }

    void SetBaseTexture(TextureType type, std::unique_ptr<Textures> tex) {
        basetexture[type] = std::move(tex);  // ���L�����ړ�
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
  //png�f�[�^�ƃT�C�Y�Ȃǂ̏����󂯂Ƃ�A�摜���X���C�X���ă����o�ϐ��Ɋi�[����
  //=======================================================================================
    bool CreateGameTexture(TextureType type, const std::wstring&, TextureConfig config);

    //=======================================================================================
    // �C�ӂ� GameTexture ��`�悷�鋤�ʊ֐�
    //=======================================================================================
    std::shared_ptr<GameTexture> GetTexture(TextureType type);

    //getter
    const std::map<TextureType, std::shared_ptr<GameTexture>>& GetAllTexture() const { return textures_; }

    //=======================================================================================
    //                          �f�X�g���N�^
    //=======================================================================================
    ~TextureManager() {}


private:
    std::map<TextureType, TextureConfig> texdatacongfig;
    std::map<TextureBaseName, std::unique_ptr<Textures>> basetexture;
    std::map<SpriteName, std::unique_ptr<Textures>> sprites;

    std::map<TextureType, std::shared_ptr<GameTexture>> textures_;      // TextureType ���L�[�ɂ��� GameTexture ���Ǘ�����}�b�v

};


#endif //TEXTUREMANAGER_H
