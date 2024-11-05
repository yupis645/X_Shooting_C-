#ifndef IBULLETMANAGER_H
#define IBULLETMANAGER_H

//---------------------------------------------------------------------------------------------------------------
//                                     �e���Ǘ�����N���X(�C���^�[�t�F�[�X)
//---------------------------------------------------------------------------------------------------------------

class BulletBase;
class Vector2;
class PlayerShot;
class PlayerBom;
class EnemyShot;

class IBulletsManager {
public:
    ~IBulletsManager() = default;

    // �e�𐶐�����֐�
    virtual void CreatePlayerShot(Vector2 pos) = 0;
    virtual void CreatePlayerBom(Vector2 pos) = 0;
    virtual void CreateEnemyShot(Vector2 startPos, Vector2 targetPos, float radianplus = 0) = 0;
    
    //Scene�Ǘ��N���X�ɌĂяo������֐�
    virtual int Update(int framecount) = 0;
    virtual int Draw() = 0;

    //�e�̃X�e�[�^�X������������֐�
    virtual void InitPlayerShot() = 0;
    virtual void InitPlayerBom() = 0;
    virtual void InitEnemyShot() = 0;

    //�e�̏����X�V����֐�
    virtual void UpdatePlayerShot(int frameocunt) = 0;
    virtual void UpdatePlayerBom(int frameocunt) = 0;
    virtual void UpdateEnemyShot(int frameocunt) = 0;

    //Active�Ȓe����ʂɕ`�悳����
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