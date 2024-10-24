#include "EnemyBase.h"

#include "common.h"
#include "IPlayer.h"


namespace {
	constexpr int OWNFRAMECOUNT_LIMIT = 1000;

}

//==========================================================
//				コンストラクタ
//==========================================================
EnemyBase::EnemyBase() :shootdown(false), back_num(0), back_coord(0), type(0), direction(0),
						currentanimnum(0),  ownframecount(0), radian(0), currentspeed(0), moving(Vector2::zero)
{}


//==========================================================
//				初期化
//==========================================================

void EnemyBase::Init()
{
	status.Init();
	shootdown = false;			//被弾判定
	back_num = 0;		//配置されている裏マップの番号
	back_coord = 0;		//裏マップにおける配置
	type = 0;		//同一個体の違う挙動
	direction = 0;		//向き
	currentanimnum = 0;		//アニメーションパターンの切り替えタイミング
	ownframecount = 0;	//初期化された瞬間からカウントを開始する(行動パターンに使用する)
	currentspeed = 0;
	radian = 0;
	moving = 0;
	Vector2::zero;
}


Vector2 EnemyBase::Enemy_Patterns(int movepattrnnumber)
{
	int dir_search = MapConfig::CHIP_SIZE + (MapConfig::CHIP_SIZE - (MapConfig::CHIP_SIZE * currentspeed));

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
			position.y = ScreenConfig::SRN_H;
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


void EnemyBase::StatusSetup(int number, int typenumber)
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

}

void EnemyBase::OwnFrameCountUpdate()
{
	ownframecount++;

	int Limit = OWNFRAMECOUNT_LIMIT;	//Clampで使うためにintに変換
	Clamp(ownframecount, 0, Limit);
}
