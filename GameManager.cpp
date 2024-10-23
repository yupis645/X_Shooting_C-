
//----------------------------------------------------------------------------------------------------
//                              �Q�[���S�̂��Ǘ�����N���X
// 
// �Q�[���S�̂��Ǘ�����N���X�B�Q�[���J�n����I���܂Ő�����������
// di�R���e�i�ł̓V���O���g���Ńo�C���h����Ă���̂ŁAcreate�֐��ŏ�ɓ����C���X�^���X���擾�ł���
// init(������),input(����),update(�X�V),draw(�`��)�̃��C�t�T�C�N�����Ǘ�����
//----------------------------------------------------------------------------------------------------
#include "GameManager.h"
#include "GameScene.h" 
#include "TitleScene.h" 
#include "DIContainer.h"
#include "SceneManager.h"
#include "Game.h"
#include "IInputManager.h"
#include "ResourceManager.h"
#include "SceneBase.h"

using InputFlag = IInputManager::InputFlag;
using InputMode = IInputManager::InputMode;

//===========================================================================================
//							�R���X�g���N�^
// 
// di�R���e�i���K�v�Ȋ֐��̃C���X�^���X���쐬���ă����o�ϐ��ŕۊǂ���
// currentscene�ɂ�TitleScene�N���X���ŏ��ɍ쐬����
//===========================================================================================
GameManager::GameManager(std::shared_ptr<DIContainer> con)
	: container_(con),
	gamestatus_(con->Create<GameStatus>()),
	inputmanager_(con->Create<IInputManager>()),
	resourcemanager_(con->Create<ResourceManager>())
{
	scenemanager_ = std::make_shared<SceneManager>(container_);
}

//===========================================================================================
//							������
//===========================================================================================
int GameManager::Init() {
	scenemanager_->SwitchToScene<TitleScene>();

	return 0;
}

//===========================================================================================
//							����
// 
// InputReception�ɂĕ����L�[�Az,x,esc,enter�ȂǃQ�[�����Ɏg�p����S�ẴL�[�̓��͂��擾����
// ���N���X�͂����ł̓��͌��ʂ��󂯂ăA�N�V�������N�����B
//===========================================================================================
int GameManager::Input()
{
	//�S�Ă̓��͂��󂯂���
	inputmanager_->InputReception();

	//ESC�L�[�̓��͂��������ꍇ
	if (inputmanager_->IsFlagSet(InputFlag::esc, InputMode::pushdown))		//esc�t���O���`�F�b�N
	{
		return SceneID::APP_EXIT;			//�A�v���̏I����main�֐��ɓ`����	
	}


	return 0;

}

//===========================================================================================
//							�V�[���̍X�V
// 
// �V�[���̍X�V�������s���B�V�[�����ׂ̍��ȏ�����Scene�N���X���s���B
// �����ł�scene�N���X��Update�̕Ԃ�l�ɂ���ăG���[���� �y�� �V�[���J�ڂ��s��
//===========================================================================================
int GameManager::GameLoop() {

	int ir = scenemanager_->Init();
	int ur = scenemanager_->Update();
	int dr = scenemanager_->Draw();

	if (ir + ur + dr >= SceneID::APP_EXIT) return SceneID::APP_EXIT;

	return 0;
}

//===========================================================================================
//							�I������
//===========================================================================================
int GameManager::End() {

	return 99;
}