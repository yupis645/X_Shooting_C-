#include "BulletsManager.h"

#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "GameTexture.h"
#include "IPlayer.h"


BulletsManager::BulletsManager(std::shared_ptr<ResourceManager> rm, std::shared_ptr<SpriteRenderer> sr, std::shared_ptr<IPlayer> lpa) :
    shottex(rm->GetTexture(TextureType::Bullet)),
    bomtex(rm->GetTexture(TextureType::Bom)),
    render_(sr)
{
    for (auto& shot : playershots) {
        shot = std::make_shared<PlayerShot>();
    }
    for (auto& e_shot : enemyshots) {
        e_shot = std::make_shared<EnemyShot>();
    }
    playerboms = std::make_shared<PlayerBom>();

}

// �e�̐����A�Ǘ��֐��Ȃǂ�ǉ�
void BulletsManager::CreatePlayerShot(Vector2 pos) {

    for (size_t i = 0; i < playershots.size(); i++) {	//���˃t���O�������Ă��Ȃ��V���b�g�ԍ���T��
        if (!playershots[i]->GetActive()) {				//�V���b�g�̔��˃t���O�������Ă��Ȃ��ԍ�����������
            playershots[i]->Create(pos);
            return;
        }
    }
};

void BulletsManager::CreatePlayerBom(Vector2 pos) {
    if (!playerboms->GetActive()) {
        playerboms->Create(pos);
        return;

    }

}

void BulletsManager::CreateEnemyShot(Vector2 startPos, Vector2 targetPos, float radianplus = 0) {

    for (size_t i = 0; i < enemyshots.size(); i++) {	//���˃t���O�������Ă��Ȃ��V���b�g�ԍ���T��
        if (!enemyshots[i]->GetActive()) {				//�V���b�g�̔��˃t���O�������Ă��Ȃ��ԍ�����������
            enemyshots[i]->Create(startPos, targetPos, radianplus);
            return;
        }
    }
};

void BulletsManager::InitPlayerShot() {
    for (size_t i = 0; i < playershots.size(); i++) {
        playershots[i]->Init();
    }
}
void BulletsManager::InitPlayerBom() {
    playerboms->Init();
}
void BulletsManager::InitEnemyShot() {
    for (size_t i = 0; i < enemyshots.size(); i++) {
        enemyshots[i]->Init();
    }
}


int BulletsManager::Update(int framecount) {
    UpdatePlayerShot(framecount);
    UpdatePlayerBom(framecount);
    UpdateEnemyShot(framecount);
    
    return 0;

}
int BulletsManager::Draw() {

    DrawPlayerShot();
    DrawPlayerBom();
    DrawEnemyShot();

    return 0;

}





void BulletsManager::UpdatePlayerShot(int frameocunt) {
    for (size_t i = 0; i < playershots.size(); i++) {
        if (playershots[i]->GetActive()) {					//�V���b�g�t���O��ON�Ȃ�
            playershots[i]->Update(frameocunt);
        }
    }
}
void BulletsManager::UpdatePlayerBom(int frameocunt) {
    if (playerboms->GetActive()) {
        playerboms->Update(frameocunt, PlayerConfig::BOM_SPEED);
    }
}
void BulletsManager::UpdateEnemyShot(int frameocunt) {
    for (size_t i = 0; i < enemyshots.size(); i++) {
        if (enemyshots[i]->GetActive()) {					//�V���b�g�t���O��ON�Ȃ�
            enemyshots[i]->Update(frameocunt);
        }
    }
}

void BulletsManager::DrawPlayerShot() {
    for (size_t i = 0; i < playershots.size(); i++) {
        if (playershots[i]->GetActive()) {					//�V���b�g�t���O��ON�Ȃ�
            int left_x = static_cast<int>(playershots[i]->GetDrawPos().x - PlayerConfig::SHOT_SPEED_HOLLOW);
            int right_x = static_cast<int>(playershots[i]->GetDrawPos().x + PlayerConfig::SHOT_SPEED_HOLLOW);
            int y    = static_cast<int>(playershots[i]->GetDrawPos().y);

            render_->DrawFromCenterPos(shottex, 0, left_x, y, PlayerConfig::SHOT_PIC_SIZE);
            render_->DrawFromCenterPos(shottex, 0, right_x,y, PlayerConfig::SHOT_PIC_SIZE);

            
        }
    }
}
void BulletsManager::DrawPlayerBom() {
    if (playerboms->GetActive()) {
    
        int s = 0;
    }
    if (playerboms->GetActive() && !playerboms->GetIsBomber()) {
        render_->DrawFromCenterPos(bomtex, 0, playerboms->GetDrawPos(),PlayerConfig::BON_PIC_SIZE);
    }
}
void BulletsManager::DrawEnemyShot() {
    for (size_t i = 0; i < enemyshots.size(); i++) {
        if (enemyshots[i]->GetActive()) {					//�V���b�g�t���O��ON�Ȃ�
            render_->DrawFromCenterPos(shottex, 0, enemyshots[i]->GetDrawPos(),EnemyShotConfig::PIC_SIZE);
        }
    }
}

int BulletsManager::GetEnemyshotSum()
{
    return static_cast<int>(enemyshots.size());
}

int BulletsManager::GetPlayershotSum()
{
    return static_cast<int>(playershots.size());
}

std::shared_ptr<EnemyShot> BulletsManager::GetEnemyShotIndex(int i)
{
    return enemyshots[i];
    
}

std::shared_ptr<PlayerShot> BulletsManager::GetPlayerShotIndex(int i)
{
    return playershots[i];
}

std::shared_ptr<PlayerBom> BulletsManager::GetPlayerBom()
{
    return playerboms;
}
