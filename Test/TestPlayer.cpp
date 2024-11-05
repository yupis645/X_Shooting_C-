#include "TestPlayer.h"

#include "InputManager.h"
#include "GameTexture.h"
#include "types.h"
#include "DIContainer.h"
#include "DebugManager.h"
#include "Player.h"

using namespace PlayerConfig;
using namespace ScreenConfig;

//===============================================================
//					コンストラクタ
//===============================================================
TestPlayer::TestPlayer(std::shared_ptr<DIContainer> con)
	: Player(con->Create<ResourceManager>(), con->Create<SpriteRenderer>(), con->Create<IInputManager>()),
	debug_(con->Create<DebugManager>())
{
	

}

//===============================================================
//					プレイヤーの情報初期化
//===============================================================
int TestPlayer::Init() {
	Player::Init();

	return 0;
}
//===============================================================
//					入力情報の処理
//===============================================================
int TestPlayer::Move(Vector2 move) {
	Player::Move(move);

	return 0;
}

//===============================================================
//					プレイヤーの更新
//===============================================================
int TestPlayer::Update(int framecount, Vector2 moveinput) {
	return Player::Update(framecount,moveinput);

}
//===============================================================
//			プレイヤー、照準器、ショット、ボムの描写
//===============================================================
int TestPlayer::Draw() {
	Player::Draw();

	if (!Player::Getshootdown())
	{
		debug_->DrawHitBox(*this,255,0,0,true);
	}

	return 0;
}


int TestPlayer::Sync_PositionAndHitbox()
{
	Player::Sync_PositionAndHitbox();


	return 0;
}
int TestPlayer::AnimationUpdate() {
	return Player::AnimationUpdate();

}