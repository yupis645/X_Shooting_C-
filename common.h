#ifndef GAME_DEFINITIONS_H
#define GAME_DEFINITIONS_H

#include	"conioex.h" 
#include "Geometry.h"

//-------------------------------------------------------------------------------------------
//			Game�Ŏg���\���̂�v���g�^�C�v�錾�����Ă���
// 
//�\���̂� �E�v���C���[ �E�󒆓G �E�n��G �E�{�X�@�E�}�b�v �E�e��摜�f�[�^ �Ȃ�
// �v���g�^�C�v�錾�� �Q�[�����[�v,�e�I�u�W�F�N�g�̏������A�����A�X�V�A�`��
//-------------------------------------------------------------------------------------------

#define TestMode true			//�^�C�g����|�[�Y��ʂɑ���������o�� & �f�o�b�N���[�h���g�p�ł���悤�ɂȂ�B

// DebugOn �� StageRupe �� TestMode �L�����̂ݍ쓮����
#define DebugOn true			//TestMode��true�̎��̂ݎg�p�ł���f�o�b�N���[�h�̃t���O�Bfalse�ɂ���ƃf�o�b�N���[�h�ɓ���Ȃ��Ȃ�
#define StageRupe false			//true�Ȃ�w�肵���X�e�[�W���烋�[�v����Bfalse�Ȃ�{�X��|�����n�_�ŏI��
//�����܂�





//==============================================================
//					/*�v���C���[�֌W�̒�`*/
// 
//==============================================================

namespace PlayerConfig {
	constexpr int SPEED = 5;		//�v���C���[�̈ړ����x	
	constexpr int PLAYER_HITBOX_SIZE = 16;		//�摜�̃T�C�Y
	constexpr int PLAYER_PIC_SIZE = 32;		//�摜�̃T�C�Y

	constexpr int SIGHT_HITBOX_SIZE = 32;		//�摜�̃T�C�Y
	constexpr int SIGHT_PIC_SIZE = 32;		//�摜�̃T�C�Y

	constexpr int MAX_SHOT = 3;		//��ʓ��ɕ\���ł���V���b�g�̐�
	constexpr int SHOT_SPEED = 20;		//�V���b�g�̒e��
	constexpr int SHOT_SPEED_HOLLOW = 8;
	constexpr int SHOT_HITBOX_WIDTH = 32;		//�摜�̃T�C�Y
	constexpr int SHOT_HITBOX_HEIGHT = 16;		//�摜�̃T�C�Y
	constexpr int SHOT_PIC_SIZE = 8;		//�摜�̃T�C�Y

	constexpr int BOM_SPEED = 5;		//�V���b�g�̒e��
	constexpr int BOM_RANGE = 100;		//�{���̎˒�����
	constexpr int BUNBER_HITBOX_SIZE = 24;		//�摜�̃T�C�Y
	constexpr int BON_PIC_SIZE = 8;		//�摜�̃T�C�Y
}
//==============================================================
//					/*�G�l�~�[���ʂ̒�`*/
// 
//==============================================================
namespace AirEnemyConfig {
	constexpr int PIC_LINE_WIDE = 8;		//�󒆓G�̉摜�̍s�̐�
	constexpr int MAX_ENEMY = 20;			//�G�̍ő�o����( �󒆂ƒn��͕ʃJ�E���g)
}
namespace GroundEnemyConfig {
	constexpr int PIC_LINE_WIDE = 4;		//�󒆓G�̉摜�̍s�̐�
	constexpr int MAX_ENEMY = 20;			//�G�̍ő�o����( �󒆂ƒn��͕ʃJ�E���g)
}
namespace EnemyShotConfig {
	constexpr int HITBOX_SIZE = 8;		//�摜�̃T�C�Y
	constexpr int PIC_SIZE = 8;		//�摜�̃T�C�Y
	constexpr int SPEED = 4;			//�G�e�̊�{�̑��x
	constexpr int MAX_SHOT = 17;			//�G�e�̊�{�̑��x

}
constexpr int MAX_LEVEL = 64;			//�G�̏o�����x���̏��

namespace SpriteSize {
	constexpr int PLAYER       = 32;
	constexpr int LOOKON_SIGHT = 32;
	constexpr int BULLET       = 8;
	constexpr int ENEMY_SMALL  = 32;
	constexpr int ENEMY_MEDIUM = 48;
	constexpr int ENEMY_LARGE  = 64;
	constexpr int BOMBER	   = 47;
	constexpr int MAP_CHIP	   = 32;
}


//============================================
//�{�X & �C��A�R�A�̃X�e�[�^�X
//============================================
//typedef struct BOSS {
//	bool F;				//�o���t���O
//	bool down;			//���Ĕ���(�R�A�j��)
//	ENEMY_ST enemy[5];	//�C��~4�ƃR�A�̏��
//	float center_x;		//x�����S���W
//	float center_y;		//y�����S���W
//	int pic_x;			//����x���W(�X�v���C�g�p)
//	int pic_y;			//����y���W(�X�v���C�g�p)
//
//	Bmp* pic[120];				//�{�̂𕪊������X�v���C�g
//	Bmp* pats[5];				//���j�O�̖C��ƃR�A�̉摜
//}BOSS;

//============================================
//�f�o�b�N�p�̍\����
//============================================
struct DenugState {
	bool G_enemy_stop;
	bool A_enemy_stop;
	bool Player_invalid;
};







//==============================================================================================
//					�S�̃V�[���Ŏg�p����f�[�^
// 
// �EGame�ŉ��Z����A���U���g�ŕ\������score
// �E�^�C�g����ʂ�1Player��2Player�ǂ��炩��I�Ԃ��ŏ����l���ς��life
//==============================================================================================
class GameStatus {
public:
	GameStatus() :Score(0), Life(0) {};
	~GameStatus() {}
	// �X�R�A�̃Q�b�^�[�ƃZ�b�^�[
	int score() const { return Score; }
	void score(int s) { Score = s; }
	// ���C�t�̃Q�b�^�[�ƃZ�b�^�[
	int life() const { return Life; }
	void life(int l) { Life = l; }

private:
	int Score;
	int Life;
};
//==============================================================================================
//					instance�Ƃ��đ��݂���I�u�W�F�N�g�̊��N���X
//==============================================================================================
class GameObject {
public:
	GameObject() : position(0, 0), hitbox(0, 0, 0, 0), active(false) {
		// ���ʂ̏���������
	}

	virtual void InitClear() {
		position = Vector2::zero;
		hitbox = Boxcollider::zero;
		active = false;
	}

	virtual Vector2 GetPosition()const { return position; }
	virtual void SetPosition(Vector2 pos) { position = pos; }

	virtual Boxcollider GetHitbox()const { return hitbox; }
	virtual void SetHitbox(Boxcollider box) { hitbox = box; }

	virtual bool GetActive() { return active; }
	virtual void SetActive(bool isactive) { active = isactive; }


	~GameObject() = default;

protected:
	Vector2 position;
	Boxcollider hitbox;
	bool active;
};


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

constexpr int AIR_ENEMY_MAX_LEVEL = 64;

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

enum class TextureBaseName {
	Title,
	Player_Sight,
	Bullet,
	Bomber,
	AirEnemy,
	GroundEnemy,
	Boss,
	Algo_Core,
	MapChip
};

enum class SpriteName {
	Title,
	Player_Sight,
	Bullet,
	Bomber,
	AirEnemy_SmallSprite,
	AirEnemy_MiddleSprite,
	GroundEnemy_SmallSprite,
	GroundEnemy_LargeSprite,
	Boss,
	Algo_Core,
	MapChip
};

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

//==============================================================
//					PNG�f�[�^�֘A
// 
//==============================================================
struct SpritesConfig {
	int width;   // 1�̃X���C�X�̉���
	int height;  // 1�̃X���C�X�̏c��
	int rows;    // �s��
	int columns; // ��
};


namespace SpritesConfigs {
	const std::map<SpriteName, TextureConfig> Configs = {
		{Title                  ,{198						, 58						,  1,  1 }},
		{Player_Sight           ,{SpriteSize::PLAYER		, SpriteSize::PLAYER		,  6,  2}},
		{Bullet                 ,{SpriteSize::BULLET		,SpriteSize::BULLET			,  3,  1,}},
		{Bomber                 ,{SpriteSize::BOMBER		, SpriteSize::BOMBER		,  6,  2}},
		{AirEnemy_SmallSprite   ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	, 11, 11}},
		{AirEnemy_MiddleSprite  ,{SpriteSize::ENEMY_MEDIUM	, SpriteSize::ENEMY_MEDIUM	,  8, 8}},
		{GroundEnemy_SmallSprite,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  4, 8}},
		{GroundEnemy_LargeSprite,{SpriteSize::ENEMY_LARGE	, SpriteSize::ENEMY_LARGE	,  4, 7}},
		{Boss                   ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	, 11, 11}},
		{Algo_Core              ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  4, 2}},
		{MapChip                ,{SpriteSize::MAP_CHIP		, SpriteSize::MAP_CHIP		, 12, 10}}
	};
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
	const std::map<TextureType, TextureConfig> Configs = {
		{TextureType::Title          ,{198, 58,  1,  1, 0, 1}},
		{TextureType::Player         ,{SpriteSize::PLAYER		, SpriteSize::PLAYER		,  6,  2, 2, 3}},
		{TextureType::Targetsight    ,{SpriteSize::LOOKON_SIGHT	, SpriteSize::LOOKON_SIGHT	,  6,  2, 0, 2}},
		{TextureType::Bullet         ,{SpriteSize::BULLET		,SpriteSize::BULLET			,  3,  1, 0, 2}},
		{TextureType::Bom            ,{SpriteSize::BULLET		,  SpriteSize::BULLET		,  3,  1, 2, 1}},
		{TextureType::Boss           ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	, 11, 11, 0, 11 * 11}},
		{TextureType::BossParts      ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  5,  1, 0, 1}},
		{TextureType::Bomber         ,{SpriteSize::BOMBER		, SpriteSize::BOMBER		,  6,  1, 0, 6}},
		{TextureType::Air_EnemyBomber,{SpriteSize::BOMBER		, SpriteSize::BOMBER		,  6,  2, 6, 6}},
		{TextureType::Map            ,{SpriteSize::MAP_CHIP		, SpriteSize::MAP_CHIP		, 12, 10, 0, 12 * 10}},

		{TextureType::Toroid         ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  8, 1 , 0, 8}},
		{TextureType::Torkan         ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  8, 2 , 8, 7}},
		{TextureType::Giddospario    ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  8, 3 ,16, 8}},
		{TextureType::Zoshi          ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  8, 4 ,24, 4}},
		{TextureType::Jara           ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  8, 5 ,32, 6}},
		{TextureType::Kapi           ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  8, 6 ,40, 7}},
		{TextureType::Terrazi        ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  8, 7 ,48, 7}},
		{TextureType::Zakato         ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  8, 8 ,56, 1}},
		{TextureType::Bragzakato     ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  8, 9 ,64, 1}},
		{TextureType::Garuzakato     ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  8,10 ,72, 1}},
		{TextureType::Bacura         ,{SpriteSize::ENEMY_MEDIUM	, SpriteSize::ENEMY_MEDIUM	,  8, 8 ,56, 8}},

		{TextureType::Barra          ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  4, 1 ,0,  2}},
		{TextureType::Zolbak         ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  4, 2 ,4,  4}},
		{TextureType::Logram         ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  4, 3 ,8,  4}},
		{TextureType::Domogram       ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  4, 4 ,12, 4}},
		{TextureType::Derota         ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  4, 5 ,16, 4}},
		{TextureType::Grobda         ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  4, 6 ,20, 4}},
		{TextureType::Bozalogram     ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  4, 7 ,24, 1}},
		{TextureType::Sol            ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  4, 8 ,28, 4}},
		{TextureType::Garubarra      ,{SpriteSize::ENEMY_LARGE	, SpriteSize::ENEMY_LARGE	,  4, 6 ,20, 1}},
		{TextureType::Garuderota     ,{SpriteSize::ENEMY_LARGE	, SpriteSize::ENEMY_LARGE	,  4, 7 ,24, 4}},
		{TextureType::Algo           ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  4, 1 , 0, 4}},
		{TextureType::Ad_core        ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  4, 2 , 4, 1}},
		{TextureType::Spflag         ,{SpriteSize::ENEMY_SMALL	, SpriteSize::ENEMY_SMALL	,  4, 1 , 2, 1}}
	};
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
	constexpr EnemyStatus TOROID     { 0 , 32, 32, 0,  8,   30, 2.0f, 0.04f };	// �g�[���C�h
	constexpr EnemyStatus TORKAN     { 1 , 32, 32, 0,  6,   50, 4.0f, 0.0f  };   // �^���P��
	constexpr EnemyStatus GIDDOSPARIO{ 2 , 16, 32, 0,  8,   10, 7.0f, 0.0f  };   // �M�h�X�p���I
	constexpr EnemyStatus ZOSHI      { 3 , 32, 32, 0,  4,   70, 3.0f, 0.0f  };   // �]�V�[
	constexpr EnemyStatus JARA       { 4 , 32, 32, 0,  6,  150, 4.0f, 0.06f };   // �W�A��
	constexpr EnemyStatus KAPI       { 5 , 32, 32, 0,  7,  300, 4.0f, 0.15f };   // �J�s
	constexpr EnemyStatus TERRAZI    { 6 , 32, 32, 0,  7,  700, 5.0f, 0.08f };   // �e���W
	constexpr EnemyStatus ZAKATO     { 7 , 16, 32, 0,  1,  100, 3.0f, 0.0f  };   // �U�J�[�g
	constexpr EnemyStatus BRAGZAKATO { 8 , 16, 32, 0,  1,  600, 3.0f, 0.0f  };   // �u���O�U�J�[�g
	constexpr EnemyStatus GARUZAKATO { 9 , 16, 32, 0,  1, 1000, 3.0f, 0.0f  };   // �K���U�J�[�g
	constexpr EnemyStatus BACURA     { 10, 48, 48, 0,  8,    0, 2.0f, 0.0f  };   // �o�L����

	constexpr EnemyStatus BARRA      { 50, 32, 32, 0,  1,  100, 0.0f , 0.0f };   // �o�[��
	constexpr EnemyStatus ZOLBAK     { 51, 32, 32, 0,  4,  200, 0.0f , 0.0f };   // �]���o�O
	constexpr EnemyStatus LOGRAM     { 52, 32, 32, 0,  4,  300, 0.0f , 0.0f };   // ���O����
	constexpr EnemyStatus DOMOGRAM   { 53, 32, 32, 0,  4,  800, 0.75f, 0.5f };   // �h���O����
	constexpr EnemyStatus DEROTA     { 54, 32, 32, 0,  4,  200, 0.0f , 0.0f };   // �f���[�_
	constexpr EnemyStatus GROBDA     { 55, 32, 32, 0,  4,  200, 0.5f , 0.5f };   // �O���u�_�[
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

//============================================================================================================================
//			�C���^�[�t�F�[�X�^�ϐ��̃C���X�^���X�`�F�b�N
// 
// �C���^�[�t�F�[�X�^���ŏ��Ɏw�肵�A���̂��Ƃɔ��ʂ����������N���X���w�肷�邱�Ƃ�
//		�����N���X���C���X�^���X������Ă��邩�m�F�ł���B�Ԃ�l��
//		�����N���X�Ȃ炻�̃N���X���A��
//		����ȊO�Ȃ�nullptr�A��
//============================================================================================================================
template <typename TargetType, typename InterfaceType>
std::shared_ptr<TargetType> InterfaceInstanceCheak(const std::shared_ptr<InterfaceType>& instance, const std::string& typeName) {
	auto castedInstance = std::dynamic_pointer_cast<TargetType>(instance);

	return castedInstance;
}

//============================================================================================================================
//								�`��
//============================================================================================================================
struct Textures {
	ComPtr<ID3D11ShaderResourceView> SRV;     //�V�F�[�_�[���\�[�X�r���[
	std::unique_ptr<DirectX::SpriteBatch> Sprite;            //2D�X�v���C�g��`�ʂ���N���X
};

													/*�ϐ��錾*/

const Boxcollider winView = { 0,0,ScreenConfig::SRN_W,ScreenConfig::SRN_H };		//��ʂ̒[�����̍��W�B��ʓ��ɉf���Ă��邩���肷��


extern bool DebugEnable;




//namespace TextureConfigs {
//	constexpr TextureConfig TITLE          { 198, 58,  1,  1, 0, 1         };
//	constexpr TextureConfig PLAYER         { 32 , 32,  6,  2, 2, 3         };
//	constexpr TextureConfig TARGETSIGHT    { 32 , 32,  6,  2, 0, 2         };
//	constexpr TextureConfig BULLET         { 8  ,  8,  3,  1, 0, 2         };
//	constexpr TextureConfig BOM            { 8  ,  8,  3,  1, 2, 1         };
//	constexpr TextureConfig BOSS           { 32 , 32, 11, 11, 0, 11 * 11   };
//	constexpr TextureConfig BOSSALGO       { 32 , 32,  5,  1, 0, 1         };
//	constexpr TextureConfig COMMON_BOMBER  { 48 , 48,  6,  1, 0, 6         };
//	constexpr TextureConfig AIR_ENEMYBOMBER{ 48 , 48,  6,  2, 6, 6         };
//	constexpr TextureConfig MAP            { 32 , 32, 12, 10, 0, 12 * 10   };
//
//	constexpr TextureConfig TOROID         { 32, 32,  8, 1 , 0, 8        };
//	constexpr TextureConfig TORKAN         { 32, 32,  8, 2 , 8, 7        };
//	constexpr TextureConfig GIDDOSPARIO    { 32, 32,  8, 3 ,16, 8        };
//	constexpr TextureConfig ZOSHI          { 32, 32,  8, 4 ,24, 4        };
//	constexpr TextureConfig JARA           { 32, 32,  8, 5 ,32, 6        };
//	constexpr TextureConfig KAPI           { 32, 32,  8, 6 ,40, 7        };
//	constexpr TextureConfig TERRAZI        { 32, 32,  8, 7 ,48, 7        };
//	constexpr TextureConfig ZAKATO         { 32, 32,  8, 8 ,56, 1        };
//	constexpr TextureConfig BRAGZAKATO     { 32, 32,  8, 9 ,64, 1        };
//	constexpr TextureConfig GARUZAKATO     { 32, 32,  8,10 ,72, 1        };
//	constexpr TextureConfig BACURA         { 48, 48,  8, 8 ,56, 8        };
//
//	constexpr TextureConfig BARRA          { 32, 32,  4, 1 ,0,  2        };
//	constexpr TextureConfig ZOLBAK         { 32, 32,  4, 2 ,4,  4        };
//	constexpr TextureConfig LOGRAM         { 32, 32,  4, 3 ,8,  4        };
//	constexpr TextureConfig DOMOGRAM       { 32, 32,  4, 4 ,12, 4        };
//	constexpr TextureConfig DEROTA         { 32, 32,  4, 5 ,16, 4        };
//	constexpr TextureConfig GROBDA         { 32, 32,  4, 6 ,20, 4        };
//	constexpr TextureConfig BOZALOGRAM     { 32, 32,  4, 7 ,24, 1        };
//	constexpr TextureConfig SOL            { 32, 32,  4, 8 ,28, 4        };
//	constexpr TextureConfig GARUBARRA      { 64, 64,  4, 6 ,20, 1        };
//	constexpr TextureConfig GARUDEROTA     { 64, 64,  4, 7, 24, 4        };
//	constexpr TextureConfig ALGO           { 32, 32,  4, 1 , 0, 4        };
//	constexpr TextureConfig AD_CORE        { 32, 32,  4, 2 , 4, 1        };
//	constexpr TextureConfig SPFLAG         { 32, 32,  4, 1 , 2, 1        };
//
//}


#endif // GAME_DEFINITIONS_H