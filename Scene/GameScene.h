#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Game.h"
#include "di.hpp"
#include "DIContainer.h"
#include "SceneBase.h"
//#include "Player.h"
#include "IInputManager.h"
#include "ResourceManager.h"
//#include "EnemysManager.h"
//#include "BulletManager.h"
//#include "MapManager.h"

class GameScene : public SceneBase {
public:
    GameScene(std::shared_ptr<DIContainer> con,std::shared_ptr<Scenestatus> ss, std::shared_ptr<GameStatus> gs, std::shared_ptr<IInputManager> input, std::shared_ptr<ResourceManager> rm);

    // ����������
    int Init() override;

    // �X�V����
    int Update() override;

    // �`�揈��
    int Draw() override;

    ~GameScene() override {
        // �I�������i���\�[�X����Ȃǁj
    }
private:
    std::shared_ptr<DIContainer> container_;  // Player �N���X�ւ̈ˑ�
    std::shared_ptr<Scenestatus> scenestatus_;  // Player �N���X�ւ̈ˑ�
    std::shared_ptr<GameStatus> gamestatus_;  // Player �N���X�ւ̈ˑ�
    //std::shared_ptr<IPlayer> player_;  // Player �N���X�ւ̈ˑ�
    //std::shared_ptr<IEnemysManager> enemymanager_;
    //std::shared_ptr<IBulletManager>bulletmanager_;
    std::shared_ptr<IMapManager>mapmanager_;
    std::shared_ptr<IInputManager>inputmanager_;
    std::shared_ptr<ResourceManager>resourcemanager_;
};

#endif // GAMESCENE_H