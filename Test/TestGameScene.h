#ifndef TESTGAMESCENE_H
#define TESTGAMESCENE_H


class DIContainer;
class DebugManager;
class TestInputManager;

#include <iostream>
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

    ~TestGameScene() = default;

private:
    std::shared_ptr<DebugManager> debug_;
    std::shared_ptr<TestInputManager> testinput_;

};

#endif // TESTGAMESCENE_H

