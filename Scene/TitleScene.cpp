
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
	//ステート定数
	constexpr int PUSH_START_WAIT_STATE = 0;		//ステート 0: pushstartとボタンが押されるのを待っているステート
	constexpr int SELECT_PLAYER_MODE_STATE = 1;		//ステート 1: 1 playerか2 playerかを決めるステート
	constexpr int GAMESCENE_SHIFT_STATE = 2;		//ステート 2: ゲームシーンへ移行するステート

	//SELECT_PLAYER_MODE時のcursorの上限と下限
	constexpr int CURSOR_MAX_VALUE = 1;				//cursorの上限
	constexpr int CURSOR_MIN_VALUE = 0;				//cursorの下限

	//SELECT_PLAYER_MODEで選択された時の自機の残機
	constexpr int PLAYER_ONE_LIFE = 3;
	constexpr int PLAYER_TWO_LIFE = PLAYER_ONE_LIFE * 2;

	//ステート1 -> ステート2に移動する際のカーソルの位置の名前
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


	if (state >= GAMESCENE_SHIFT_STATE) return -1;  // state が 2 以上ならエラーを返す

	FrameCountUpdate(1);		//フレームカウント


	if (inputmanager_->IsFlagSet(InputFlag::esc, InputMode::pushdown))return SceneID::APP_EXIT;
	if (inputmanager_->IsFlagSet(InputFlag::select, InputMode::pushdown))
	{
		state++;
	}

	// cursorの操作
	if (inputmanager_->IsFlagSet(InputFlag::down, InputMode::pushdown))cursorinput--;		//下方向が入力されたら最初のみ反応
	if (inputmanager_->IsFlagSet(InputFlag::up, InputMode::pushdown))cursorinput++;			//上方向が入力されたら最初のみ反応
	if (inputmanager_->IsFlagSet(InputFlag::cancel, InputMode::pushdown))isinit = false;			//上方向が入力されたら最初のみ反応

	// カーソルのループ
	movecarsor(0,cursorinput, CURSOR_MIN_VALUE, CURSOR_MAX_VALUE);
	
	//state変数がGAMESCENE_SHIFT_STATEになったらシーン遷移
	if (state >= GAMESCENE_SHIFT_STATE) {
		switch ((int)Getcarsor().y) {
		case SELECT_ONE_PLAYER:
			gamestatus_->life(PLAYER_ONE_LIFE);
			break;
		case SELECT_TWO_PLAYER:
			gamestatus_->life(PLAYER_TWO_LIFE);
			break;
		}
		//次のシーンをセットする
		return SceneID::GAME;	//次の遷移先画面IDをセット
	}

	return 0;
}

int TitleScene::Draw()
{
	auto TextW_offset = [](int y = 0) { return CENTER_X - (HALFWORD_W * y); };		//テキストを表示する際の行方向へのオフセット
	auto SelectTextOffset = [](int i = 1) { return 30 - (i * 30); };

	

	//resourcemanager_->GameTextureDraw(TextureType::Title, 0, SRN_W / 2 - 99, 100);		//タイトルの表示
	render_->DrawFromTopLeftPos(titlenameplate, 0, SRN_W / 2 - 99, 100);

	switch (state) {
	case PUSH_START_WAIT_STATE:
		WriteTextFA(TextW_offset(static_cast<int>(menu[0].str.size())), CENTER_Y, 0, "%s", menu[0].toCharArray());		//"PUSH START ENTER"の表示
		break;
	case SELECT_PLAYER_MODE_STATE:
		for (int i = 0; i < 2; i++) {
			WriteTextFA(TextW_offset(static_cast<int>(menu[2].str.size())), CENTER_Y - SelectTextOffset(i), 0, "%s", menu[i + 1].toCharArray());	//テキストの表示位置
		}
		WriteTextFA(TextW_offset(static_cast<int>(menu[0].str.size())) - WORD_W, CENTER_Y - SelectTextOffset((int)Getcarsor().y), 0, "→");	//カーソルの表示
		break;
	
	}

	return 0;
}

inline TitleScene::~TitleScene() {
	// 終了処理（リソース解放など）
}

