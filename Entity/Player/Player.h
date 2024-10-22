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
        // �Ə��킪�n��̓G�Ɣ���Ă���ꍇ�A�A�j���[�V�����ԍ���ύX
        int anim = enemyhit ? 1 : 0;

        /* �Ə��̕`�� */
        texture->DrawFromCenterPos(anim, (int)position.x, (int)position.y, PlayerConfig::SIGHT_PIC_SIZE);
    }
private:
    bool enemyhit;
    Vector2 position;
    Boxcollider hitbox;           // �Ə��̓����蔻��
    std::shared_ptr<GameTexture> texture;       //�}�b�v�`�b�v�̉摜��ۊǂ��Ă����ϐ�
};

class Player : public GameObject, public IPlayer {
public:

    // �R���X�g���N�^�ƃf�X�g���N�^
    Player(std::shared_ptr<ResourceManager> rm) ;
    ~Player();

    // �����o�֐��̎���
    int Init() override;                                // ������
    int Create()override;                              // �v���C���[���쐬
    int Update(int framecount, Vector2 moveinput)override; // �X�V����
    int Draw()override;                  // �`�揈��


    //�����Ɋւ���֐�
    int Move(Vector2 move) override;
    int Sync_PositionAndHitbox() override;
    int AnimationUpdate() override;

    void InitClear()override { GameObject::InitClear(); }

    //�v���p�e�B & getter / setter

    bool Getshootdown() const override { return shootdown; }
    void Setshootdown(bool isshootdown) override{ shootdown = isshootdown; }


    Vector2 GetPosition()const override { return GameObject::GetPosition(); }
    void SetPosition(Vector2 pos) override { GameObject::SetPosition(pos); }

    Boxcollider GetHitbox()const override { return GameObject::GetHitbox(); }
    void SetHitbox(Boxcollider box) override { GameObject::SetHitbox(box); }

    bool GetActive() override { return GameObject::GetActive(); }
    void SetActive(bool isactive) override { GameObject::SetActive(isactive); }


protected:
    Targetsight sight;          //�Ə���
    int anim;                    // �A�j���[�V�����p�^�[���̐؂�ւ��^�C�~���O
    int pat;                     // �A�j���[�V�����p�^�[���ԍ�
    bool shootdown;                    // ��e����
    std::shared_ptr<GameTexture> texture;       //�}�b�v�`�b�v�̉摜��ۊǂ��Ă����ϐ�
    int ownframecount;
};

#endif // PLAYER_H