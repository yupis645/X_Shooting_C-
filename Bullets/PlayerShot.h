#ifndef PLAYERSHOT_H
#define PLAYERSHOT_H

#include "BulletBase.h"

class PlayerShot : public BulletBase{
public:
    //�R���X�g���N�^
    PlayerShot() { }

    int Create(Vector2 pos) ;

    int Init();
    int Update(int framecount) ;

    ~PlayerShot() = default;

};

#endif //PLAYERSHOT_H