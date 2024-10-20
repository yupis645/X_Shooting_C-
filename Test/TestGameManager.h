#ifndef TESTGAMEMANAGER_H
#define TESTGAMEMANAGER_H

#include "Game.h"
#include "di.hpp"
#include "IGameManager.h"
#include "SceneBase.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "IInputManager.h"
#include "DIContainer.h"
#include "ResourceManager.h"
#include "common.h"

#include "TestScene.h"

class TestGameManager : public IGameManager{
public:
    TestGameManager(std::shared_ptr<DIContainer> con)
        : container_(con),
        scenestatus_(con->Create<Scenestatus>()),
        gamestatus_(con->Create<GameStatus>()),
        resoucemanager_(con->Create<ResourceManager>()),
        inputmanager_(con->Create<IInputManager>())
    {
        currentscene_ = std::make_shared<TestScene>(con,scenestatus_, gamestatus_, resoucemanager_,inputmanager_);
    }

    int Init()override;

    int Input()override;

    // �V�[���̍X�V�ƕ`��
    int Update() override;

    int Draw()override;

    // �V�[���̏I������
    int End()override;

    //�f�X�g���N�^
    ~TestGameManager() {}

private:
    std::shared_ptr<SceneBase> currentscene_;  // ���݂̃V�[��
    std::shared_ptr<GameStatus> gamestatus_;  // ���݂̃V�[��
    std::shared_ptr<Scenestatus> scenestatus_;  // ���݂̃V�[��
    std::shared_ptr<ResourceManager> resoucemanager_;  // ���݂̃V�[��
    std::shared_ptr<IInputManager> inputmanager_;  // ���݂̃V�[��
    std::shared_ptr<DIContainer> container_;  // DIContainer �̃����o�ϐ�

    //int ChangeScene(std::shared_ptr<SceneBase> newScene);
};

#endif ///ESTGAMEMANAGER_H
