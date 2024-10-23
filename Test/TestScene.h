#ifndef TESTSCENE_H
#define TESTSCENE_H

#include "SceneBase.h"
#include "IInputManager.h"
#include "DIContainer.h"
#include "ResourceManager.h"
#include "IMapManager.h"
#include "SpriteRenderer.h"

#include "common.h"

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
    std::shared_ptr<IMapManager> mapmanager_;  // Player �N���X�ւ̈ˑ�
    std::shared_ptr<SpriteRenderer> render_;  // Player �N���X�ւ̈ˑ�
    std::shared_ptr<IInputManager>inputmanager_;

};


#endif // TESTSCENE_H
