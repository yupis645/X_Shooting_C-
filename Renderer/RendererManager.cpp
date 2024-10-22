#include "RendererManager.h"
#include "conioex.h"


void RendererManager::DrawFromTopLeftPos(const std::shared_ptr<const GameTexture>&  texture, int index, int x, int y) const {
    // �e�N�X�`���͈̔̓`�F�b�N
    if (index < 0 || index >= texture->GetTextures().size()) {
        std::cerr << "Error: Invalid texture index: " << index << std::endl;
        return;
    }

    Bmp* texture_convert_bmp = texture->GetTextureIndex(index); // �e�N�X�`���̎擾
    DrawBmp(x, y, texture_convert_bmp);
}

void RendererManager::DrawFromCenterPos(const std::shared_ptr<const GameTexture>& texture, int index, int x, int y, int pic_size) const {
    if (index < 0 || index >= texture->GetTextures().size()) {
        std::cerr << "Error: Invalid texture index: " << index << std::endl;
        return;
    }

    Bmp* texture_convert_bmp = texture->GetTextureIndex(index);
    int lefttop_x = x - (pic_size / 2);
    int lefttop_y = y - (pic_size / 2);
    DrawBmp(lefttop_x, lefttop_y, texture_convert_bmp);
}