

//----------------------------------------------------------------------------------------------------
//                              �Q�[���S�̂��Ǘ�����N���X
// 
// �Q�[���S�̂��Ǘ�����N���X�B�Q�[���J�n����I���܂Ő�����������
// di�R���e�i�ł̓V���O���g���Ńo�C���h����Ă���̂ŁAcreate�֐��ŏ�ɓ����C���X�^���X���擾�ł���
// init(������),input(����),update(�X�V),draw(�`��)�̃��C�t�T�C�N�����Ǘ�����
//----------------------------------------------------------------------------------------------------
#include "SceneManager.h"

#include "SceneBase.h"
#include "GameScene.h" 
#include "TitleScene.h" 

#include "DIContainer.h"
#include "DebugManager.h" 
#include "InputManager.h" 

#include "TestGameScene.h"


#include "conioex.h"

using InputFlag = IInputManager::InputFlag;
using InputMode = IInputManager::InputMode;

//.cpp�Ŏg����萔
namespace {

	//����2�Ŏw�肳�ꂽsceneid���玟�ɕύX����V�[�����w�肵�ĕύX����
	void ChangeSceneID(SceneManager& sm, int sceneid) {
		switch (sceneid)
		{
		case SceneID::TITLE:
			sm.SwitchToScene<TitleScene>();		//�^�C�g���V�[����������x���[�h����
			break;
		case SceneID::GAME:
			sm.SwitchToScene<TestGameScene>();		//�Q�[���V�[�������[�h����
			break;
		case SceneID::OPTION:					//�I�v�V�����V�[�������[�h����
			break;
		case SceneID::RESULT:					//���U���g�V�[�������[�h����
			break;

		}
	}
}

//===========================================================================================
//							������
//===========================================================================================
int SceneManager::Init() {
	if (currentscene_->GetIsinit())  return 0;		//scene�N���X��isinit��true�̊Ԃ͏��������Ȃ�

	currentscene_->Init();


	currentscene_->SetIsinit(true);		//��������1��ȏ����Ȃ��悤��isinit��false�ɐݒ肷��

	return 0;
}


//===========================================================================================
//							�V�[���̍X�V
// 
// �V�[���̍X�V�������s���B�V�[�����ׂ̍��ȏ�����Scene�N���X���s���B
// �����ł�scene�N���X��Update�̕Ԃ�l�ɂ���ăG���[���� �y�� �V�[���J�ڂ��s��
//===========================================================================================
int SceneManager::Update() {

	currentscene_->FrameCountUpdate(1);

	int status = currentscene_->Update();

	//�Ԃ�l�� -1 �̏ꍇ
	if (status == -1) {
		std::cerr << "Error: SceneManager Update in scenemanager return -1: " << std::endl;	//�G���[���o��
		return SceneID::APP_EXIT;			//�A�v���̏I����main�֐��ɓ`����	 
	}

	//�Ԃ�l�� SceneID�͈̔͂ł������ꍇ
	if (status >= SceneID::TITLE && status <= SceneID::RESULT)
	{
		ChangeSceneID(*this, status);		//status�̔ԍ��ɂ���Ď��̃V�[�������肷��B�֐���namespace�ɂ���
	}


	return 0;
}

//===========================================================================================
//							��ʂւ̕`��
// 
// ��ʂւ̕`����s���B�ׂ��ȕ`����e�̓V�[����Draw���Ǘ�����B
// ��ʂ̃N���A���s���Ă���`����s��
//===========================================================================================
int SceneManager::Draw()
{
	ClearScreen(0x10, 0x10, 0x10);	//��ʏ����FR,G,B�̎w��F�œh��Ԃ�

	currentscene_->Draw();

	//container_->Create<DebugManager>()->DrawInputFrag();
	//container_->Create<DebugManager>()->DebugDrawTexture(DebugTexture::DebugSelectDraw::Boss);

	PrintFrameBuffer();	//��ʃo�b�t�@��]��
	RenderScreen();		//��ʂ������_�����O
	FrameSync();		//�P�t���[���̓���    

	return 0;
}
