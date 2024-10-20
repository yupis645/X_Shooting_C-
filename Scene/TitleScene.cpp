
#include "common.h"
#include "Geometry.h"
#include "TitleScene.h"
#include "Game.h"
#include "conioex.h"

using namespace ScreenConfig; 
using InputFlag = IInputManager::InputFlag;
using InputMode = IInputManager::InputMode;
namespace {
	constexpr int PUSH_START_WAIT_STATE = 0;
	constexpr int SELECT_PLAYER_MODE_STATE = 1;
	constexpr int GAMESCENE_SHIFT_STATE = 2;
	constexpr int CURSOR_MAX_VALUE = 1;
	constexpr int CURSOR_MIN_VALUE = 0;
	constexpr int PLAYER_ONE_LIFE = 3;
	constexpr int PLAYER_TWO_LIFE = PLAYER_ONE_LIFE * 2;

}

TitleScene::TitleScene(std::shared_ptr<DIContainer> con,
	std::shared_ptr<Scenestatus> ss,
	std::shared_ptr<GameStatus> gs,
	std::shared_ptr<IInputManager> im,
	std::shared_ptr<ResourceManager> rm) :
	container_(con),
	gamestatus_(gs),
	scenestatus_(ss),
	inputmanager_(im),
	resourcemanager_(rm)
{
	menu[0].updateText("PUSH STARTENTER");
	menu[1].updateText("1 PLAYER");
	menu[2].updateText("2 PLAYERS");


}

int TitleScene::Init()
{
	SceneBase::Init();

	return 0;
}


int TitleScene::Update()
{
	if (state >= GAMESCENE_SHIFT_STATE) return -1;  // state �� 2 �ȏ�Ȃ�G���[��Ԃ�

	int cursorinput = 0;

	if (inputmanager_->IsFlagSet(InputFlag::esc, InputMode::pushdown))return SceneID::APP_EXIT;
	if (inputmanager_->IsFlagSet(InputFlag::select, InputMode::pushdown))state++;

	//cursor�̑���
	if (inputmanager_->IsFlagSet(InputFlag::down, InputMode::pushdown))cursorinput--;		//�����������͂��ꂽ��ŏ��̂ݔ���
	if (inputmanager_->IsFlagSet(InputFlag::up, InputMode::pushdown))cursorinput++;			//����������͂��ꂽ��ŏ��̂ݔ���

	//�J�[�\���̃��[�v
	scenestatus_->movecarsor_y(cursorinput, CURSOR_MIN_VALUE, CURSOR_MAX_VALUE);
	
	if (state >= GAMESCENE_SHIFT_STATE) {
		switch (scenestatus_->Getcarsor().y) {
		case 0:
			gamestatus_->life(PLAYER_ONE_LIFE);
			break;
		case 1:
			gamestatus_->life(PLAYER_TWO_LIFE);
			break;
		}
		//���̃V�[�����Z�b�g����
		scenestatus_->Setnextscene(SceneID::GAME);	//���̑J�ڐ���ID���Z�b�g
	}

	return 0;
}

int TitleScene::Draw()
{
	auto TextW_offset = [](int y = 0) { return CENTER_X - (HALFWORD_W * y); };
	auto SelectTextOffset = [](int i = 1) { return 30 - (i * 30); };

	resourcemanager_->GameTextureDraw(TextureType::Title, 0, SRN_W / 2 - 99, 100);		//�^�C�g���̕\��


	switch (state) {
	case PUSH_START_WAIT_STATE:
		WriteTextFA(TextW_offset(menu[0].str.size()), CENTER_Y, 0, "%s", menu[0].toCharArray());		//"PUSH START ENTER"�̕\��
		break;
	case SELECT_PLAYER_MODE_STATE:
		for (int i = 0; i < 2; i++) {
			WriteTextFA(TextW_offset(menu[2].str.size()), CENTER_Y - SelectTextOffset(i), 0, "%s", menu[i + 1].toCharArray());	//�e�L�X�g�̕\���ʒu
		}
		WriteTextFA(TextW_offset(menu[0].str.size()) - WORD_W, CENTER_Y - SelectTextOffset(scenestatus_->Getcarsor().y), 0, "��");	//�J�[�\���̕\��
		break;
	
	}
	//	WriteTextFA(TextW_offset(menu[0].str.size()) - WORD_W, CENTER_Y - SelectTextOffset(0) - 15, 0, "lif = %d,caroser = %d,state = %d", gamestatus_->life(),scenestatus_->Getcarsor(), state);	//�J�[�\���̕\��

#if TestMode
	WriteTextFA(0, SRN_H - (WORD_H * 22), 0, "---------------------------------�������---------------------------------");
	WriteTextFA(0, SRN_H - (WORD_H * 20), 0, "�E[Enter�L�[ : ����] �E[Esc : �Q�[���̏I��]");
	WriteTextFA(0, SRN_H - (WORD_H * 18), 0, "�E[�����L�[ : �ړ�] �E[Z�L�[ : �V���b�g]�@�E[X�L�[ : ���e]�@�@");
	WriteTextFA(0, SRN_H - (WORD_H * 16), 0, "�E[Space�L�[ : �ꎞ��~] �E[D�L�[ : �f�o�b�N���[�h�؂�ւ�] ");
	WriteTextFA(0, SRN_H - (WORD_H * 14), 0, "--------------------------------------------------------------------------");
	if (DebugEnable) {
		WriteText(CENTER_X - (WORD_W * 9), SRN_H - (WORD_H * 38), L"�f�o�b�N���[�h ON");
		WriteText(0, SRN_H - (WORD_H * 36), L"----------------------�f�o�b�N���[�h�̕\����------------------------------");
		WriteText(0, SRN_H - (WORD_H * 34), L"�EPlayer���G �EPlayer,Enemy��HItBox�̉��� �E�Q�[�����̃X�e�[�^�X�̕\��");
		WriteText(0, SRN_H - (WORD_H * 32), L"--------------------------------------------------------------------------");

		WriteText(0, SRN_H - (WORD_H * 12), L"----------------------�f�o�b�N���[�h�������------------------------------");
		WriteText(0, SRN_H - (WORD_H * 10), L"�E[1,2,3,4,5,5,6,7,8,9�L�[ , Q�L�[ : �e�󒆓G�̏o��] ");
		WriteText(0, SRN_H - (WORD_H * 8), L"�E[W,E,R,T,Y,U,I,O,P,A,S�L�[: �e�n��G�̏o��]�@");
		WriteText(0, SRN_H - (WORD_H * 6), L"�E[F�L�[ : �{�X�̏o�� ]�@�E[G�L�[ : �G�̃^�C�v�ύX ]");
		WriteText(0, SRN_H - (WORD_H * 4), L"--------------------------------------------------------------------------");
	}
#endif

	return 0;
}

inline TitleScene::~TitleScene() {
	// �I�������i���\�[�X����Ȃǁj
}


//
//
//#include"common.h"
//#include "Title.h"
//
//
//// ----------------------------------------------------------------
//// �^�C�g�����
//// ----------------------------------------------------------------
////�ϐ��錾
//SCENE scTitle = { true,0,TITLE,0 ,{0,0 } };	//�V�[���\����
//
//Bmp* Titlepic = nullptr;
//const wchar_t* texture = L"res/STG_Title.png";
////�^�C�g�����
//void Title(SCENE* _sc)
//{
//	Title_Init(_sc);
//	while (_sc->loop) {
//		Title_Input(_sc);
//		Title_Update(_sc);
//		Title_Draw(_sc);
//		_sc->frame_count++;
//	}
//	Title_End(_sc);
//}
////����������
//void Title_Init(SCENE* _sc)
//{
//	_sc->loop = true;	//�Q�[�����[�v�p���t���O
//	_sc->frame_count = 0;
//	_sc->next_scene = TITLE;
//	_sc->scene_state = 0;	//�i���x�����̏�����
//
//	LoadDivBmp(texture,
//		0, 0, 198, 58, 1, 1, &Titlepic);
//
//	/*��*/
//	//LoadDivBmp(_t->filename,
//		//208, 0, 8, 5, 4, 1, _t->flash);
//
//
//
//}
////����
//void Title_Input(SCENE* _sc)
//{
//	GetKeyAll();	//�S�ẴL�[���́B
//
//	//�A�v���I���L�[�̔���
//	if (ChkKeyPress(VK_ESCAPE)) {
//		_sc->loop = false;	//�Q�[�����[�v�I��
//		_sc->next_scene = APP_EXIT;	//���̉�ʑJ�ڐ���u�A�v���I���v�ɂ���
//		return;	//�����ɂ��̊֐����I��
//	}
//	if (ChkKeyEdge(VK_RETURN)) {
//		//�G���^�[�L�[��ʂ�i��������
//		_sc->scene_state++;
//	}
//	if (ChkKeyEdge(PK_O)) {
//		//O�Ŏ��I�v�V������ʂɑJ��
//		_sc->next_scene = OPTION;	//���̑J�ڐ���ID���Z�b�g
//		_sc->loop = false;	//�^�C�g���I��
//	}
//	if (_sc->scene_state == 1) {
//		if (ChkKeyEdge(PK_UP)) {
//			_sc->carsor.y--;
//		}
//		if (ChkKeyEdge(PK_DOWN)) {
//			_sc->carsor.y++;
//		}
//
//	}
//
//#if TestMode
//	if (DebugOn) {
//		//�f�o�b�N���[�h�̗L���� / ������
//		if (ChkKeyEdge(PK_D)) { DebugEnable = DebugEnable ? false : true; }
//	}
//#endif
//
//
//}
////�X�V
//void Title_Update(SCENE* _sc)
//{
//	if (_sc->scene_state >= 2) {
//		switch (_sc->carsor.y) {
//		case 0:
//		case 1:
//			_sc->next_scene = GAME;	//���̑J�ڐ���ID���Z�b�g
//			state.life = 3;
//			break;
//		case 2:
//			_sc->next_scene = GAME;	//���̑J�ڐ���ID���Z�b�g
//			state.life = 6;
//			break;
//
//		}
//		//���̉�ʂɑJ��
//		_sc->loop = false;	//�^�C�g���I��
//
//	}
//
//	//�J�[�\���̃��[�v
//	REPEAT(_sc->carsor.y, 0, 2);		//�J�[�\����0�ȉ��ɂȂ��3��3�𒴂����0�ɖ߂�
//
//}
////�`��
//void Title_Draw(SCENE* _sc)
//{
//	MOJI Text[] = { {"PUSH START ENTER",1},{"1 PLAYER",1},{"2 PLAYERS",1} };		//�e�L�X�g�̕���
//	int po[] = { 30, 30,0 };
//	ClearScreen(0x00, 0x00, 0x00);	//��ʏ����FR,G,B�̎w��F�œh��Ԃ�
//	//��������������
//	DrawBmp(SRN_W / 2 - 99, 100, Titlepic);		//�^�C�g���̕\��
//
//	switch (_sc->scene_state) {
//	case 0:
//		WriteTextFA(SRN_W / 2 - ((WORD_W / 2) * strlen(Text[0].word)), SRN_H / 2, 0, "%s", Text[0]);		//"PUSH START ENTER"�̕\��
//		break;
//	case 1:
//		for (int r = 1; r < 4; r++) {
//			WriteTextFA(SRN_W / 2 - ((WORD_W / 2) * strlen(Text[2].word)), SRN_H / 2 - po[r], 0, "%s", Text[r]);	//�e�L�X�g�̕\���ʒu
//		}
//		WriteTextFA(SRN_W / 2 - ((WORD_W / 2) * strlen(Text[0].word)) - WORD_W, SRN_H / 2 - po[_sc->carsor.y], 0, "��");	//�J�[�\���̕\��
//
//	}
//
//#if TestMode
//	WriteTextFA(0, SRN_H - (WORD_H * 22), 0, "---------------------------------�������---------------------------------");
//	WriteTextFA(0, SRN_H - (WORD_H * 20), 0, "�E[Enter�L�[ : ����] �E[Esc : �Q�[���̏I��]");
//	WriteTextFA(0, SRN_H - (WORD_H * 18), 0, "�E[�����L�[ : �ړ�] �E[Z�L�[ : �V���b�g]�@�E[X�L�[ : ���e]�@�@");
//	WriteTextFA(0, SRN_H - (WORD_H * 16), 0, "�E[Space�L�[ : �ꎞ��~] �E[D�L�[ : �f�o�b�N���[�h�؂�ւ�] ");
//	WriteTextFA(0, SRN_H - (WORD_H * 14), 0, "--------------------------------------------------------------------------");
//	if (DebugEnable) {
//		WriteText(CENTER_X - (WORD_W * 9), SRN_H - (WORD_H * 38), L"�f�o�b�N���[�h ON");
//		WriteText(0, SRN_H - (WORD_H * 36), L"----------------------�f�o�b�N���[�h�̕\����------------------------------");
//		WriteText(0, SRN_H - (WORD_H * 34), L"�EPlayer���G �EPlayer,Enemy��HItBox�̉��� �E�Q�[�����̃X�e�[�^�X�̕\��");
//		WriteText(0, SRN_H - (WORD_H * 32), L"--------------------------------------------------------------------------");
//
//		WriteText(0, SRN_H - (WORD_H * 12), L"----------------------�f�o�b�N���[�h�������------------------------------");
//		WriteText(0, SRN_H - (WORD_H * 10), L"�E[1,2,3,4,5,5,6,7,8,9�L�[ , Q�L�[ : �e�󒆓G�̏o��] ");
//		WriteText(0, SRN_H - (WORD_H * 8), L"�E[W,E,R,T,Y,U,I,O,P,A,S�L�[: �e�n��G�̏o��]�@");
//		WriteText(0, SRN_H - (WORD_H * 6), L"�E[F�L�[ : �{�X�̏o�� ]�@�E[G�L�[ : �G�̃^�C�v�ύX ]");
//		WriteText(0, SRN_H - (WORD_H * 4), L"--------------------------------------------------------------------------");
//	}
//#endif
//	//�����������܂�
//	PrintFrameBuffer();	//��ʃo�b�t�@��]��
//	RenderScreen();		//��ʂ������_�����O
//	FrameSync();		//�P�t���[���̓���
//}
////�I������
//void Title_End(SCENE* _sc)
//{
//}