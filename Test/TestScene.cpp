#include "TestScene.h"

#include "DIContainer.h"
#include "Game.h"
#include "InputManager.h"
#include  "ResourceManager.h"
#include "IMapManager.h"
#include "SpriteRenderer.h"

using namespace ScreenConfig;
using InputFlag = IInputManager::InputFlag;
using InputMode = IInputManager::InputMode;

TestScene::TestScene(std::shared_ptr<DIContainer> con) :
    gamestatus_(con->Create<GameStatus>()),
    resourcemanager_(con->Create<ResourceManager>()),
  //  mapmanager_(con->Create<IMapManager>()),
    inputmanager_(con->Create<IInputManager>()),
    render_(con->Create<SpriteRenderer>())
{
    
}

int TestScene::Init() {
    int r = SceneBase::Init();
  //  int s = mapmanager_->Init();

    return 0;
}


int TestScene::Update() {
    //mapmanager_->Update();
    return 0; 
}

int TestScene::Draw() {

    inputmanager_->InputReception();
   // mapmanager_->Draw();

    //resourcemanager_->GameTextureDraw(TextureType::Title, 0, SRN_W / 2 - 99, 100);  // �^�C�g���̕`��
    //resourcemanager_->GameTextureDraw(TextureType::Player, 2, 100, 100);         // �v���C���[�̕`��


    //�{�̂̕`��
    for (int r = 0; r <= 10; r++) {
        for (int r2 = 0; r2 <= 10; r2++) {
            int pic_num = r * 11 + r2;
            //resourcemanager_->GameTextureDraw(TextureType::Boss, pic_num, 0 + (r2 * 32), 0 + (r * 32));         // �v���C���[�̕`��// 0 �` 110�͈̔͂Ōv�Z�����

        }
    }


    return 0;
}
