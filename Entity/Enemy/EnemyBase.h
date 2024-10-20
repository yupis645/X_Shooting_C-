#pragma once
#include "Game.h"
#include "IPlayer.h"

class EnemyBase:public GameObject {
public:
	EnemyBase();
	~EnemyBase(){}

	virtual int Init() = 0;
	virtual Vector2 Enemy_Patterns( int movepattrnnumber);

	virtual int Create(int number,int typenumber) = 0;
	virtual int AnimUpdate(int framecount, int updatecount) = 0;
	virtual int ActionUpdate(int framecount) = 0;
	virtual int UniqueUpdate(int framecount) = 0;
	virtual int Draw() = 0;


	virtual void Setshootdown(bool value) { shootdown = value; }

protected:
	EnemyStatusData status;
	bool shootdown;			//被弾判定
	int back_num;		//配置されている裏マップの番号
	int back_coord;		//裏マップにおける配置
	int type;		//同一個体の違う挙動
	int direction;		//向き
	int currentanim_number;		//アニメーションパターンの切り替えタイミング
	int actionpattern;		//行動パターン番号
	int ownframecount;	//初期化された瞬間からカウントを開始する(行動パターンに使用する)
	int currentspeed;
	float radian;
	Vector2 moving;
};