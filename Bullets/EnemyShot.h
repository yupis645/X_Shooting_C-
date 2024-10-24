#ifndef ENEMYSHOT_H
#define ENEMYSHOT_H

class Vector2;

#include "BulletBase.h"
#include <iostream>

//===================================================================================
//                  敵のショット
//===================================================================================
class EnemyShot : public BulletBase {
public:
    EnemyShot();     //コンストラクタ

    int Create(Vector2 startPos, Vector2 targetPos, float radianplus );
    int Init();
    int Update(int framecount) ;


private:
    float rad;			//進む角度(発射する際のプレイヤーに対する角度)
};

#endif //ENEMYSHOT_H