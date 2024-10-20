#ifndef TESTSCENE_H
#define TESTSCENE_H
#include <array>
#include "di.hpp"

class Scenestatus;
class GameStatus;
class IInputManager;
struct StringText;

#include "Geometry.h"
#include "SceneBase.h"
#include "IInputManager.h"
#include "DIContainer.h"
#include "ResourceManager.h"
#include "IMapManager.h"

#include "common.h"

class TestScene : public SceneBase {
public:
    TestScene(std::shared_ptr<DIContainer> container,
        std::shared_ptr<Scenestatus> st, 
        std::shared_ptr<GameStatus> gs, 
        std::shared_ptr<ResourceManager> rm,
        std::shared_ptr<IInputManager> im);

    // ����������
    int Init() override;

    // �X�V����
    int Update() override;

    // �`�揈��
    int Draw() override;

    ~TestScene() override {}

private:
    std::shared_ptr<Scenestatus> scenestatus_;  // Player �N���X�ւ̈ˑ�
    std::shared_ptr<GameStatus> gamestatus_;  // Player �N���X�ւ̈ˑ�
    std::shared_ptr<ResourceManager> resourcemanager_;
    std::shared_ptr<IMapManager> mapmanager_;  // Player �N���X�ւ̈ˑ�
    std::shared_ptr<IInputManager>inputmanager_;
};


#endif // TESTSCENE_H
