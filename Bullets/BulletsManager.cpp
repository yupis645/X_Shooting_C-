
//---------------------------------------------------------------------------------------------------------------------------
//                                  �e���Ǘ�����N���X
// 
// �G�̒e�A�v���C���[�̒e�A�v���C���[�̒n��G�ɑ΂��锚�e�@�����3�̒e���Ǘ�����B
// �����A�������A�X�V�A�`��@�̊֐�������B
//---------------------------------------------------------------------------------------------------------------------------

#include "BulletsManager.h"

#include "SpriteRenderer.h"
#include "ResourceManager.h"

// �ėp�֐�
namespace Utils {

    //==========================================================================================
    //                          �C���f�b�N�X�����֐�
    //==========================================================================================
    template<typename BulletType, std::size_t N>
    size_t FindActiveIndex(const std::array<std::shared_ptr<BulletType>, N>& bullet, bool isActive) {
        for (std::size_t i = 0; i < bullet.size(); ++i) {           //����1����z��̗v�f���������o��
            if (bullet[i] && bullet[i]->GetActive() == isActive) {  //�e��active�ϐ�������2�ƈ�v���Ă��邩�m�F����
                return i;                         //�������������炻��index�ԍ���Ԃ�
            }
        }
        return -1;                                                  //������Ȃ�������-1��Ԃ�
    }
}

//==========================================================================================
//                          �R���X�g���N�^
//
// �`��N���X�ƃ��\�[�X�N���X���󂯂Ƃ�A�`��N���X�̓����o�ϐ��ɑ�����A���\�[�X�N���X����͉摜���擾����
// �e��e�̉��������s���B
//==========================================================================================
BulletsManager::BulletsManager(std::shared_ptr<ResourceManager> rm, std::shared_ptr<SpriteRenderer> sr) :
    shottex(rm->GetTexture(TextureType::Bullet)),   //�e�̉摜���擾
    bomtex(rm->GetTexture(TextureType::Bom)),       //�{���̉摜���擾
    render_(sr)                                     //�`��N���X�̃X�}�[�g�|�C���^�̎擾
{
    //�e�̉�����
    for (auto& shot : playershots) {        
        shot = std::make_shared<PlayerShot>();      //playershot�̉�����
    }
    for (auto& e_shot : enemyshots) {
        e_shot = std::make_shared<EnemyShot>();     //enemyshot�̉�����
    }
    playerboms = std::make_shared<PlayerBom>();     //playerbom�̉�����

}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                 �O���N���X�ɓn���R��ނ̏������܂Ƃ߂��֐�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//==========================================================================================
//                         1�t���[�����Ƃ̃f�[�^�̍X�V
//==========================================================================================
int BulletsManager::Update(int framecount) {
    UpdatePlayerShot(framecount);
    UpdatePlayerBom(framecount);
    UpdateEnemyShot(framecount);

    return 0;

}

//==========================================================================================
//                              �`��
//==========================================================================================
int BulletsManager::Draw() {

    DrawPlayerShot();
    DrawPlayerBom();
    DrawEnemyShot();

    return 0;

}
                 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      �v���C���[�̒e
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//==========================================================================================
//                              ����
//==========================================================================================
void BulletsManager::CreatePlayerShot(Vector2 pos) {            // ����1:player�̍��W
    int index = Utils::FindActiveIndex(playershots, false);     //���˃t���O�������Ă��Ȃ��V���b�g�ԍ���T��
    if (index == -1) return;                                    //�Ԃ�l��-1�Ȃ�S�ăt���O�������Ă���̂Ő������Ȃ�
    playershots[index]->Create(pos);                            //index�����������炻��index�Œe�𐶐�����
};

//==========================================================================================
//                              ������
//==========================================================================================
void BulletsManager::InitPlayerShot() {
    for (size_t i = 0; i < playershots.size(); i++) {
        playershots[i]->Init();
    }
}


//==========================================================================================
//                               �X�V
// ����:�t���[���J�E���g
//==========================================================================================
void BulletsManager::UpdatePlayerShot(int frameocunt) {
    for (size_t i = 0; i < playershots.size(); i++) {
        if (playershots[i]->GetActive()) {					//�V���b�g�t���O��ON�Ȃ�
            playershots[i]->Update(frameocunt);
        }
    }
}



//==========================================================================================
//                              �`��
// 
// player�̒e�̌����ڂ͑o���Ȃ̂ŉ摜���g���B
// ���ꂼ�ꒆ����x���W����SHOT_SPEED_HOLLOW���ꂽ�ʒu�ɕ\������
//==========================================================================================
void BulletsManager::DrawPlayerShot() {
    for (size_t i = 0; i < playershots.size(); i++) {
        if (playershots[i]->GetActive()) {					//�V���b�g�t���O��ON�Ȃ�
            int left_x = static_cast<int>(playershots[i]->GetDrawPos().x - PlayerConfig::SHOT_SPEED_HOLLOW);
            int right_x = static_cast<int>(playershots[i]->GetDrawPos().x + PlayerConfig::SHOT_SPEED_HOLLOW);
            int y = static_cast<int>(playershots[i]->GetDrawPos().y);

            render_->DrawFromCenterPos(shottex, 0, left_x, y, PlayerConfig::SHOT_PIC_SIZE);
            render_->DrawFromCenterPos(shottex, 0, right_x, y, PlayerConfig::SHOT_PIC_SIZE);
        }
    }
}


//==========================================================================================
//                              �T�C�Ygetter
//==========================================================================================
int BulletsManager::GetPlayershotSum()
{
    return playershots.size();
}


//==========================================================================================
//                              index�w��getter
// ����:�擾������index�ԍ�
//==========================================================================================
std::shared_ptr<PlayerShot> BulletsManager::GetPlayerShotIndex(int i)
{
    return playershots[i];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                         �v���C���[�̃{��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//==========================================================================================
//                         ����
// ����1:player�̍��W
//==========================================================================================
void BulletsManager::CreatePlayerBom(Vector2 pos) {
    if (!playerboms->GetActive()) {
        playerboms->Create(pos);
        return;

    }

}

//==========================================================================================
//                              ������
//==========================================================================================
void BulletsManager::InitPlayerBom() {
    playerboms->Init();
}


//==========================================================================================
//                              �X�V
// ����:�t���[���J�E���g
//==========================================================================================
void BulletsManager::UpdatePlayerBom(int frameocunt) {
    if (playerboms->GetActive()) {
        playerboms->Update(frameocunt, PlayerConfig::BOM_SPEED);
    }
}


//==========================================================================================
//                              �`��
// 
// Active��true ���� �����O�̓{���̉摜��`�悷��
// �������Ă���Ԃ�Active��true�ł��`�悵�Ȃ�
//==========================================================================================
void BulletsManager::DrawPlayerBom() {
    if (playerboms->GetActive() && !playerboms->GetIsBomber()) {
        render_->DrawFromCenterPos(bomtex, 0, playerboms->GetDrawPos(), PlayerConfig::BON_PIC_SIZE);
    }
}

//==========================================================================================
//                              bom�̃Q�b�^�[
//==========================================================================================
std::shared_ptr<PlayerBom> BulletsManager::GetPlayerBom()
{
    return playerboms;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                         �G�̒e
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//==========================================================================================
//                         ����
// ����1:�e�𔭎˂���G�̍��W , ����2:player�̍��W , ����3:���ˊp�x�̎w��(�K�v�����)
//==========================================================================================
void BulletsManager::CreateEnemyShot(Vector2 startPos, Vector2 targetPos, float radianplus = 0) {
    int index = Utils::FindActiveIndex(enemyshots, false);
    if (index == -1) return;
    enemyshots[index]->Create(startPos, targetPos, radianplus);

};

//==========================================================================================
//                              ������
//==========================================================================================
void BulletsManager::InitEnemyShot() {
    for (size_t i = 0; i < enemyshots.size(); i++) {
        enemyshots[i]->Init();
    }
}


//==========================================================================================
//                              �X�V
// ����1:�t���[���J�E���g
//==========================================================================================
void BulletsManager::UpdateEnemyShot(int frameocunt) {
    for (size_t i = 0; i < enemyshots.size(); i++) {
        if (enemyshots[i]->GetActive()) {					//�V���b�g�t���O��ON�Ȃ�
            enemyshots[i]->Update(frameocunt);
        }
    }
}

//==========================================================================================
//                              �`��
//==========================================================================================
void BulletsManager::DrawEnemyShot() {
    for (size_t i = 0; i < enemyshots.size(); i++) {
        if (enemyshots[i]->GetActive()) {					//�V���b�g�t���O��ON�Ȃ�`��
            render_->DrawFromCenterPos(shottex, 0, enemyshots[i]->GetDrawPos(),EnemyShotConfig::PIC_SIZE);
        }
    }
}


//==========================================================================================
//                              �T�C�Ygetter
//==========================================================================================
int BulletsManager::GetEnemyshotSum()
{
    return enemyshots.size();
}


//==========================================================================================
//                              index�w��getter
// ����:�擾������index�ԍ�
//==========================================================================================
std::shared_ptr<EnemyShot> BulletsManager::GetEnemyShotIndex(int i)
{
    return enemyshots[i];

}
