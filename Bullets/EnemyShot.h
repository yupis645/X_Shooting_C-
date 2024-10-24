#ifndef ENEMYSHOT_H
#define ENEMYSHOT_H

class Vector2;

#include "BulletBase.h"
#include <iostream>

//===================================================================================
//                  �G�̃V���b�g
//===================================================================================
class EnemyShot : public BulletBase {
public:
    EnemyShot();     //�R���X�g���N�^

    int Create(Vector2 startPos, Vector2 targetPos, float radianplus );
    int Init();
    int Update(int framecount) ;


private:
    float rad;			//�i�ފp�x(���˂���ۂ̃v���C���[�ɑ΂���p�x)
};

#endif //ENEMYSHOT_H