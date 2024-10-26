#ifndef GAMESCENE_H
#define GAMESCENE_H


class DIContainer;
class GameSceneFactory;
class IPlayer;
class GameStatus;
class IMapManager;
class IInputManager;
class ResourceManager;
class IBulletsManager;
class IEnemysManager;

#include <iostream>
#include "SceneBase.h"



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

protected:
    std::shared_ptr<IPlayer> GetPlayer() { return player_; }
    std::shared_ptr<IBulletsManager> GetBullets() { return bullets_; }
    std::shared_ptr<IMapManager> GetMaps() { return mapmanager_; }
    std::shared_ptr<IEnemysManager> GetEnemys() { return enemys_; }

private:
    std::shared_ptr<IPlayer> player_;  // Player �N���X�ւ̈ˑ�
    std::shared_ptr<IBulletsManager> bullets_;  // Player �N���X�ւ̈ˑ�
    std::shared_ptr<IMapManager> mapmanager_;
    std::shared_ptr<IEnemysManager> enemys_;

    std::shared_ptr<DIContainer> container_;  // Player �N���X�ւ̈ˑ�
    std::shared_ptr<GameStatus> gamestatus_;  // Player �N���X�ւ̈ˑ�
    std::shared_ptr<IInputManager>input_;
    std::shared_ptr<ResourceManager>resourcemanager_;
    std::shared_ptr<GameSceneFactory>instanceFactory_;


};

#endif // GAMESCENE_H