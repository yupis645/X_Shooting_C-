
//----------------------------------------------------------------------------------------------------
//                              �e�X�g�pGameManager
// 
// �Q�[���S�̂��Ǘ�����N���X�̃e�X�g�N���X
// init(������),input(����),update(�X�V),draw(�`��)�̃��C�t�T�C�N�����Ǘ�����
//----------------------------------------------------------------------------------------------------

#include "TestGameManager.h"
#include "TestScene.h"

#include "GameManager.h"
#include "GameScene.h" 
#include "TitleScene.h" 
#include "DIContainer.h"
#include "SceneManager.h"
#include "IInputManager.h"
#include "ResourceManager.h"
#include "SceneBase.h"


//==================================================================
//						�R���X�g���N�^
// 
// di�R���e�i���AgameStatus,ResouceManager,InputManager�̃C���X�^���X���擾����
// currnetscene_�ɂ͍ŏ��Ɏg�p����V�[�����w�肷��
//==================================================================
TestGameManager::TestGameManager(std::shared_ptr<DIContainer> con)
	: container_(con),
	gamestatus_(con->Create<GameStatus>()),
	resoucemanager_(con->Create<ResourceManager>()),
	inputmanager_(con->Create<IInputManager>()),
	render_(con->Create<SpriteRenderer>())
{
}

//==================================================================
//						������
//==================================================================
int TestGameManager::Init() {
	scenemanager_->SwitchToScene<TestScene>();

	return 0;
}

//==================================================================
//						����
//==================================================================
int TestGameManager::Input()
{
	return 0;
}


//==================================================================
//						�X�V
//==================================================================
int TestGameManager::GameLoop() {

	scenemanager_->Init();
	scenemanager_->Update();
	scenemanager_->Draw();

	



	return 0;
}



//==================================================================
//						�I������
//==================================================================
int TestGameManager::End() {

	return 99;
}