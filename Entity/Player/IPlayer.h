#ifndef IPLAYER_H
#define IPLAYER_H

#include "Geometry.h"

class IPlayer {
public:
    virtual ~IPlayer() = default;       //デストラクタ

    virtual int Init() = 0;                                // 初期化
    virtual int Update(int framecount,Vector2 moveinput) = 0; // 更新処理
    virtual int Draw() = 0;

    //動きに関する関数
    virtual int Move(Vector2 move) = 0;
    virtual int Sync_PositionAndHitbox() = 0;
    virtual int AnimationUpdate() = 0;

    virtual void InitClear() = 0;

    virtual void HitCollision(bool isshootdown) = 0;

    //プロパティ & getter / setter
    virtual bool Getshootdown() const = 0;

	virtual Vector2 GetPosition()const = 0;
	virtual void SetPosition(Vector2 pos) = 0;

	virtual Boxcollider GetHitbox()const = 0;
	virtual void SetHitbox(Boxcollider box) = 0;

	virtual bool GetActive() = 0;

};

#endif // IPLAYER_H