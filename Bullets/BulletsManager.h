#ifndef BULLETSMANAGER_H
#define BULLETSMANAGER_H

class Vector2;

class SpriteRenderer;
class ResourceManager;
class GameTexture;

#include "IBulletsManager.h"
#include "PlayerBom.h"
#include "PlayerShot.h"
#include "EnemyShot.h"


//===================================================================================
//                  ��ʏ�̔��˕��̊Ǘ�
//===================================================================================
class BulletsManager : public IBulletsManager  {
public:
    //�R���X�g���N�^
    BulletsManager(std::shared_ptr<ResourceManager> rm, std::shared_ptr<SpriteRenderer> sr);

    // �v���C���[�̒e
    void CreatePlayerShot(Vector2 pos)override;     
    void InitPlayerShot() override;

    //�v���C���[�̃{��
    void CreatePlayerBom(Vector2 pos )override;
    void InitPlayerBom() override;

    //�G�̒e
    void CreateEnemyShot(Vector2 startPos, Vector2 targetPos, float dir)override;
    void InitEnemyShot()override;

    //�R��ނ̋��ʏ������܂Ƃ߂��֐�
    int Update(int framecount);
    int Draw();

    ~BulletsManager() = default;        //�f�X�g���N�^

public:     //�Q�b�^�[/�Z�b�^�[
    int GetEnemyshotSum() override;
    int GetPlayershotSum() override;

    std::shared_ptr<EnemyShot> GetEnemyShotIndex(int i) override;
    std::shared_ptr<PlayerShot> GetPlayerShotIndex(int i) override;
    std::shared_ptr<PlayerBom> GetPlayerBom() override;


protected:    //�����Ŏg���ʂ̍X�V�ƕ`��֐�(�e�X�g�N���X�ł��g����悤��protected)
    void DrawPlayerShot()override;
    void UpdatePlayerShot(int frameocunt) override;

    void DrawPlayerBom()override;
    void UpdatePlayerBom(int frameocunt)override;

    void UpdateEnemyShot(int frameocunt)override;
    void DrawEnemyShot()override;

private :
    std::array<std::shared_ptr<PlayerShot>, PlayerConfig::MAX_SHOT> playershots;
    std::shared_ptr<PlayerBom> playerboms;  // Player �N���X�ւ̈ˑ�
    std::array<std::shared_ptr<EnemyShot>, EnemyShotConfig::MAX_SHOT> enemyshots;
  
    std::shared_ptr<SpriteRenderer> render_;

    std::shared_ptr<GameTexture> shottex;
    std::shared_ptr<GameTexture> bomtex;

};

#endif //BULLETSMANAGER_H