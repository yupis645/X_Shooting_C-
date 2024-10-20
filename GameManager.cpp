#include "GameManager.h"
#include "GameScene.h" 
#include "TitleScene.h" 

static int a = ScreenConfig::SRN_W;
static int b = ScreenConfig::SRN_H;
static int c = ScreenConfig::PXW;
static int d = ScreenConfig::PXH;

#include "conioex.h"

using InputFlag = IInputManager::InputFlag;
using InputMode = IInputManager::InputMode;

int GameManager::Init() {
	return 0;
}

int GameManager::Input()
{
	inputmanager_->InputReception();

	if (inputmanager_->IsFlagSet(InputFlag::esc, InputMode::pushdown))
	{
		return 999;
	}

	


//#if TestMode
//	if (DebugOn) {
//		//�f�o�b�N���[�h�̗L���� / ������
//		if (ChkKeyEdge(PK_D)) { DebugEnable = DebugEnable ? false : true; }
//	}
//#endif

	return 0;

}
//
//// �V�[���̐؂�ւ�
//int GameManager::ChangeScene(std::shared_ptr<SceneBase> newScene) {
//	currentscene_ = newScene;
//	if (currentscene_) {
//		currentscene_->Init();
//		return 0;
//	}
//	return -1;
//}

// �V�[���̍X�V�ƕ`��
int GameManager::Update() {

	
	currentscene_->Update();

	if (scenestatus_->SceneChangeSignal())
	{
		SwitchToScene<GameScene>();
	}


	return 0;
}

int GameManager::Draw() 
{
	ClearScreen(0x10, 0x10, 0x10);	//��ʏ����FR,G,B�̎w��F�œh��Ԃ�
	//��������������
	currentscene_->Draw();
	//�����������܂�
	PrintFrameBuffer();	//��ʃo�b�t�@��]��
	RenderScreen();		//��ʂ������_�����O
	FrameSync();		//�P�t���[���̓���    

	return 0;
}

// �V�[���̏I������
int GameManager::End() {

	return 99;
}