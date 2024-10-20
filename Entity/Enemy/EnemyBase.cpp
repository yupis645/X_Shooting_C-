#include "EnemyBase.h"


//==========================================================
//				コンストラクタ
//==========================================================
EnemyBase::EnemyBase() :shootdown(false), back_num(0), back_coord(0), type(0), direction(0),
						currentanim_number(0), actionpattern(0), ownframecount(0), radian(0), currentspeed(0), moving(Vector2::zero)
{}


//==========================================================
//				初期化
//==========================================================

int EnemyBase::Init()
{
	status.Init();
	shootdown = false;			//被弾判定
	back_num = 0;		//配置されている裏マップの番号
	back_coord = 0;		//裏マップにおける配置
	type = 0;		//同一個体の違う挙動
	direction = 0;		//向き
	currentanim_number = 0;		//アニメーションパターンの切り替えタイミング
	actionpattern = 0;		//行動パターン番号
	ownframecount = 0;	//初期化された瞬間からカウントを開始する(行動パターンに使用する)
	currentspeed = 0;
	radian = 0;
	moving = 0;
	Vector2::zero;

	return 0;
}


Vector2 EnemyBase::Enemy_Patterns(int movepattrnnumber)
{
	int dir_search = CHIP_SIZE + (CHIP_SIZE - (CHIP_SIZE * currentspeed));

	switch (movepattrnnumber) {
		/*自機に向かって進む*/
	case 0:

		position.x += (float)currentspeed * cos(radian);		//X軸の移動
		position.y += (float)currentspeed * sin(radian);		//Y軸の移動
		break;


		/*Y軸の位置に関係なく自機の方向に向かう*/
	case 1:
		position.x += (float)currentspeed * cos(radian);		//X軸の移動
		position.y += currentspeed;
		break;

		/*画面の下から出現する*/
	case 2:
		if (ownframecount <= 5) {
			position.y = SRN_H;
		}
		position.x += (float)currentspeed * cos(radian);		//X軸の移動
		position.y -= currentspeed;		//Y軸の移動
		break;
		/*そのまま直進する*/
	case 3:
		position.y += (float)currentspeed;		//Y軸の移動
		break;
		/*加速度を加算しつつdirの方へ移動する*/
	case 4:
		position.x -= (float)1 * cos(radian) * direction;		//X軸の移動
		position.y -= (float)currentspeed * status.acceleration;		//Y軸の移動

		/*加速*/
		currentspeed += currentspeed * status.acceleration;

		break;

		/*加速度を加算しつつｘ軸方向に逃げる*/
	case 5:
		position.y++;
		position.x -= (float)currentspeed * direction;		//X軸の移動
		/*加速*/
		currentspeed += currentspeed * status.acceleration;
		break;

	}

	return 0;
}
