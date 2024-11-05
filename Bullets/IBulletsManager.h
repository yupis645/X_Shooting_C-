#ifndef IBULLETMANAGER_H
#define IBULLETMANAGER_H

//---------------------------------------------------------------------------------------------------------------
//                                     弾を管理するクラス(インターフェース)
//---------------------------------------------------------------------------------------------------------------

class BulletBase;
class Vector2;
class PlayerShot;
class PlayerBom;
class EnemyShot;

class IBulletsManager {
public:
    ~IBulletsManager() = default;

    // 弾を生成する関数
    virtual void CreatePlayerShot(Vector2 pos) = 0;
    virtual void CreatePlayerBom(Vector2 pos) = 0;
    virtual void CreateEnemyShot(Vector2 startPos, Vector2 targetPos, float radianplus = 0) = 0;
    
    //Scene管理クラスに呼び出させる関数
    virtual int Update(int framecount) = 0;
    virtual int Draw() = 0;

    //弾のステータスを初期化する関数
    virtual void InitPlayerShot() = 0;
    virtual void InitPlayerBom() = 0;
    virtual void InitEnemyShot() = 0;

    //弾の情報を更新する関数
    virtual void UpdatePlayerShot(int frameocunt) = 0;
    virtual void UpdatePlayerBom(int frameocunt) = 0;
    virtual void UpdateEnemyShot(int frameocunt) = 0;

    //Activeな弾を画面に描画させる
    virtual void DrawPlayerShot() = 0;
    virtual void DrawPlayerBom() = 0;
    virtual void DrawEnemyShot() = 0;


    //getter / setter
    virtual int GetEnemyshotSum() = 0;
    virtual int GetPlayershotSum() = 0;


    virtual std::shared_ptr<EnemyShot> GetEnemyShotIndex(int i) = 0;
    virtual std::shared_ptr<PlayerShot> GetPlayerShotIndex(int i) = 0;
    virtual std::shared_ptr<PlayerBom> GetPlayerBom() = 0;



};

#endif //IBULLETMANAGER_H