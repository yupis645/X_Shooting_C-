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
		Error= 99,				//もしエラーを出したかったらこれを使う
		OnBulletShot = 2,		//弾を発射する
	};
	enum class MovePatternID {
		TowardsPlayer,          // 自機に向かって進む
		ReverseTowardsPlayer,   // 自機とは逆方向に進む
		HorizontalTrack,        // Y軸の位置に関係なく自機の方向に向かう
		AppearFromBottom,       // 画面の下から上に向かう
		StraightAccelerate,     //直進しながら加速する
		AccelerateTowardsDir,   // 加速度を加算しつつdirの方へ移動する
		EscapeX                 // 加速度を加算しつつx軸方向に逃げる
	};

	virtual void Init() ;
	
	void Setshootdown(bool value) { shootdown = value; }
	int GetNumber() { return status.number; }
	int GetAnimNum() { return currentanimnum; }
	int GetPicSize() { return status.pic_size; }

protected:
	EnemyStatus status;
	bool shootdown;		//被弾判定
	int back_num;		//配置されている裏マップの番号
	int back_coord;		//裏マップにおける配置
	int currentanimnum;	//アニメーションパターンの切り替えタイミング
	int actionpattern;	//行動パターン番号
	int ownframecount;	//初期化された瞬間からカウントを開始する(行動パターンに使用する)
	float radian;		//弾の発射角度
	int direction;		//向き
	Vector2 moving;		//移動座標

	Vector2 Enemy_Patterns(MovePatternID id);
	void StatusSetup(const EnemyStatus& initstatus);
	void OwnFrameCountUpdate();

};

#endif //ENEMYBASE_H