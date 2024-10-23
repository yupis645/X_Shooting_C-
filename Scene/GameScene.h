#ifndef GAMESCENE_H
#define GAMESCENE_H

class GameSceneFactory;
class DIContainer;


#include "Game.h"
#include "DIContainer.h"
#include "SceneBase.h"
#include "IMapManager.h"
#include "IInputManager.h"
#include "ResourceManager.h"
#include "GameSceneFactory.h"
#include "IPlayer.h"


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
    std::shared_ptr<IPlayer> player_;  // Player �N���X�ւ̈ˑ�
    std::shared_ptr<DIContainer> container_;  // Player �N���X�ւ̈ˑ�
    std::shared_ptr<GameStatus> gamestatus_;  // Player �N���X�ւ̈ˑ�
    std::shared_ptr<IMapManager>mapmanager_;
    std::shared_ptr<IInputManager>inputmanager_;
    std::shared_ptr<ResourceManager>resourcemanager_;
    std::shared_ptr<GameSceneFactory>instanceFactory_;


};

#endif // GAMESCENE_H