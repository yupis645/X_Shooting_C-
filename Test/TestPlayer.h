
#ifndef TESTPLAYER_H
#define TESTPLAYER_H

class IInputManager;
class GameTexture;
class DebugManager;
class DIContainer;
class Vetcor2;

#include "Player.h"


class TestPlayer : public Player {
public:
    // �R���X�g���N�^�ƃf�X�g���N�^
    TestPlayer(std::shared_ptr<DIContainer> con);

    // �����o�֐��̎���
    int Init() override;                                // ������
    int Update(int framecount, Vector2 moveinput) override; // �X�V����
    int Draw() override;                  // �`�揈��

    // �����Ɋւ���֐�
    int Move(Vector2 move) override;
    int Sync_PositionAndHitbox() override;
    int AnimationUpdate() override;

    ~TestPlayer() = default;

private:
    std::shared_ptr<DebugManager> debug_;
};


#endif // TESTPLAYER_H
