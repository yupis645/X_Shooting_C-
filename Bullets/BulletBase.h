#ifndef BULLETBASE_H
#define BULLETBASE_H

#include "Geometry.h"
#include "Game.h"

//===================================================================================
//                  発射物の基底クラス
//===================================================================================
class BulletBase  :public GameObject{
public:
    BulletBase() {}
    Vector2 GetDrawPos()
    {
        return position;
    }

    ~BulletBase() = default;

protected:

};


#endif //BULLETBASE_H