#include "PlayerShot.h"


//===============================================================
//					�V���b�g�̍쐬
// 
// ���ˍő吔�ȉ��Ȃ���W�ⓖ���蔻���ݒ肵�Ēe�𐶐�����
// �E���˃t���O�����Ă�
// �E�����蔻���ݒ肷��
// �E���˃J�E���g�����Z����
//===============================================================
int PlayerShot::Create(Vector2 pos) {

    active = true;					//�V���b�g���˃t���O�𗧂Ă�

    //SetRectSquareValues(hitbox,SHOT_HITBOX_SIZE);			//�����蔻���ݒ肷��(���@�̓����蔻��Ɠ����傫��)
    hitbox.CenterPositionSync(pos, PlayerConfig::SHOT_HITBOX_WIDTH,PlayerConfig::SHOT_HITBOX_HEIGHT);
    position = pos;

    return 0;
}


//===============================================================
//					�V���b�g�̏�����
// 
// ���N���X����ǉ����ꂽ�ϐ��͂Ȃ��̂Ŋ��N���X��init�ŏ�����
//===============================================================
int PlayerShot::Init() {
    InitClear();

    return false;
}


//===============================================================
//					�V���b�g�̍X�V
// 
// �t���O�������Ă���V���b�g��S�čX�V����
// �EY���W�ړ�
// �E��ʊO�ɏo���炻�̊Ǘ��ԍ��̃V���b�g������������
//===============================================================
int PlayerShot::Update(int framecount) {

    if (!active) return 0;

    position.y -= PlayerConfig::SHOT_SPEED;		//�V���b�g�̍��W��ݒ肵���l���i�߂�
    hitbox.CenterPositionSync(position, PlayerConfig::SHOT_HITBOX_WIDTH, PlayerConfig::SHOT_HITBOX_HEIGHT);

    if (position.y < 0) {			//�V���b�g����ʊO�ɏo����
        Init();
    }

    return 0;
}
