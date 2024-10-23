#include "SpriteRenderer.h"
#include "conioex.h"


void SpriteRenderer::DrawFromTopLeftPos(const std::shared_ptr<const GameTexture>&  texture, int index, int x, int y) const {
    // テクスチャの範囲チェック
    if (index < 0 || index >= texture->GetTextures().size()) {
        int s = texture->GetTextures().size();
        std::cerr << "Error: Invalid texture index: " << index << std::endl;
        return;
    }

    Bmp* texture_convert_bmp = texture->GetTextureIndex(index); // テクスチャの取得
    DrawBmp(x, y, texture_convert_bmp);
}

void SpriteRenderer::DrawFromCenterPos(const std::shared_ptr<const GameTexture>& texture, int index, int x, int y, int pic_size) const {
    if (index < 0 || index >= texture->GetTextures().size()) {
        std::cerr << "Error: Invalid texture index: " << index << std::endl;
        return;
    }

    Bmp* texture_convert_bmp = texture->GetTextureIndex(index);
    int lefttop_x = x - (pic_size / 2);
    int lefttop_y = y - (pic_size / 2);
    DrawBmp(lefttop_x, lefttop_y, texture_convert_bmp);
}