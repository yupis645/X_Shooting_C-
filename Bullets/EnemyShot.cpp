#include "EnemyShot.h"

#include "IPlayer.h"

using namespace EnemyShotConfig;


EnemyShot::EnemyShot() : rad(0) {  }

// ���N���X�� Update �֐����I�[�o�[���C�h
int EnemyShot::Create(Vector2 startPos, Vector2 targetPos, float radianplus = 0) {

    active = true;
    position = startPos;

    /*hitbox������*/
    hitbox.CenterPositionSync(position, PIC_SIZE);
    //_s->shot[Nextshotnum].player_x = (int)_p.center_x;				//���̊֐��ɓ������u�Ԃ̃v���C���[���W���L����(X��)
    //_s->shot[Nextshotnum].player_y = (int)_p.center_y;				//���̊֐��ɓ������u�Ԃ̃v���C���[���W���L����(Y��)

    rad = atan2(targetPos.y - (float)hitbox.top, targetPos.x - (float)hitbox.left);		//�O�p�`�̊p�x���Z�o����

    //���˂���e�̌����𐳕��ɂ���ĕ������i��
    if (radianplus != 0) {
        rad += radianplus;
    }

    return 0;
}

int EnemyShot::Init() {
    InitClear();
    rad = 0;

    return 0;
}
int EnemyShot::Update(int framecount)  {

    if (!active) return 0;

    //�e����ʓ��ɂ���ꍇ
    if (hitbox.left >= 0 && hitbox.top >= 0 && hitbox.left <= ScreenConfig::SRN_W && hitbox.top <= ScreenConfig::SRN_H) {
        position.x += EnemyShotConfig::SPEED* cos(rad);		//X���̈ړ�
        position.y += EnemyShotConfig::SPEED * sin(rad);		//Y���̈ړ�

        /*�e�̓����蔻��̓���*/
        hitbox.CenterPositionSync(position, PIC_SIZE);

    }
    //�e����ʊO�ɏo���ꍇ
    else {  Init(); }


    return 0;
}





