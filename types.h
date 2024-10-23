#ifndef TYPES_H
#define TYPES_H

#include "common.h"
//-----------------------------------------------------------------------------------------------------
//				�����̕ϐ��ō\�����ꂽ�f�[�^�\����錾����t�@�C��
// 
// 
//-----------------------------------------------------------------------------------------------------

//===========================================================
//         ����png�f�[�^�ƃX���C�X���邽�߂̐ݒ�
// 
// width��height�ŃX���C�X����l�p�����
// row�͉��Acoluwn�͏c�ɉ����X���C�X���邩���߂�
// �X���C�X���閇����row * coluwn�ŎZ�o�ł���
//===========================================================
struct UseTextureDataConfig
{
    const wchar_t* texturepath;     //png�̃f�[�^�p�X
    int width;                      //�P���̃X���C�X�ɑ΂��鉡�̒���
    int height;                     //�P���̃X���C�X�ɑ΂���c�̒���
    int row;                        // �������ɐ؂��鐔
    int column;                     //�c�����ɐ؂��鐔
};

//===========================================================
// �摜���Ǘ�����map�Ŏ��ʂ��邽�߂̃L�[�Ɏg���萔
//===========================================================
enum class TextureType {
    Title,
    Player,
    Targetsight,
    Bullet,
    Bom,
    Map,
    Bomber,
    PlayerBomber,
    BomBomber,
    Air_EnemyBomber,
    Ground_EnemyBomber,

    AirEnemy,
    Toroid,
    Torkan,
    Giddospario,
    Zoshi,
    Jara,
    Kapi,
    Terrazi,
    Zakato,
    Bragzakato,
    Garuzakato,
    Bacura,

    GroundEnemy,
    Barra,
    Zolbak,
    Logram,
    Domogram,
    Derota,
    Grobda,
    Bozalogram,
    Sol,
    Garubarra,
    Garuderota,
    Boss,
    BossParts,
    Algo,
    Ad_core,
    Spflag
};


//===========================================================
// �}�b�v�`�b�v�̏��̔z��Ɛi�s�x���Ǘ�����
//===========================================================
struct MapStatus {
    std::array<int,MapConfig::MAP_H * MapConfig::MAP_W> data;
    int y;
};



#endif //TYPES_H