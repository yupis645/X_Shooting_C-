#ifndef TESTGAMESCENE_H
#define TESTGAMESCENE_H


class DIContainer;
class DebugManager;
class TestInputManager;
class TestBulletsManager;
class TestEnemysManager;
class TestPlayer;


#include "GameScene.h"
#include "TestInputManager.h"



class TestGameScene : public GameScene {
public:
    TestGameScene(std::shared_ptr<DIContainer> con);

    int Init()override;

    // XVˆ—
    int Update()override;

    // •`‰æˆ—
    int Draw() override;

    void DebugCreateEnemy();

    ~TestGameScene() = default;

private:
    std::shared_ptr<DebugManager> debug_;
    std::shared_ptr<TestInputManager> testinput_;
    std::shared_ptr<TestEnemysManager> testenemys_;
    std::shared_ptr<TestBulletsManager> testbullets_;
    std::shared_ptr<TestPlayer> testplayer_;


    int createA_enemynumber;
    int createG_enemynumber;

};

#endif // TESTGAMESCENE_H

