#ifndef TESTSCENE_H
#define TESTSCENE_H

class DIContainer;
class GameStatus;
class IInputManager;
class ResourceManager;
class SpriteRenderer;
class IMapManager;

#include "SceneBase.h"


class TestScene : public SceneBase {
public:
    TestScene(std::shared_ptr<DIContainer> container);

    int Init()override;

    // �X�V����
    int Update()override;

    // �`�揈��
    int Draw() override;

    ~TestScene() override {}

private:
    std::shared_ptr<GameStatus> gamestatus_;  // Player �N���X�ւ̈ˑ�
    std::shared_ptr<ResourceManager> resourcemanager_;
   // std::shared_ptr<IMapManager> mapmanager_;  // Player �N���X�ւ̈ˑ�
    std::shared_ptr<SpriteRenderer> render_;  // Player �N���X�ւ̈ˑ�
    std::shared_ptr<IInputManager>inputmanager_;

};


#endif // TESTSCENE_H
