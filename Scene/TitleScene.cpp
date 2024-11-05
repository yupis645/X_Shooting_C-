
#include "TitleScene.h"

#include "DIContainer.h"
#include "IInputManager.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "GameTexture.h"
#include "conioex.h"
#include "InputManager.h"
#include "ResourceManager.h"

using namespace ScreenConfig;
using InputFlag = IInputManager::InputFlag;
using InputMode = IInputManager::InputMode;
namespace {
	//�X�e�[�g�萔
	constexpr int PUSH_START_WAIT_STATE = 0;		//�X�e�[�g 0: pushstart�ƃ{�^�����������̂�҂��Ă���X�e�[�g
	constexpr int SELECT_PLAYER_MODE_STATE = 1;		//�X�e�[�g 1: 1 player��2 player�������߂�X�e�[�g
	constexpr int GAMESCENE_SHIFT_STATE = 2;		//�X�e�[�g 2: �Q�[���V�[���ֈڍs����X�e�[�g

	//SELECT_PLAYER_MODE����cursor�̏���Ɖ���
	constexpr int CURSOR_MAX_VALUE = 1;				//cursor�̏��
	constexpr int CURSOR_MIN_VALUE = 0;				//cursor�̉���

	//SELECT_PLAYER_MODE�őI�����ꂽ���̎��@�̎c�@
	constexpr int PLAYER_ONE_LIFE = 3;
	constexpr int PLAYER_TWO_LIFE = PLAYER_ONE_LIFE * 2;

	//�X�e�[�g1 -> �X�e�[�g2�Ɉړ�����ۂ̃J�[�\���̈ʒu�̖��O
	constexpr int SELECT_ONE_PLAYER = 0;
	constexpr int SELECT_TWO_PLAYER = 1;

}


TitleScene::TitleScene(std::shared_ptr<DIContainer> con) :
	container_(con),
	gamestatus_(con->Create<GameStatus>()),
	inputmanager_(con->Create<IInputManager>()),
	resourcemanager_(con->Create<ResourceManager>())
{
	menu[0].updateText("PUSH STARTENTER");
	menu[1].updateText("1 PLAYER");
	menu[2].updateText("2 PLAYERS");

	titlenameplate = resourcemanager_->GetTexture(TextureType::Title);

}

int TitleScene::Init()
{
	SceneBase::Init();

	return 0;
}


int TitleScene::Update()
{
	float cursorinput = 0;


	if (state >= GAMESCENE_SHIFT_STATE) return -1;  // state �� 2 �ȏ�Ȃ�G���[��Ԃ�

	FrameCountUpdate(1);		//�t���[���J�E���g


	if (inputmanager_->IsFlagSet(InputFlag::esc, InputMode::pushdown))return SceneID::APP_EXIT;
	if (inputmanager_->IsFlagSet(InputFlag::select, InputMode::pushdown))
	{
		state++;
	}

	// cursor�̑���
	if (inputmanager_->IsFlagSet(InputFlag::down, InputMode::pushdown))cursorinput--;		//�����������͂��ꂽ��ŏ��̂ݔ���
	if (inputmanager_->IsFlagSet(InputFlag::up, InputMode::pushdown))cursorinput++;			//����������͂��ꂽ��ŏ��̂ݔ���
	if (inputmanager_->IsFlagSet(InputFlag::cancel, InputMode::pushdown))isinit = false;			//����������͂��ꂽ��ŏ��̂ݔ���

	// �J�[�\���̃��[�v
	movecarsor(0,cursorinput, CURSOR_MIN_VALUE, CURSOR_MAX_VALUE);
	
	//state�ϐ���GAMESCENE_SHIFT_STATE�ɂȂ�����V�[���J��
	if (state >= GAMESCENE_SHIFT_STATE) {
		switch ((int)Getcarsor().y) {
		case SELECT_ONE_PLAYER:
			gamestatus_->life(PLAYER_ONE_LIFE);
			break;
		case SELECT_TWO_PLAYER:
			gamestatus_->life(PLAYER_TWO_LIFE);
			break;
		}
		//���̃V�[�����Z�b�g����
		return SceneID::GAME;	//���̑J�ڐ���ID���Z�b�g
	}

	return 0;
}

int TitleScene::Draw()
{
	auto TextW_offset = [](int y = 0) { return CENTER_X - (HALFWORD_W * y); };		//�e�L�X�g��\������ۂ̍s�����ւ̃I�t�Z�b�g
	auto SelectTextOffset = [](int i = 1) { return 30 - (i * 30); };

	

	//resourcemanager_->GameTextureDraw(TextureType::Title, 0, SRN_W / 2 - 99, 100);		//�^�C�g���̕\��
	render_->DrawFromTopLeftPos(titlenameplate, 0, SRN_W / 2 - 99, 100);

	switch (state) {
	case PUSH_START_WAIT_STATE:
		WriteTextFA(TextW_offset(static_cast<int>(menu[0].str.size())), CENTER_Y, 0, "%s", menu[0].toCharArray());		//"PUSH START ENTER"�̕\��
		break;
	case SELECT_PLAYER_MODE_STATE:
		for (int i = 0; i < 2; i++) {
			WriteTextFA(TextW_offset(static_cast<int>(menu[2].str.size())), CENTER_Y - SelectTextOffset(i), 0, "%s", menu[i + 1].toCharArray());	//�e�L�X�g�̕\���ʒu
		}
		WriteTextFA(TextW_offset(static_cast<int>(menu[0].str.size())) - WORD_W, CENTER_Y - SelectTextOffset((int)Getcarsor().y), 0, "��");	//�J�[�\���̕\��
		break;
	
	}

	return 0;
}

inline TitleScene::~TitleScene() {
	// �I�������i���\�[�X����Ȃǁj
}

