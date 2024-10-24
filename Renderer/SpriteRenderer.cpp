#include "SpriteRenderer.h"

#include "Game.h"
#include "conioex.h"
#include "GameTexture.h"
#include "ResourceManager.h"
#include "Geometry.h"

namespace {
    //==========================================================================================
    //指定されたindexが範囲内にあるかチェック
    //==========================================================================================
    Bmp* IndexOverCheak(const std::shared_ptr<const GameTexture>& texture, int index, int x, int y) {
        if (index < 0 || index >= texture->GetTextures().size()) {
            std::cerr << "Error: Invalid texture index: " << index << std::endl;
            return nullptr;
        }

        return texture->GetTextureIndex(index); // テクスチャの取得
    }
}
//==========================================================================================
//                  コンストラクタ
//==========================================================================================
SpriteRenderer::SpriteRenderer(std::shared_ptr<ResourceManager> rm)
{
    bomber = rm->GetTexture(TextureType::PlayerBomber);
    airenemybomber= rm->GetTexture(TextureType::Air_EnemyBomber);
}

//==========================================================================================
//                  左上座標を起点に画像を描画する
//==========================================================================================
bool SpriteRenderer::DrawFromTopLeftPos(const std::shared_ptr<const GameTexture>&  texture, int index, int x, int y) const {
    Bmp* texture_convert_bmp = IndexOverCheak(texture, index, x, y);

    if (texture_convert_bmp == nullptr) return true;        //変換失敗なのでここで処理を終える

    DrawBmp(static_cast<int>(x), static_cast<int>(y), texture_convert_bmp);

    return false;
}

/// <summary>
///  左上座標を起点に画像を描画する(オーバーロード)
/// </summary>
/// <param name="texture"></param>
/// <param name="index"></param>
/// <param name="pos"></param>
/// <returns></returns>
bool SpriteRenderer::DrawFromTopLeftPos(const std::shared_ptr<const GameTexture>&  texture, int index, Vector2 pos) const {
    return DrawFromTopLeftPos(texture, index, static_cast<int>(pos.x), static_cast<int>(pos.y));
}

//==========================================================================================
//                  中心座標を起点に画像を描画する
//==========================================================================================
bool SpriteRenderer::DrawFromCenterPos(const std::shared_ptr<const GameTexture>& texture, int index, int x, int y, int pic_size) const {
    Bmp* texture_convert_bmp = IndexOverCheak(texture, index, x, y);

    if (texture_convert_bmp == nullptr) return true;        //変換失敗なのでここで処理を終える

    int lefttop_x = x - (pic_size / 2) + 1;
    int lefttop_y = y - (pic_size / 2) + 1;

    DrawBmp(static_cast<int>(lefttop_x), static_cast<int>(lefttop_y), texture_convert_bmp);

    return false;
}
/// <summary>
/// 中心座標を起点に画像を描画する(オーバーロード)
/// </summary>
/// <param name="texture"></param>
/// <param name="index"></param>
/// <param name="pos"></param>
/// <param name="pic_size"></param>
/// <returns></returns>
bool SpriteRenderer::DrawFromCenterPos(const std::shared_ptr<const GameTexture>& texture, int index, Vector2 pos, int pic_size) const {
    return DrawFromCenterPos(texture, index, static_cast<int>(pos.x), static_cast<int>(pos.y),pic_size);
}

//==========================================================================================
//                  左上座標を起点に爆発を描画する
// 
// typeによって汎用的な爆発と空中敵の爆発を使い分ける
//==========================================================================================
bool SpriteRenderer::DrawBomberFromTopLeftPos(BomberType tex,int index, int x, int y) const{
    Bmp* texture_convert_bmp = nullptr;
    if (tex == BomberType::bomber) {
        texture_convert_bmp = IndexOverCheak(bomber, index, x, y);
    }
    else if (tex == BomberType::airenemybomber) {
        texture_convert_bmp = IndexOverCheak(airenemybomber, index, x, y);
    }

    if (texture_convert_bmp == nullptr) return true;        //変換失敗なのでここで処理を終える

    DrawBmp(static_cast<int>(x), static_cast<int>(y), texture_convert_bmp);

    return false;
}

/// <summary>
/// 左上座標を起点に爆発を描画する(オーバーロード)
/// </summary>
/// <param name="tex"></param>
/// <param name="index"></param>
/// <param name="pos"></param>
/// <returns></returns>
bool SpriteRenderer::DrawBomberFromTopLeftPos(BomberType tex,int index, Vector2 pos) const{
    return DrawBomberFromTopLeftPos(tex, index, static_cast<int>(pos.x), static_cast<int>(pos.y));
}


//==========================================================================================
//                  中心座標を起点に爆発を描画する
// 
// typeによって汎用的な爆発と空中敵の爆発を使い分ける
//==========================================================================================
bool SpriteRenderer::DrawBomberFromCenterPos(BomberType tex,int index, int x, int y) const{
    

    Bmp* texture_convert_bmp = nullptr;
    if (tex == BomberType::bomber) {
        texture_convert_bmp = IndexOverCheak(bomber, index, x, y);
    }
    else if (tex == BomberType::airenemybomber) {
        texture_convert_bmp = IndexOverCheak(airenemybomber, index, x, y);
    }

    if (texture_convert_bmp == nullptr) return true;        //変換失敗なのでここで処理を終える

    int lefttop_x = x - (BOMBER_PIC_SIZE / 2) + 1;
    int lefttop_y = y - (BOMBER_PIC_SIZE / 2) + 1;

    DrawBmp(static_cast<int>(lefttop_x), static_cast<int>(lefttop_y), texture_convert_bmp);

    return false;
}

/// <summary>
/// 中心座標を起点に爆発を描画する(オーバーロード)
/// </summary>
/// <param name="tex"></param>
/// <param name="index"></param>
/// <param name="pos"></param>
/// <returns></returns>
bool SpriteRenderer::DrawBomberFromCenterPos(BomberType tex,int index,Vector2 pos) const{
    return DrawBomberFromCenterPos(tex, index, static_cast<int>(pos.x), static_cast<int>(pos.y));
}
