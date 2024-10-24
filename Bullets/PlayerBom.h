#ifndef PLAYERBOM_H
#define PLAYERBOM_H

class Vector2;

#include "BulletBase.h"

class PlayerBom : public BulletBase {
public:
    PlayerBom() : range(0), bomber(false), bombertime(0){ }   //コンストラクタ

    int Create(Vector2 pos);
    int Init();
    int Update(int _frameC,float shootspeed) ;

    bool GetIsBomber() { return bomber; }

private:
    int range;			//射程距離
    bool bomber;		//爆発フラグ(攻撃判定)
    int bombertime;

    
    void FallUpdate();     //爆発前の更新
    void BomberUpdate(int framecount);      //爆発後の更新
};

#endif //PLAYERBOM_H