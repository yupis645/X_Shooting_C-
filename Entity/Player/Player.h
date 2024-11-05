#ifndef PLAYER_H
#define PLAYER_H

class IInputManager;
class GameTexture;
class SpriteRenderer;
class ResourceManager;

#include "IPlayer.h"

#include "Game.h"
#include "Geometry.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"

class Player : public GameObject, public IPlayer {
public:
    // �R���X�g���N�^�ƃf�X�g���N�^
    Player(std::shared_ptr<ResourceManager> rm, std::shared_ptr<SpriteRenderer> render, std::shared_ptr<IInputManager> input);

    // �����o�֐��̎���
    int Init() override;                                // ������
    int Update(int framecount, Vector2 moveinput) override; // �X�V����
    int Draw() override;                  // �`�揈��

    // �����Ɋւ���֐�
    int Move(Vector2 move) override;
    int Sync_PositionAndHitbox() override;
    int AnimationUpdate() override;

    void InitClear() override { GameObject::InitClear(); }

    void HitCollision(bool isshootdown) override;

    // �v���p�e�B & getter / setter
    bool Getshootdown() const override { return shootdown; }
    

    Vector2 GetPosition() const override { return GameObject::GetPosition(); }
    void SetPosition(Vector2 pos) override { GameObject::SetPosition(pos); }

    Boxcollider GetHitbox() const override { return GameObject::GetHitbox(); }
    void SetHitbox(Boxcollider box) override { GameObject::SetHitbox(box); }

    bool GetActive() override { return GameObject::GetActive(); }
    void SetActive(bool isactive) override { GameObject::SetActive(isactive); }

    ~Player() = default;

private:
    class Targetsight {
    public:
        Targetsight(Player& player, std::shared_ptr<ResourceManager> rm)
            : player_(player), enemyhit(false), position({ 0, 0 }), hitbox(0, 0, 0, 0)
        {
            // ResourceManager���g�p���ăe�N�X�`����������
            texture = rm->GetTexture(TextureType::Targetsight);
        }

        ~Targetsight() {}

        void Init() {
            position = player_.GetPosition();
            position.y -= PlayerConfig::BOM_RANGE;
            hitbox = Boxcollider::zero;
            enemyhit = false;
        }

        void Update() {
            position = player_.GetPosition();
            position.y -= PlayerConfig::BOM_RANGE;

        }

        void hitboxsync(Vector2 position) {
            hitbox.CenterPositionSync(position, PlayerConfig::SIGHT_HITBOX_SIZE);

        }

        void LookonEnemy(Boxcollider enemyhitbox) {
            enemyhit = hitbox.BoxCollision(enemyhitbox);
        }

        void Draw() {
            int anim = enemyhit ? 1 : 0;
            if (player_.render_ && texture) {
                player_.render_->DrawFromCenterPos(texture, anim, static_cast<int>(position.x), static_cast<int>(position.y), PlayerConfig::SIGHT_PIC_SIZE);
            }
        }

    private:
        Player& player_;  // Player�N���X�ւ̎Q��
        bool enemyhit;
        Vector2 position;
        Boxcollider hitbox;
        std::shared_ptr<GameTexture> texture; // �}�b�v�`�b�v�̉摜��ۊǂ��Ă����ϐ�
    };

private:
    int anim;
    int pat;
    bool shootdown;
    int ownframecount;
    std::unique_ptr<Targetsight> targetsight; 

    std::shared_ptr<IInputManager> input_;
    std::shared_ptr<GameTexture> texture;
    std::shared_ptr<SpriteRenderer> render_;
};


#endif // PLAYER_H