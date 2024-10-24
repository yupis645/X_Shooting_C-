#ifndef BULLETBASE_H
#define BULLETBASE_H

#include "Geometry.h"
#include "Game.h"

//===================================================================================
//                  ”­ŽË•¨‚ÌŠî’êƒNƒ‰ƒX
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