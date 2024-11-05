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
    AirEnemyEnd,

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
    Spflag,
    GroundEnemyEnd
};
//===========================================================
// �G��ԍ����Ǘ�����
//===========================================================
namespace EnemyID {
    enum EnemyName {
        Toroid = 0,
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
        AirEnemyEnd,

        Barra = 50,
        Zolbak,
        Logram,
        Domogram,
        Derota,
        Grobda,
        Bozalogram,
        Sol,
        Garubarra,
        Garuderota,
        Algo,
        Ad_core,
        Spflag,
        GroundEnemyEnd,


        toroid_type2 = 100 + Toroid,
        zoshi_type2 = 100 + Zoshi,
        zoshi_type3 = 200 + Zoshi,
        Jara_type2  = 100 + Jara,
        zakato_type2 = 100 + Zakato,
        zakato_type3 = 200 + Zakato,
        zakato_type4 = 300 + Zakato,
        bragzakato_type2 = 100 + Bragzakato,
        bragzakato_type3 = 200 + Bragzakato,
        bragzakato_type4 = 300 + Bragzakato,

        Logram_type2 = 100 + Logram,
        Logram_type3 = 200 + Logram,
        Logram_type4 = 300 + Logram,
        Logram_type5 = 400 + Logram,
        Garubarra_type2 = 100 + Garubarra,
        Garubarra_type3 = 200 + Garubarra,
        Garubarra_type4 = 300 + Garubarra,
        Garubarra_type5 = 400 + Garubarra,
        Garubarra_type6 = 500 + Garubarra,
        Garubarra_type7 = 600 + Garubarra,
        Garubarra_type8 = 700 + Garubarra,
        Garubarra_type9 = 800 + Garubarra,


    };
};

//===========================================================
// �}�b�v�`�b�v�̏��̔z��Ɛi�s�x���Ǘ�����
//===========================================================
struct MapStatus {
    std::array<int,MapConfig::MAP_H * MapConfig::MAP_W> data;
    int y;
};



#endif //TYPES_H