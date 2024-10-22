
#include "Player.h"

using namespace PlayerConfig;
using namespace ScreenConfig;

//===============================================================
//					コンストラクタ
//===============================================================
Player::Player(std::shared_ptr<ResourceManager> rm) : anim(0),  pat(0) ,shootdown(false)          
{
	//texture = rm->GetTextureManager()->GetTexture(TextureType::Player);     //マップチップのロード
	Create();
	// 必要な初期化処理があればここに記述
}



//===============================================================
//				 デストラクタ
//===============================================================
Player::~Player() {
	// 必要ならリソース解放などを行う
}

//===============================================================
//					プレイヤーの情報初期化
// 
// 座標などの情報を初期化する
//===============================================================
int Player::Init() {
	GameObject::InitClear();
	sight.Init();
	anim = 0;
	pat = 0;
	shootdown = false;
	ownframecount = 0;
	return 0;
}

//===============================================================
//					プレイヤーの作成
// 
// 仮に作ったPLAYERに必要なデータをセットして返す
// ・中心座標から画像と当たり判定の左上座標を求める
// ・照準器の左右をプレイヤーの左右と揃える
// ・自機、ショット&ボム、照準器の画像を取得する
//===============================================================
int Player::Create() {

	Init();


	hitbox.CenterPositionSync(position, PLAYER_HITBOX_SIZE);

	/*照準の当たり判定の更新*/
	sight.Init();

	


	///*プレイヤー画像読み込み*/
	//LoadDivBmp(PngData.Player, 0, 0, PLAYER_PIC_SIZE, PLAYER_PIC_SIZE, 6, 2,pic);		//自機 or 照準の画像ロード
	//LoadDivBmp(PngData.Shot, 0, 0, BULLET_SIZE, BULLET_SIZE, 3, 1, bullet);			//ザッパー or ブラスターの画像ロード	

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


	//Vector2 pic = LeftTopPos(position, PLAYER_PIC_SIZE);
	///* プレイヤー or 照準の描写 */
	//if (!shootdown) {
	//	// ImageManager からプレイヤー画像を取得して描画
	//	DrawBmp(pic.x, pic.y, ImageManager::player[anim]);               // 自機の描写
	//	//DrawBmp(pic_x, pic_y - BOM_ST, ImageManager::player[sight_anim]); // 照準の描写（ボムの射程距離分離す）
	//	sight.Draw();
	//}

	///* プレイヤーが撃破された場合 */
	//else if (shootdown && anim < 6) {  // 爆発アニメーションの描画（anim <= 6は爆発アニメーションが6フレーム）
	//	DrawBmp(pic.x, pic.y, ImageManager::PlayerBomber[anim]);  // 自機の描写
	//	

		return 0;
	//}
}


int Player::Sync_PositionAndHitbox()
{
	/////*プレイヤーの当たり判定を更新する*/
	hitbox.CenterPositionSync(position, PLAYER_HITBOX_SIZE);

	/////*照準の当たり判定の更新*/
	sight.hitboxsync(position);

	return 0;
}
int Player::AnimationUpdate(){

	////*自機のアニメーション番号の進行*/

		//被弾していない場合
	if (shootdown == false) {
		if (ownframecount % 12 == 0) {
			anim++;		//アニメーション番号を進める
			Clamp(anim, 2, 4);		//プレイヤーのanim番号をループさせる
			ownframecount = 0;
		}
	}
	else {
		if (ownframecount % 20 == 0)	return 2;
	}

	return 0;
}
//
//int Player::AirEnemyCollision()
//{
//	return 0;
//}
//
//int Player::EnemyBulletCollision(std::shared_ptr<
// > EB)
//{
//	for (int i = 0; i < EB->EnemyshotSize(); i++)
//	{
//		shootdown = hitbox.BoxCollision(EB->GetEnemyShotArray(i).GetHitbox());
//	}
//
//	return 0;
//}
//
////===============================================================
////				ショットの描画
//// 
//// フラグが建っているショットを描写する。見た目上は二つ弾があるが判定は一つだけ
//// ・左の弾の描写
//// ・右の弾の描写
////===============================================================
//void Shot_Draw(P_SHOT_ST _s[], Bmp _bmpR, Bmp _bmpL) {
//	for (int r = 0; r < MAX_SHOT; r++) {
//		if (_s[r].F == true) {
//			DrawBmp(_s[r].hitbox.left - BULLET_SIZE, _s[r].hitbox.top, &_bmpL);		//ショット(左)の描写
//			DrawBmp(_s[r].hitbox.right, _s[r].hitbox.top, &_bmpR);		//ショット(右)の描写
//		}
//	}
//}
////===============================================================
////				ボムの描写
//// 
//// フラグが建っている間のみボムを描写する。攻撃判定を出している間はなにも表示しない
//// ・ボムの描写
////===============================================================
//void Bom_Draw(P_BOM_ST* _b, Bmp _bmp) {
//	if (_b->F == true) {
//		DrawBmp(_b->center_x - BULLET_SIZE, _b->center_y - BULLET_SIZE, &_bmp);		//ボムの描写
//	}
//}