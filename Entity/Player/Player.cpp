
#include "Player.h"

#include "InputManager.h"
#include "GameTexture.h"
#include "types.h"

using namespace PlayerConfig;
using namespace ScreenConfig;

//===============================================================
//					コンストラクタ
//===============================================================
//===============================================================
//					コンストラクタ
//===============================================================
Player::Player(std::shared_ptr<ResourceManager> rm, std::shared_ptr<SpriteRenderer> render, std::shared_ptr<IInputManager> input)
	: anim(0), pat(0), shootdown(false), ownframecount(0), render_(render),input_(input),
	texture(rm->GetTexture(TextureType::Player)) // 必要なら初期化
{
	// Targetsightのインスタンスを動的に作成
	targetsight = std::make_unique<Targetsight>(*this, rm);
}




//===============================================================
//					プレイヤーの情報初期化
// 
// 座標などの情報を初期化する
//===============================================================
int Player::Init() {
	position = Vector2(CENTER_X, CENTER_Y);
	hitbox.CenterPositionSync(position, PLAYER_HITBOX_SIZE);
	targetsight->Init();
	anim = 0;
	pat = 0;
	shootdown = false;
	ownframecount = 0;
	return 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

																	/*入力された情報を処理する*/

//===============================================================
//					入力情報の処理
// 
// ・移動キーによる移動
// ・ショットキーによる射撃
// ・ボムキーによる対地攻撃
//===============================================================
int Player::Move(Vector2 move) {

	// 左移動: 左端に到達していないなら移動を許可
	if (move.x < 0 && hitbox.left <= 0) {
		move.x = 0;  
	}
	// 右移動: 右端に到達していないなら移動を許可
	if (move.x > 0 && hitbox.right >= SRN_W) {
		move.x = 0;  
	}

	// 上移動: 上端に到達していないなら移動を許可
	if (move.y < 0 && hitbox.top <= 0) {
		move.y = 0; 
	}
	// 下移動: 下端に到達していないなら移動を許可
	if (move.y > 0 && hitbox.bottom >= SRN_H) {
		move.y = 0;  
	}

	// 移動量を反映
	position.x += move.x * SPEED;
	position.y += move.y * SPEED;

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

																	/*更新処理*/

//===============================================================
//					プレイヤーの更新
// 
// ・座標移動に合わせた画像や当たり判定の移動
// ・アニメーション番号の管理
// ・ショットの更新(座標移動 & ヒット処理)
// ・ボムの更新(座標移動 & ヒット処理)
// ・敵と敵弾に対する被弾判定
// 
//  ※TestMode true & DebugEnable trueの場合は被弾処理を無効化
//===============================================================
int Player::Update( int framecount, Vector2 moveinput) {
	
	//独自のframecountを進める
	ownframecount++;

	//プレイヤーと照準器のboxcolliderの移動
	Sync_PositionAndHitbox();

	targetsight->Update();

	////*自機のアニメーション番号の進行*/
	int s = AnimationUpdate();
	if (s == 2) return 2;

	//入力に対する自機の移動
	Move(moveinput) ;

	

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

																	/*プレイヤー関連のスプライトを表示させる*/
//===============================================================
//			プレイヤー、照準器、ショット、ボムの描写
// 
// anim番号にそってそれぞれ描写する。
// ・照準器は当たり判定が地上敵と重なっている場合はanim番号が変化する(通常は青で重なっていると赤になる)
// ・被弾するまではプレイヤーと照準器のスプライト。
//	   被弾後は爆発アニメーションを描画する
// ・ショットの描画
// ・ボムの描画
//===============================================================
int Player::Draw() {


	/* プレイヤー or 照準の描写 */
	if (!shootdown) {
		render_->DrawFromCenterPos(texture,anim, position, PLAYER_PIC_SIZE);
		targetsight->Draw();

		
	}

	/* プレイヤーが撃破された場合 */
	else if (shootdown && anim < 6) {  // 爆発アニメーションの描画（anim <= 6は爆発アニメーションが6フレーム）
		render_->DrawBomberFromCenterPos(SpriteRenderer::BomberType::bomber,anim, position);
		//DrawBmp(pic.x, pic.y, ImageManager::PlayerBomber[anim]);  // 自機の描写
		//render_->DrawFromCenterPos(texture, anim, position.x, position.y, PLAYER_PIC_SIZE);


		return 0;
	}

	return 0;
}


int Player::Sync_PositionAndHitbox()
{
	/////*プレイヤーの当たり判定を更新する*/
	hitbox.CenterPositionSync(position, PLAYER_HITBOX_SIZE);

	/////*照準の当たり判定の更新*/
	targetsight->hitboxsync(position);

	return 0;
}
int Player::AnimationUpdate(){

	////*自機のアニメーション番号の進行*/

		//被弾していない場合
	if (shootdown == false) {
		if (ownframecount % 12 == 0) {
			anim++;		//アニメーション番号を進める
			//Clamp(anim, 2, 4);		//プレイヤーのanim番号をループさせる
			if(anim >= TextureConfigs::PLAYER.indexcount) anim = 0;
			ownframecount = 0;
		}
	}

	else {
		if (ownframecount % 12 == 0) {
			anim++;		//アニメーション番号を進める
			//Clamp(anim, 2, 4);		//プレイヤーのanim番号をループさせる
			if (anim >= 5) anim = 0;
		}
		if (ownframecount % 20 == 0)	return 2;
	}

	return 0;
}