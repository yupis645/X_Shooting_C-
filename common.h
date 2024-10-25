#ifndef GAME_DEFINITIONS_H
#define GAME_DEFINITIONS_H

#include	"conioex.h" 
#include "Geometry.h"
#include "Game.h"
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <Windows.h>
#include <array>
#include <iostream>
#include <vector>
#include <map>
#include "di.hpp"


namespace di = boost::di;

// ----------------------------------------------------------------
// �A�v�����ʂ̒�`
// ----------------------------------------------------------------


#define TestMode true			//�^�C�g����|�[�Y��ʂɑ���������o�� & �f�o�b�N���[�h���g�p�ł���悤�ɂȂ�B

// DebugOn �� StageRupe �� TestMode �L�����̂ݍ쓮����
#define DebugOn true			//TestMode��true�̎��̂ݎg�p�ł���f�o�b�N���[�h�̃t���O�Bfalse�ɂ���ƃf�o�b�N���[�h�ɓ���Ȃ��Ȃ�
#define StageRupe false			//true�Ȃ�w�肵���X�e�[�W���烋�[�v����Bfalse�Ȃ�{�X��|�����n�_�ŏI��
//�����܂�


//==============================================================
//					��ʊ֘A�̒�`
// 
//==============================================================
namespace ScreenConfig {
	constexpr int PXW        = 1;		     //�T�C�Y�䗦(����)
	constexpr int PXH        = 1;		     //�T�C�Y�䗦(����)
	constexpr int WIN_W      = 200 * 3;	     //(8*25*4)	//�E�B���h�E�T�C�Y(����)
	constexpr int WIN_H      = 260 * 3;		 //(8*25*3)	//�E�B���h�E�T�C�Y(�c��)
	constexpr int SRN_W      = WIN_W / PXW;	 //��ʃT�C�Y(����)
	constexpr int SRN_H      = WIN_H / PXH;	 //��ʃT�C�Y(����)
	constexpr int CENTER_X   = SRN_W / 2;	 //��ʂ̒���X���W
	constexpr int CENTER_Y   = SRN_H / 2;	 //��ʂ̒���Y���W
	constexpr int WORD_W     = 8;	         //1�����̉���
	constexpr int HALFWORD_W = 4;		     //���p�����̉���
	constexpr int WORD_H     = 15;		     //1�����̍���
}

//==============================================================
//				���ID�F���݂̉�ʂ̏�Ԃ�\��
// 
//==============================================================
enum SceneID {
	TITLE = 1,     // �^�C�g��
	GAME = 2,      // �Q�[��
	RESULT = 3,    // ����
	OPTION = 4,    // �I�v�V����
	APP_EXIT = 999 // �A�v���I��
};

namespace SceneConfig {
	constexpr int FRAME_COUNT_VALUE = 1;		//�t���[���J�E���g����ۂ�1�t���[���ŉ��Z����l

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//==============================================================
//					�}�b�v�֘A�̒�`
// 
//==============================================================
namespace MapConfig {
	constexpr int MAP_W = ScreenConfig::SRN_W / 31;	//�}�b�v�̃T�C�Y(��ʂ̑傫�� / �}�b�v�`�b�v�̃T�C�Y)	
	constexpr int MAP_H = ScreenConfig::SRN_H / 31;	//�}�b�v�̃T�C�Y(��ʂ̑傫�� / �}�b�v�`�b�v�̃T�C�Y)
	constexpr int CHIP_SIZE = 32;			//�}�b�v�`�b�v�̃T�C�Y(�����`)
	constexpr int SCROLL_SPEED = 1;		//�X�N���[���̃X�s�[�h
	constexpr int MAX_STAGE = 3;		//�X�e�[�W��
}
//==============================================================
//					PNG�f�[�^�֘A
// 
//==============================================================
struct TextureConfig {
	int width;   // 1�̃X���C�X�̉���
	int height;  // 1�̃X���C�X�̏c��
	int rows;    // �s��
	int columns; // ��
	int startindex;
	int indexcount;
};

namespace TextureConfigs {
	constexpr TextureConfig TITLE          { 198, 58,  1,  1, 0, 1         };
	constexpr TextureConfig PLAYER         { 32 , 32,  6,  2, 2, 3         };
	constexpr TextureConfig TARGETSIGHT    { 32 , 32,  6,  2, 0, 2         };
	constexpr TextureConfig BULLET         { 8  ,  8,  3,  1, 0, 2         };
	constexpr TextureConfig BOM            { 8  ,  8,  3,  1, 2, 1         };
	constexpr TextureConfig BOSS           { 32 , 32, 11, 11, 0, 11 * 11   };
	constexpr TextureConfig BOSSALGO       { 32 , 32,  5,  1, 0, 1         };
	constexpr TextureConfig COMMON_BOMBER  { 48 , 48,  6,  1, 0, 6         };
	constexpr TextureConfig AIR_ENEMYBOMBER{ 48 , 48,  6,  1, 6, 6         };
	constexpr TextureConfig MAP            { 32 , 32, 12, 10, 0, 12 * 10   };

	constexpr TextureConfig TOROID         { 32, 32,  1, 8 , 0, 8        };
	constexpr TextureConfig TORKAN         { 32, 32,  8, 2 , 8, 7        };
	constexpr TextureConfig GIDDOSPARIO    { 32, 32,  8, 3 ,16, 8        };
	constexpr TextureConfig ZOSHI          { 32, 32,  8, 4 ,24, 4        };
	constexpr TextureConfig JARA           { 32, 32,  8, 5 ,32, 6        };
	constexpr TextureConfig KAPI           { 32, 32,  8, 6 ,40, 7        };
	constexpr TextureConfig TERRAZI        { 32, 32,  8, 7 ,48, 7        };
	constexpr TextureConfig ZAKATO         { 32, 32,  8, 8 ,56, 1        };
	constexpr TextureConfig BRAGZAKATO     { 32, 32,  8, 9 ,64, 1        };
	constexpr TextureConfig GARUZAKATO     { 32, 32,  8,10 ,72, 1        };
	constexpr TextureConfig BACURA         { 48, 48,  8, 8 ,56, 8        };

	constexpr TextureConfig BARRA          { 32, 32,  1, 4 ,0,  2        };
	constexpr TextureConfig ZOLBAK         { 32, 32,  1, 8 ,4,  4        };
	constexpr TextureConfig LOGRAM         { 32, 32,  1,12 ,8,  4        };
	constexpr TextureConfig DOMOGRAM       { 32, 32,  1,16 ,12, 4        };
	constexpr TextureConfig DEROTA         { 32, 32,  1,20 ,16, 4        };
	constexpr TextureConfig GROBDA         { 32, 32,  1,24 ,20, 4        };
	constexpr TextureConfig BOZALOGRAM     { 32, 32,  1,28 ,24, 1        };
	constexpr TextureConfig SOL            { 32, 32,  1,32 ,28, 4        };
	constexpr TextureConfig GARUBARRA      { 64, 64,  1,22 ,20, 1        };
	constexpr TextureConfig GARUDEROTA     { 64, 64,  1,28 ,24, 4        };
	constexpr TextureConfig ALGO           { 48, 48,  1, 4 , 0, 4        };
	constexpr TextureConfig AD_CORE        { 64, 64,  1, 1 , 0, 1        };
	constexpr TextureConfig SPFLAG         { 32, 32,  1, 3 , 3, 1        };

}


struct EnemyStatus {
	int number;			//�G�l�~�[�̎�ނ���ʂ��邽�߂̔ԍ�
	int hitbox_size;	//�����蔻��̃T�C�Y
	int pic_size;		//�摜�T�C�Y
	int type;		    //����̂̈Ⴄ����
	int anim_sum;	    //�s���p�^�[���̐�
	int points;		    //�|�C���g
	float speed;	    //�ړ����x
	float acceleration;	//�����x
};

// �G�f�[�^�̔z��
namespace EnemyStatusData{
	constexpr EnemyStatus DUMMY      {-1 ,  0,  0, 0,  0,    0, 0.0f, 0.0f  };	// �_�~�[
	constexpr EnemyStatus TOROID     { 0 , 32, 32, 1,  8,   30, 2.0f, 0.04f };	// �g�[���C�h
	constexpr EnemyStatus TORKAN     { 1 , 32, 32, 0,  7,   50, 4.0f, 0.0f  };   // �^���P��
	constexpr EnemyStatus GIDDOSPARIO{ 2 , 16, 32, 0,  8,   10, 7.0f, 0.0f  };   // �M�h�X�p���I
	constexpr EnemyStatus ZOSHI      { 3 , 32, 32, 2,  4,   70, 3.0f, 0.0f  };   // �]�V�[
	constexpr EnemyStatus JARA       { 4 , 32, 32, 0,  6,  150, 4.0f, 0.04f };   // �W�A��
	constexpr EnemyStatus KAPI       { 5 , 32, 32, 0,  7,  300, 4.0f, 0.15f };   // �J�s
	constexpr EnemyStatus TERRAZI    { 6 , 32, 32, 0,  7,  700, 5.0f, 0.08f };   // �e���W
	constexpr EnemyStatus ZAKATO     { 7 , 16, 32, 3,  1,  100, 3.0f, 0.0f  };   // �U�J�[�g
	constexpr EnemyStatus BRAGZAKATO { 8 , 16, 32, 3,  1,  600, 3.0f, 0.0f  };   // �u���O�U�J�[�g
	constexpr EnemyStatus GARUZAKATO { 9 , 16, 32, 0,  1, 1000, 3.0f, 0.0f  };   // �K���U�J�[�g
	constexpr EnemyStatus BACURA     { 10, 48, 48, 0,  8,    0, 2.0f, 0.0f  };   // �o�L����

	constexpr EnemyStatus BARRA      { 50, 32, 32, 0,  1,  100, 0.0f , 0.0f };   // �o�[��
	constexpr EnemyStatus ZOLBAK     { 51, 32, 32, 0,  4,  200, 0.0f , 0.0f };   // �]���o�O
	constexpr EnemyStatus LOGRAM     { 52, 32, 32, 4,  4,  300, 0.0f , 0.0f };   // ���O����
	constexpr EnemyStatus DOMOGRAM   { 53, 32, 32, 0,  4,  800, 0.75f, 0.5f };   // �h���O����
	constexpr EnemyStatus DEROTA     { 54, 32, 32, 0,  4,  200, 0.0f , 0.0f };   // �f���[�_
	constexpr EnemyStatus GROBDA     { 55, 32, 32, 8,  4,  200, 0.5f , 0.5f };   // �O���u�_�[
	constexpr EnemyStatus BOZALOGRAM { 56, 32, 32, 0,  1,  600, 0.0f , 0.0f };   // �{�U���O����
	constexpr EnemyStatus SOL        { 57, 32, 32, 0,  4, 2000, 0.0f , 0.0f };   // �\��
	constexpr EnemyStatus GARUBARRA  { 58, 32, 63, 0,  1,  300, 0.0f , 0.0f };   // �K���o�[��
	constexpr EnemyStatus GARUDEROTA { 59, 32, 64, 0,  4, 2000, 0.0f , 0.0f };   // �K���f���[�^
	constexpr EnemyStatus ALGO       { 60, 16, 48, 0,  0, 1000, 0.0f , 0.0f };   // �A���S
	constexpr EnemyStatus AD_CORE    { 61, 32, 64, 0,  1, 4000, 0.0f , 0.0f };   // A/G�R�A
	constexpr EnemyStatus SPFLAG     { 62, 32, 32, 0,  1, 1000, 0.0f , 0.0f };   // SP�t���b�O
}

namespace EnemyTextureConfig {
	constexpr int S_SIZE_SLICE_WIDTH = 32;      // 1�̃X���C�X�̉���
	constexpr int S_SIZE_SLICE_HEIGHT = 32;     // 1�̃X���C�X�̏c��
	constexpr int M_SIZE_SLICE_WIDTH = 48;      // 1�̃X���C�X�̉���
	constexpr int M_SIZE_SLICE_HEIGHT = 48;     // 1�̃X���C�X�̏c��
	constexpr int L_SIZE_SLICE_WIDTH = 64;      // 1�̃X���C�X�̉���
	constexpr int L_SIZE_SLICE_HEIGHT = 64;     // 1�̃X���C�X�̏c��
	constexpr int AIR_ENEMY_SLICE_ROWS_MAX = 8;          // �s��
	constexpr int GROUND_ENEMY_SLICE_ROWS_MAX = 4;          // �s��
	constexpr int SLICE_COLUMNS = 1;       // ��
}
//==============================================================
//					���w
// 
//==============================================================
//#define ABS(num) ((num) > 0 ? (num) : -(num))		//�������O�����l��Ԃ�
//#define REPEAT(num,min,max) if(num > max){num = min;} else if(num < min){num = max;}		

template<typename T>
T ABS(T num) {
	return num > 0 ? num : -num;
}

template<typename T>
void Clamp(T& num, T min, T max) {
	if (num > max) {
		num = min;
	}
	else if (num < min) {
		num = max;
	}
}

													/*�ϐ��錾*/

const Boxcollider winView = { 0,0,ScreenConfig::SRN_W,ScreenConfig::SRN_H };		//��ʂ̒[�����̍��W�B��ʓ��ɉf���Ă��邩���肷��


extern bool DebugEnable;



#endif // GAME_DEFINITIONS_H