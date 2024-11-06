#ifndef TEXTUREDATAMANAGER_H
#define TEXTUREDATAMANAGER_H

class GameTexture;

class TextureManager {
public:
    TextureManager(){}


    bool LoadTextureBase(TextureBaseName type, const wchar_t* textureFilePath, ComPtr<ID3D11Device1> device, ComPtr<ID3D11DeviceContext1> deviceContext);


    bool SplitTexture(SpriteName name,ComPtr<ID3D11DeviceContext1> deviceContext);

    const std::vector<std::unique_ptr<Textures>>& GetSpriteTextures(SpriteName name) const {
        return sprites.at(name); // �Y������X�v���C�g���Q�ƂŕԂ�
    }

    const Textures* GetSpriteTextureAtIndex(SpriteName name, int index) const {
        const auto& textures = sprites.at(name);
        if (index >= 0 && index < textures.size()) {
            return textures[index].get(); // `unique_ptr` �̏��L�����ڂ����Ƀ|�C���^��Ԃ�
        }
        return nullptr; // �����ȃC���f�b�N�X�̏ꍇ�� `nullptr`
    }

    const Textures* GetSprite(TextureType type, int index) const;



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
    std::map<TextureBaseName, std::unique_ptr<Textures>> basetexture;
  
    std::map<SpriteName, std::vector<std::unique_ptr<Textures>>> sprites;     // SpriteName���L�[�ɕ����e�N�X�`�����Ǘ�����map

    std::map<TextureType, std::shared_ptr<GameTexture>> textures_;      // TextureType ���L�[�ɂ��� GameTexture ���Ǘ�����}�b�v

};


#endif //TEXTUREMANAGER_H
