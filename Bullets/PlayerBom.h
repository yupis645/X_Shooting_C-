#ifndef PLAYERBOM_H
#define PLAYERBOM_H

class Vector2;

#include "BulletBase.h"

class PlayerBom : public BulletBase {
public:
    PlayerBom() : range(0), bomber(false), bombertime(0){ }   //�R���X�g���N�^

    int Create(Vector2 pos);
    int Init();
    int Update(int _frameC,float shootspeed) ;

    bool GetIsBomber() { return bomber; }

private:
    int range;			//�˒�����
    bool bomber;		//�����t���O(�U������)
    int bombertime;

    
    void FallUpdate();     //�����O�̍X�V
    void BomberUpdate(int framecount);      //������̍X�V
};

#endif //PLAYERBOM_H