#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

class DIContainer;
class GameStatus;
class Scenestatus;
class IInputManager;
class ResourceManager;
class GameTextureManager;
class SceneBase;

#include "Game.h"
#include "di.hpp"
#include "IGameManager.h"
#include "SceneBase.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "IInputManager.h"
#include "ResourceManager.h"
#include "DIContainer.h"
#include "common.h"


class GameManager :public IGameManager {
public:
    GameManager(std::shared_ptr<DIContainer> con)
        : container_(con),
        scenestatus_(con->Create<Scenestatus>()),
        gamestatus_(con->Create<GameStatus>()),
       inputmanager_(con->Create<IInputManager>()) ,
       resourcemanager_(con->Create<ResourceManager>())
    {
        currentscene_ = std::make_shared<TitleScene>(container_, scenestatus_, gamestatus_, inputmanager_,resourcemanager_);
    }

    // �e���v���[�g�֐��ŃV�[���𐶐����Đ؂�ւ�
    template <typename SceneType>
    void SwitchToScene() {
        currentscene_ = std::make_shared<SceneType>( container_, scenestatus_, gamestatus_, inputmanager_, resourcemanager_);
    }

    int Init()override;

    int Input()override;

    // �V�[���̍X�V�ƕ`��
    int Update()override;

    int Draw()override;

    // �V�[���̏I������
    int End()override;

    //�f�X�g���N�^
    ~GameManager() {}

private:
    std::shared_ptr<DIContainer> container_;  // Di�R���e�i
    std::shared_ptr<GameStatus> gamestatus_;  // �Q�[���֘A�̃X�e�[�^�X
    std::shared_ptr<Scenestatus> scenestatus_;  // �V�[���Ɋւ���X�e�[�^�X
    std::shared_ptr<IInputManager> inputmanager_;  // ���͊֌W
    std::shared_ptr<ResourceManager> resourcemanager_;  // �摜��CSV�t�@�C���Ȃǂ��Ǘ�����N���X
    std::shared_ptr<SceneBase> currentscene_;  // ���݂̃V�[��

    //int ChangeScene(std::shared_ptr<SceneBase> newScene);
};

#endif // GAMEMANAGER_H
