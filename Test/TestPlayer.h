
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
    // コンストラクタとデストラクタ
    TestPlayer(std::shared_ptr<DIContainer> con);

    // メンバ関数の実装
    int Init() override;                                // 初期化
    int Update(int framecount, Vector2 moveinput) override; // 更新処理
    int Draw() override;                  // 描画処理

    // 動きに関する関数
    int Move(Vector2 move) override;
    int Sync_PositionAndHitbox() override;
    int AnimationUpdate() override;

    ~TestPlayer() = default;

private:
    std::shared_ptr<DebugManager> debug_;
};


#endif // TESTPLAYER_H
