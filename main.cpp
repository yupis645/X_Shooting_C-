
#include"common.h"
#include "Game.h"
#include "di.hpp"
#include "GameManager.h"
#include "TitleScene.h"
#include "Geometry.h"
#include "DIContainer.h"

#include "TestGameManager.h"


// �f�o�b�N���[�h�̏�����ԁB�f�o�b�N���[�h���L���Ȃ�ŏ�����true
bool DebugEnable = DebugOn;
/*
* @brief	main()�֐�
*
* @note	�A�v���̊J�n�ʒu�B
*	��ʑJ�ڂ̗��������Đ��䂵�Ă���
*/
int main(void)
{
	//�y�A�v���S�̂̏������z
	SetCaption("2023 HAL Osaka.");	//�E�B���h�E�^�C�g��

	InitConioEx(ScreenConfig::SRN_W, 
				ScreenConfig::SRN_H,
				ScreenConfig::PXW,
				ScreenConfig::PXH);	//�������F�^�e���R�T�C�Y�ƃh�b�g�̑傫��





	//�y��ʑJ�ڂׂ̈̃��[�v�z
	int scene_id = TITLE;
	// SCENE�\���̂�DI�R���e�i�ɓo�^����
	//auto injector = di::make_injector(
	//	di::bind<Scenestatus>().to(std::make_shared<Scenestatus>()),   // SCENE���쐬���A�o�^
	//	di::bind<IPlayer>().to<Player>()	//�v���C���[
	//);

	//DIContainer container;

	//auto playerpt = injector.create<std::shared_ptr<Player>>();
	// 
	// 
	   // DI�R���e�i���쐬
	auto injector = std::make_shared<DIContainer>();

	auto GM = injector->Create<GameManager>();

	//// GameManager��DI�R���e�i����擾
	//auto GM = std::make_shared<GameManager>(injector);

	// GameManager�̏�����
	GM->Init();

	while (1) {

		int state = GM->Input();
		int gamestate = GM->Update();
		int sw = GM->Draw();

		if (state == APP_EXIT) {
			break;
		}
	}

	GM->End();

	//�y�A�v���S�̂̏I�������z
	EndConioEx();	//ConioEx�̏I������
	return 0;
}


//
//// �f�o�b�N���[�h�̏�����ԁB�f�o�b�N���[�h���L���Ȃ�ŏ�����true
//bool DebugEnable = DebugOn;
//
////�X�R�A�Ǝc�@�ȂǃV�[�����ׂ��Ŏg�p������
// GAMESTATE state = {0,0};
///*
//* @brief	main()�֐�
//*
//* @note	�A�v���̊J�n�ʒu�B
//*	��ʑJ�ڂ̗��������Đ��䂵�Ă���
//*/
//int main(void)
//{
//	//�y�A�v���S�̂̏������z
//	SetCaption("2023 HAL Osaka.");	//�E�B���h�E�^�C�g��
//	InitConioEx(SRN_W, SRN_H, PXW, PXH);	//�������F�^�e���R�T�C�Y�ƃh�b�g�̑傫��
//
//	//�y��ʑJ�ڂׂ̈̃��[�v�z
//	int scene_id = TITLE;
//	// SCENE�\���̂�DI�R���e�i�ɓo�^����
//	//auto injector = di::make_injector(
//	//	di::bind<Scenestatus>().to(std::make_shared<Scenestatus>()),   // SCENE���쐬���A�o�^
//	//	di::bind<IPlayer>().to<Player>()	//�v���C���[
//
//	//);
//
//	//DIContainer container;
//
//	//auto playerpt = injector.create<std::shared_ptr<Player>>();
//
//
//	GameManager Gamemanager(std::make_shared<DIContainer>(),std::make_shared<TitleScene>(),std::make_shared<GameStatus>(),std::make_shared<InputManager>());
//	Gamemanager.Init();
//
//
//	while (true) {
//		switch (scene_id) {
//		case	TITLE:	//�^�C�g�����
//			Title(&scTitle);
//			scene_id = scTitle.next_scene;	//���̉��ID���󂯎��
//			break;
//		case	GAME:	//�Q�[�����
//			Game(&scGame);
//			scene_id = scGame.next_scene;	//���̉��ID���󂯎��
//			break;
//		case	RESULT:	//���U���g���
//			Result(&scResult);
//			scene_id = scResult.next_scene;	//���̉��ID���󂯎��
//		}
//		//�A�v���I������
//		if (scene_id == APP_EXIT) {
//			break;
//		}
//	}
//	//�y�A�v���S�̂̏I�������z
//	EndConioEx();	//ConioEx�̏I������
//	return 0;
//}
//
//




//----------------------------------------------------------------
//	2023 HAL osaka.
//----------------------------------------------------------------
