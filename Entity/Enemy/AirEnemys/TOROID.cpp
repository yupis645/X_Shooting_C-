#include "AirEnemyBase.h"

#include "common.h"
#include "Player.h"


namespace {
	constexpr int   ANIM_UPDATE_INTERVAL = 5;
	constexpr float DECELERATION       = 5;
	constexpr int   DECELERATION_LINIT   = 5;
}


TOROID::TOROID(std::weak_ptr<IPlayer> player, int num)
{
	Create(player, num);
}

void TOROID::Init(){
	EnemyBase::Init();
}

int TOROID::Create( std::weak_ptr<IPlayer> player,int number)
{
	auto useplayer = player.lock();

	EnemyBase::StatusSetup(EnemyStatusData::TOROID);


	AirEnemyBase::InitPostionPattern(useplayer->GetPosition().x);

	AirEnemyBase::Create(useplayer, number);

	return 0;
}

int TOROID::Update(std::weak_ptr<IPlayer> player)
{
	return  AirEnemyBase::Update(player);
}


int TOROID::UniqueUpdate(std::weak_ptr<IPlayer> player)
{
	auto useplayer = player.lock();

	if(ownframecount < 5) TergetRadian(useplayer->GetPosition());

	//被弾判定がtrueの場合
	AirEnemyBase::AnimUpdate(ANIM_UPDATE_INTERVAL);

	/*弾を撃つ前の動き*/
	if (actionpattern == 0)
	{
		return ActionPattern01(useplayer->GetHitbox(), useplayer->GetPosition());
	}

	if (actionpattern == 1) 
	{
		ActionPattern02();
	}
	if (actionpattern == 2) 
	{
		ActionPattern03();
	}
	return 0;
}

int TOROID::ActionPattern01(const Boxcollider& playerhitbox, const Vector2& playerpos)
{
	//出現時にプレイヤーがいた座標に向かって進む

		Enemy_Patterns(MovePatternID::TowardsPlayer);		//行動パターン 0:自機に向かう

		/*Y軸の距離関係なくプレイヤーのの当たり判定とX軸が重なったら*/
		if (playerhitbox.left <= position.x  &&
			playerhitbox.right >= position.x &&
			playerpos.y > position.y) {		//自機とY軸が一致したとき


			actionpattern++;			//減速パターンへ移行する

			direction = position.x > playerpos.x ? -1 : 1;	//プレイヤーとの位置関係によって向きを再設定する

			return OnBulletShot;

		}
	return 0;
}

void TOROID::ActionPattern02()
{	//一定速度に落ちるまで減速する
	Enemy_Patterns(MovePatternID::TowardsPlayer);		//行動パターン 0:自機に向かう

	status.speed -= 0.2f;					            //減速
	if (status.speed < 0.6)  actionpattern = 2; 		//速度が0.6を下回ったら逃走パターンに移行する
}

void TOROID::ActionPattern03()
{
	//反対方向に向かって逃走する
	Enemy_Patterns(MovePatternID::EscapeX);		//行動パターン 5:加速度を加算しつつｘ軸方向に逃げる


}


