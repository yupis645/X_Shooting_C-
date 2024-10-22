#ifndef GAMESCENE_H
#define GAMESCENE_H

class DIContainer;

#include "Game.h"
#include "DIContainer.h"
#include "di.hpp"
#include "SceneBase.h"
#include "IInputManager.h"
#include "ResourceManager.h"


class GameScene : public SceneBase {
public:
    GameScene(std::shared_ptr<DIContainer> con);


    int Init()override;

    // �X�V����
    int Update()override;

    // �`�揈��
    int Draw() override;

    ~GameScene() override {
        // �I�������i���\�[�X����Ȃǁj
    }
private:
    std::shared_ptr<DIContainer> container_;  // Player �N���X�ւ̈ˑ�
    std::shared_ptr<GameStatus> gamestatus_;  // Player �N���X�ւ̈ˑ�
    std::shared_ptr<IMapManager>mapmanager_;
    std::shared_ptr<IInputManager>inputmanager_;
    std::shared_ptr<ResourceManager>resourcemanager_;


};

#endif // GAMESCENE_H