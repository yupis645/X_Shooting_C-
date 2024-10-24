#ifndef ENEMYBASE_H
#define ENEMYBASE_H

class IPlayer;
class Vector2;

#include "Game.h"

class EnemyBase:public GameObject {
public:
	EnemyBase();
	~EnemyBase(){}
	enum UpdateReturnID {
		Error= 99,
		OnBulletShot = 2,
	};

	virtual void Init() ;

	virtual int Create(std::shared_ptr<IPlayer> pl,int number,int typenumber = 0) = 0;

	virtual int Update(std::shared_ptr<IPlayer> pl) = 0;
	virtual int UniqueUpdate(std::shared_ptr<IPlayer> pl) = 0;

	virtual int AnimUpdate(int UpdateInterval) = 0;


	virtual void Setshootdown(bool value) { shootdown = value; }

protected:
	EnemyStatusData status;
	bool shootdown;			//被弾判定
	int back_num;		//配置されている裏マップの番号
	int back_coord;		//裏マップにおける配置
	int type;		//同一個体の違う挙動
	int direction;		//向き
	int currentanimnum;		//アニメーションパターンの切り替えタイミング
	int actionpattern;		//行動パターン番号
	int ownframecount;	//初期化された瞬間からカウントを開始する(行動パターンに使用する)
	float currentspeed;
	float radian;
	Vector2 moving;

	Vector2 Enemy_Patterns(int movepattrnnumber);
	void StatusSetup(int number, int typenumber = 0);
	void OwnFrameCountUpdate();

};

#endif //ENEMYBASE_H