#include "TestGameManager.h"

#include "TestScene.h"

using InputFlag = IInputManager::InputFlag;
using InputMode = IInputManager::InputMode;

int TestGameManager::Init() {
	currentscene_->Init();


	return 0;
}

int TestGameManager::Input()
{
	return 0;
}

// �V�[���̍X�V�ƕ`��
int TestGameManager::Update() {

	
	currentscene_->Update();



	return 0;
}

int TestGameManager::Draw()
{
	ClearScreen(0x10, 0x10, 0x10);	//��ʏ����FR,G,B�̎w��F�œh��Ԃ�
	//��������������
	inputmanager_->InputReception();
	currentscene_->Draw();
	//�����������܂�
	PrintFrameBuffer();	//��ʃo�b�t�@��]��
	RenderScreen();		//��ʂ������_�����O
	FrameSync();		//�P�t���[���̓���    

	return 0;
}

// �V�[���̏I������
int TestGameManager::End() {

	return 99;
}