#ifndef PLAYER_H
#define PLAYER_H

#include "Game.h"
#include "common.h"
#include "IPlayer.h"
#include "Geometry.h"
#include "conioex.h"
#include "GameTexture.h"
#include "ResourceManager.h"

class Targetsight{
public :
    Targetsight() : enemyhit(false), position({0,0}), hitbox(0, 0, 0, 0) {}
    ~Targetsight(){}

    void Init() {
        hitbox = Boxcollider::zero;
        enemyhit = false;
    }

    void hitboxsync(Vector2 position) {
        hitbox.CenterPositionSync(position, PlayerConfig::SIGHT_HITBOX_SIZE);

    }

    void LookonEnemy(Boxcollider enemyhitbox) {
        enemyhit = hitbox.BoxCollision(enemyhitbox);
    }

    void Draw() {
        // 照準器が地上の敵と被っている場合、アニメーション番号を変更
        int anim = enemyhit ? 1 : 0;

        /* 照準の描写 */
        texture->DrawFromCenterPos(anim, (int)position.x, (int)position.y, PlayerConfig::SIGHT_PIC_SIZE);
    }
private:
    bool enemyhit;
    Vector2 position;
    Boxcollider hitbox;           // 照準の当たり判定
    std::shared_ptr<GameTexture> texture;       //マップチップの画像を保管しておく変数
};

class Player : public GameObject, public IPlayer {
public:

    // コンストラクタとデストラクタ
    Player(std::shared_ptr<ResourceManager> rm) ;
    ~Player();

    // メンバ関数の実装
    int Init() override;                                // 初期化
    int Create()override;                              // プレイヤーを作成
    int Update(int framecount, Vector2 moveinput)override; // 更新処理
    int Draw()override;                  // 描画処理


    //動きに関する関数
    int Move(Vector2 move) override;
    int Sync_PositionAndHitbox() override;
    int AnimationUpdate() override;

    void InitClear()override { GameObject::InitClear(); }

    //プロパティ & getter / setter

    bool Getshootdown() const override { return shootdown; }
    void Setshootdown(bool isshootdown) override{ shootdown = isshootdown; }


    Vector2 GetPosition()const override { return GameObject::GetPosition(); }
    void SetPosition(Vector2 pos) override { GameObject::SetPosition(pos); }

    Boxcollider GetHitbox()const override { return GameObject::GetHitbox(); }
    void SetHitbox(Boxcollider box) override { GameObject::SetHitbox(box); }

    bool GetActive() override { return GameObject::GetActive(); }
    void SetActive(bool isactive) override { GameObject::SetActive(isactive); }


protected:
    Targetsight sight;          //照準器
    int anim;                    // アニメーションパターンの切り替えタイミング
    int pat;                     // アニメーションパターン番号
    bool shootdown;                    // 被弾判定
    std::shared_ptr<GameTexture> texture;       //マップチップの画像を保管しておく変数
    int ownframecount;
};

#endif // PLAYER_H