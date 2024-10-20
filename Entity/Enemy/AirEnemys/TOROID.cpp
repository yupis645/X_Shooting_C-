#include "TOROID.h"


int TOROID::Init(){
	EnemyBase::Init();
}

int TOROID::Create(int number, int typenumber)
{

	type = typenumber;

	//numberの百の位はエネミーのTypeを表す(100 = Type:1 , 200 = Type:2)
	if (number >= 100) {
		type = number / 100;								//ナンバーを100で割ってTypeを取り出す
		number = number - (100 * type);						//100の位を取り除いた敵のナンバーを取り出す
	}


	//_e->enemy[EmptyNum] = A_enemyDate[number];
	//基礎ステータスをコピー or 各値のセット
	status = A_ENEMY_DATA_ARRAY[number];

	currentspeed = status.speed;

	//出現位置の設定
	//if (number == 0 || number == 4 || number == 6) {		//対象:トーロイド,ジアラ,テラジ
		position.x = player_->GetPosition().x + 250 + (rand() % 200);		//player_から 250 離れた位置から更に 0～200 の乱数を加算したX座標を指定 
	//}
	//else {													//それ以外
	//	_e->enemy[EmptyNum].center_x = (float)(rand() % SRN_W + 1); 			//画面の横サイズに収まる範囲でランダムなX座標を指定
	//}

	//もし乱数で取得したX座標が画面の横サイズを超えていたら
	if (position.x >= SRN_W) { position.x = player_->GetPosition().x - 350 + (rand() % 200); }

	/*複数の行動パターンのある敵のステータス変更*/
	////ジソー
	//if (_e->enemy[EmptyNum].number == 3) {
	//	if (_e->enemy[EmptyNum].type > 0 && _e->enemy[EmptyNum].type < 3) { _e->enemy[EmptyNum].points = 100; }	//Typeによる得点の変動
	//}
	////ザガート
	//else if (_e->enemy[EmptyNum].number == 7) {
	//	if (_e->enemy[EmptyNum].type == 0) { _e->enemy[EmptyNum].points = 100; }
	//	if (_e->enemy[EmptyNum].type == 1) { _e->enemy[EmptyNum].points = 150;	_e->enemy[EmptyNum].speed = 4.0; }
	//	if (_e->enemy[EmptyNum].type == 2) { _e->enemy[EmptyNum].points = 200; }
	//	if (_e->enemy[EmptyNum].type == 3) { _e->enemy[EmptyNum].points = 300;	_e->enemy[EmptyNum].speed = 4.0; }
	//}

	/*画像を代入する*/
	//LoadDivBmp(PngData.A_Enemy, 0, 0, _e->enemy[EmptyNum].pic_size, _e->enemy[EmptyNum].pic_size, A_ENEMY_PIC_LINE, 11, _e->enemy[EmptyNum].pic);

	/*中心座標から'当たり判定'と'画像'の左上と右下の座標*/
	//Hitbox_Sync(&_e->enemy[EmptyNum].hitbox, _e->enemy[EmptyNum].hitbox_size,				//RECT:当たり判定 , int:当たり判定の中心座標から見たサイズ
	//	&_e->enemy[EmptyNum].center_x, &_e->enemy[EmptyNum].center_y,						//float:中心座標(X) , 中心座標(Y)
	//	&_e->enemy[EmptyNum].pic_x, &_e->enemy[EmptyNum].pic_y, _e->enemy[EmptyNum].pic_size);	//int:画像左上のx座標 , 画像左上のy座標 , int:画像のサイズ
	hitbox.CenterPositionSync(position, status.hitbox_size);

	/*画面の中心を軸に左右どちらに寄っているかによって最初の進行方向をさだめる*/
	direction = hitbox.left < CENTER_X ? -1 : 1;

	return 0;
}

int TOROID::ActionUpdate(int framecount)
{

	bool frame_out = false;					//画面から消去するかを判定をする(処理の中でtrueになった場合、処理の最期で画面から削除 & 情報の初期化を行う)

	ownframecount++;				//敵一体についている個別のタイマーを進める(行動処理に使う)

	//被弾判定がtrueの場合
	if (shootdown == true) {
		if (ownframecount % 2 == 0) {		//2フレームに一度入る
			currentanim_number++;					//anim変数を加算する(爆発アニメーションの進行)
		}
		if ( currentanim_number> 11) {				//anim変数が 11よりも大きくなったら
			InitClear();
		}
	}

	//以下は被弾判定が出ていない場合に処理に進む

	UniqueUpdate(framecount);		//敵の行動(numberによって異なる挙動をする)

	hitbox.CenterPositionSync(position, status.hitbox_size);
	////当たり判定の同期
	//Hitbox_Sync(&_e->enemy[r].hitbox, _e->enemy[r].hitbox_size,				//RECT:当たり判定 , int:当たり判定の中心座標から見たサイズ
	//	&_e->enemy[r].center_x, &_e->enemy[r].center_y,						//float:中心座標(X) , 中心座標(Y)
	//	&_e->enemy[r].pic_x, &_e->enemy[r].pic_y, _e->enemy[r].pic_size);


	//座標が画面外に出た場合の座標の初期化
	if (ownframecount > 50) {				//出現してから50フレーム立ってから判定に入る(出現してしばらくは画面端に当たっていても消去しない)
		if (hitbox.BoxCollision( winView) == false)		//当たり判定とウィンドウサイズのRECTと重なっていない = 画面外 なら
		{
			InitClear();
		}
	}
	return 0;
}


int TOROID::UniqueUpdate(int framecount)
{
	currentanim_number = AnimUpdate(framecount, 5);	//アニメーションの進行

	/*弾を撃つ前の動き*/
	if (actionpattern == 0) ActionPattern01();
	if (actionpattern == 1) ActionPattern02(framecount);
	if (actionpattern == 2) ActionPattern03(framecount);

	return 0;
}

int TOROID::ActionPattern01()
{
	//出現時にプレイヤーがいた座標に向かって進む

		Enemy_Patterns(0);		//行動パターン 0:自機に向かう

		/*Y軸の距離関係なくプレイヤーのの当たり判定とX軸が重なったら*/
		if (player_->GetHitbox().left <= position.x  &&
			player_->GetHitbox().right >= position.x &&
			player_->GetPosition().y > position.y) {		//自機とY軸が一致したとき

			tiypeaction();

			actionpattern++;			//減速パターンへ移行する

			direction = position.x > player_->GetPosition().x ? -1 : 1;	//プレイヤーとの位置関係によって向きを再設定する
		}
	return 0;
}

int TOROID::ActionPattern02(int framecount )
{	//一定速度に落ちるまで減速する
	Enemy_Patterns(0);		//行動パターン 0:自機に向かう

	currentspeed -= 0.1f;					//減速
	if (currentspeed < 0.6)  actionpattern = 2; 		//速度が0.6を下回ったら逃走パターンに移行する

	return 0;
}

int TOROID::ActionPattern03(int framecount)
{
	//反対方向に向かって逃走する
	Enemy_Patterns(5);		//行動パターン 5:加速度を加算しつつｘ軸方向に逃げる


	//currentanim_number = AnimUpdate(framecount, 5);	//アニメーションの進行


	return 0;
}

int TOROID::tiypeaction()
{
	//type 0 : 特に追加アクションはなし

	//type 1 : プレイヤーに向かって弾を発射する
	if (type == 1) {
		bulletmanager_->CreateEnemyShot(position);	//bulletmanagerで敵の弾を作る
	}


	return 0;
}
