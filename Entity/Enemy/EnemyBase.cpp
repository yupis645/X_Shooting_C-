#include "EnemyBase.h"

#include "common.h"
#include "IPlayer.h"


namespace {
	constexpr int OWNFRAMECOUNT_LIMIT = 1000;

}

//==========================================================
//				コンストラクタ
//==========================================================
EnemyBase::EnemyBase() :status(EnemyStatusData::DUMMY),shootdown(false), back_num(0), back_coord(0), direction(0), actionpattern(0),
						currentanimnum(0),  ownframecount(0), radian(0), moving(Vector2::zero)
{}


//==========================================================
//				初期化
//==========================================================

void EnemyBase::Init()
{
	EnemyStatus status = EnemyStatusData::DUMMY;
	back_num = 0;		//配置されている裏マップの番号
	back_coord = 0;		//裏マップにおける配置
	direction = 0;		//向き
	actionpattern = 0;
	currentanimnum = 0;		//アニメーションパターンの切り替えタイミング
	ownframecount = 0;	//初期化された瞬間からカウントを開始する(行動パターンに使用する)
	radian = 0;
	moving = 0;
	Vector2::zero;
	GameObject::InitClear();
}



Vector2 EnemyBase::Enemy_Patterns(MovePatternID id)
{

	switch (id) {
		/*自機に向かって進む*/
	case MovePatternID::TowardsPlayer:
		position.x += status.speed * cos(radian);		    //X軸の移動
		position.y += status.speed * sin(radian);		    //Y軸の移動
		break;

		/*自機とは逆方向に進む*/
	case MovePatternID::ReverseTowardsPlayer:
		position.x -= status.speed * cos(radian);		    //X軸の移動
		position.y -= status.speed * sin(radian);		    //Y軸の移動
		break;

		/*Y軸の位置に関係なく自機の方向に向かう*/
	case MovePatternID::HorizontalTrack:
		position.x += status.speed * cos(radian);		    //X軸の移動
		position.y += status.speed;
		break;

		/*画面の下から出現する*/
	case MovePatternID::AppearFromBottom:
		position.x += status.speed * cos(radian);		    //X軸の移動
		position.y -= status.speed;		                    //Y軸の移動
		break;
		/*そのまま直進する*/
	case MovePatternID::StraightAccelerate:
		position.y += status.speed;		                    //Y軸の移動
		break;

		/*加速度を加算しつつdirの方へ移動する*/
	case MovePatternID::AccelerateTowardsDir:
		position.x -= 1.0f * cos(radian) * direction;		//X軸の移動
		position.y -= status.speed * status.acceleration;	//Y軸の移動

		/*加速*/
		status.speed += status.speed * status.acceleration;

		break;


		/*加速度を加算しつつｘ軸方向に逃げる*/
	case MovePatternID::EscapeX:
		position.y++;
		position.x -= status.speed * direction;		        //X軸の移動
		/*加速*/
		status.speed += status.speed * status.acceleration;
		break;

	}

	return 0;

}


void EnemyBase::StatusSetup(const EnemyStatus& initstatus)
{
	//基礎ステータスをコピー or 各値のセット
	status = initstatus;


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
